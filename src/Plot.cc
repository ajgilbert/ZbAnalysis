//Class Header
#include "Plot.h"
//Standard Library
#include <vector>
#include <iostream>
//ZbAnalysis
#include "TH1PlotElement.h"
#include "RatioPlotElement.h"
//ROOT
#include "TROOT.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TPaveStats.h"
#include "THStack.h"
#include "TPad.h"

namespace ajg{

  bool Plot::AddTH1PlotElement(ajg::TH1PlotElement element) {
    if (element_map_.count(element.name()) == 0) {
      if (!element.hist_ptr()) {
        std::cerr << "Error: Cannot add TH1PlotElement with name \"" <<
          element.name() << "\", TH1F pointer is null." << std::endl;
        return false;
      } else {
        elements_.push_back(element);
        element_map_[element.name()] = element;
        if (element.in_stack()) ++n_in_stack;
      }
      return true;
    } else {
      std::cerr << "Error: Cannot add TH1PlotElement with name \"" <<
        element.name() << "\", name already in use." << std::endl;
      return false;
    }
  }

  bool Plot::AddRatioPlotElement(ajg::RatioPlotElement element) {
    ratios_.push_back(element);
    return true;
  }
  
  void Plot::SetRatioYaxisRange(double min, double max) {
    custom_ratio_y_axis_range = true;
    ratio_y_axis_min = min;
    ratio_y_axis_max = max;
  }

  void Plot::SetXaxisRange(double min, double max) { 
    custom_x_axis_range = true;
    x_axis_min = min;
    x_axis_max = max;
  }

  int Plot::GeneratePlot() {

    SetTdrStyle();
    unsigned n_elements = elements_.size();
    unsigned n_legend = 0;
    double y_pos_max = 0.90;
    double y_pos_current = 0.90;
    THStack thstack("stack","stack");
    unsigned n_added_to_stack = 0;

    //1st Loop through elements - information gathering
    for (unsigned i = 0; i < n_elements; ++i) {
      TH1PlotElement const& ele = elements_[i];
      //Count number of elements with a legend entry
      if (ele.legend_text() != "") ++n_legend;
      //Overide whatever default style has been applied to the histograms
      ele.hist_ptr()->UseCurrentStyle();
    }

    //Create a TLegend object, if necessary
    TLegend *legend = 0;
    if (n_legend > 0) {
      //Allow 5% of the Canvas height for each 'row'
      double legend_y1 = y_pos_max - (n_legend * legend_height);
      y_pos_current = legend_y1 - 0.03;
      legend = new TLegend(0.60,legend_y1,0.90,y_pos_max,"","brNDC");
    }

    //Set up canvas (and optionally pads)
    TCanvas* canv = new TCanvas("canv","canv");
    canv->cd();
    TPad* upper = NULL;
    TPad* lower = NULL;
    if (draw_ratio_hist) {
      upper = new TPad("upper","pad",0,0.3,1,1);
      lower = new TPad("lower","pad",0,0,1,0.30);
      upper->SetBottomMargin(0.02);
      upper->Draw();
      upper->cd();
    }

    double max_bin_content = 0.0;
    bool first_drawn = false;
    for (unsigned i = 0; i < n_elements; ++i) {
      TH1PlotElement & ele = elements_[i];
      //This is a fix for histograms with negative bin content
      //for which Sumw2 has not already been called
      for (int j = 0; j < ele.hist_ptr()->GetNbinsX(); ++j) {
        if (ele.hist_ptr()->GetBinContent(j) < 0) 
          ele.hist_ptr()->SetBinContent(j,0.0);
      }
      ele.hist_ptr()->Sumw2();
      //If draw_normalised is set, this takes priority over any scale factor
      if (!ele.draw_normalised()) {
        ele.hist_ptr()->Scale(ele.scale_factor());
      } else {
        //I THINK THIS IGNORES UNDER/OVERFLOW BINS - BUT SHOULD
        //REALLY BE BETTER DEFINED
        ele.hist_ptr()->Scale(1./ele.hist_ptr()->Integral());
      }

      ele.hist_ptr()->Rebin(ele.rebin_factor());
      ele.hist_ptr()->SetLineColor(ele.line_color());
      ele.hist_ptr()->SetLineWidth(ele.line_width());
      ele.hist_ptr()->SetLineStyle(ele.line_style());
      ele.hist_ptr()->SetMarkerColor(ele.marker_color());
      ele.hist_ptr()->SetMarkerSize(ele.marker_size());
      ele.hist_ptr()->SetMarkerStyle(ele.marker_style());
      ele.hist_ptr()->SetFillColor(ele.fill_color());
      ele.hist_ptr()->SetFillStyle(ele.fill_style());
      //UPDATE: MAKE THIS AN OPTION
      ele.hist_ptr()->SetStats(false);

      if (ele.legend_text() != ""){
        std::string leg_options = "";
        if (ele.draw_fill()) leg_options += "f";
        if (ele.draw_line()) leg_options += "l";
        if (ele.draw_marker() || ele.draw_stat_error_y()) leg_options += "p";
        legend->AddEntry(ele.hist_ptr(),
            ele.legend_text().c_str(),leg_options.c_str());
      }
      std::string draw_options = "";
      if (ele.draw_fill()) draw_options += "HIST";
      if (ele.draw_marker()) draw_options += "P";
      if (ele.draw_stat_error_y()) draw_options += "E1";

      //Loop through bins of each histo (respecting any custom
      //x-axis range that is applied) to find the largest bin
      for (int j = 0; j < ele.hist_ptr()->GetNbinsX(); ++j) {
        bool bin_in_range = true;
        if (custom_x_axis_range) {
          if ((ele.hist_ptr()->GetBinLowEdge(j) < x_axis_min)
              || (ele.hist_ptr()->GetXaxis()->GetBinUpEdge(j) > x_axis_max))
            bin_in_range = false;
        }
        if (bin_in_range) {
          if (ele.hist_ptr()->GetBinContent(j) > max_bin_content) {
            max_bin_content = ele.hist_ptr()->GetBinContent(j);
          }
        }
      }

      //Special actions for first histogram drawn
      if (i == 0) {
        ele.hist_ptr()->GetXaxis()->SetTitle(x_axis_title.c_str());
        if (x_axis_min > 0 && x_axis_max > 0){
          ele.hist_ptr()->GetXaxis()->SetRangeUser(x_axis_min,x_axis_max);
        }
        if (draw_ratio_hist) {
          ele.hist_ptr()->GetXaxis()->SetLabelSize(0.0);
          ele.hist_ptr()->GetXaxis()->SetTitleSize(0.0);
        }

        ele.hist_ptr()->GetYaxis()->SetTitle(y_axis_title.c_str());
        //ele.hist_ptr()->SetName("Madgraph");
        if (!ele.in_stack()) {
          ele.hist_ptr()->Draw(draw_options.c_str());
          first_drawn = true;
        } else {
          thstack.Add(ele.hist_ptr());
          if (n_added_to_stack == 0) thstack.SetHistogram(ele.hist_ptr());
          ++n_added_to_stack;
          if (n_added_to_stack == n_in_stack) {
            thstack.Draw();
            first_drawn = true;
          }
        }

        canv->Update();
        /*
           TPaveStats *st = (TPaveStats*)ele.hist_ptr()->FindObject("stats");
           st->SetX1NDC(0.65); 
           st->SetX2NDC(0.89); 
           st->SetY1NDC(0.6); 
           st->SetY2NDC(0.75); 
           */
      } else {
        //ele.hist_ptr()->SetName("aMC@NLO");
        if (!ele.in_stack()) {
          std::string same_opt = "";
          if (first_drawn) same_opt = "SAME";
          first_drawn = true;
          ele.hist_ptr()->Draw((same_opt+draw_options).c_str());
        } else {
          thstack.Add(ele.hist_ptr());
          ++n_added_to_stack;
          if (n_added_to_stack == n_in_stack) {
            std::string same_opt = "";
            if (first_drawn) same_opt = "SAME";
            first_drawn = true;
            thstack.Draw((same_opt+"HIST").c_str());
          }
        }
        canv->Update();
        /*
           TPaveStats *st = (TPaveStats*)ele.hist_ptr()->FindObject("stats");
           st->SetX1NDC(0.65); 
           st->SetX2NDC(0.89); 
           st->SetY1NDC(0.45); 
           st->SetY2NDC(0.6); 
           */
      }



    }

    TLatex *title_latex = new TLatex();
    title_latex->SetNDC();
    title_latex->SetTextSize(0.03);
    title_latex->SetTextAlign(31);
    title_latex->DrawLatex(0.95,0.96,title_right.c_str());
    title_latex->SetTextAlign(11);
    title_latex->DrawLatex(0.14,0.96,title_left.c_str());


    //Adjust the y-axis maximum to account for largest bin
    if (y_axis_log) {
      elements_[0].hist_ptr()->SetMaximum(max_bin_content*1.5);
    } else {
      elements_[0].hist_ptr()->SetMaximum(max_bin_content*1.1);
    }
    canv->Update();

    //Apply legend style options
    legend->SetBorderSize(1);
    legend->SetTextFont(42);
    legend->SetLineColor(0);
    legend->SetLineStyle(1);
    legend->SetLineWidth(1);
    legend->SetFillColor(0);
    legend->SetFillStyle(1001);
    legend->Draw();

    if (draw_ratio_hist) {
      canv->cd();
      lower->SetTopMargin(0.026);
      lower->SetBottomMargin(0.22);
      lower->Draw();
      lower->cd();
      std::vector<TH1F*> ratio_ele;
      ratio_ele.resize(ratios_.size());
      for (unsigned k = 0; k < ratios_.size(); ++k) {
        TH1F* num = 0;
        TH1F* den = 0;
        for (unsigned m = 0; m < elements_.size(); ++m) {
          if (elements_[m].name() == ratios_[k].hist_numerator())
            num = elements_[m].hist_ptr();
          if (elements_[m].name() == ratios_[k].hist_denominator())
            den = elements_[m].hist_ptr();
        }
        if (num && den) {
          ratio_ele[k] = (TH1F*)num->Clone();
          if (x_axis_min > 0 && x_axis_max > 0){
            ratio_ele[k]->GetXaxis()->SetRangeUser(x_axis_min,x_axis_max);
          }
          ratio_ele[k]->Divide(den);
          ratio_ele[k]->SetLineColor(ratios_[k].line_color());
          ratio_ele[k]->SetLineWidth(ratios_[k].line_width());
          ratio_ele[k]->SetLineStyle(ratios_[k].line_style());
          ratio_ele[k]->SetMarkerColor(ratios_[k].marker_color());
          ratio_ele[k]->SetMarkerSize(ratios_[k].marker_size());
          ratio_ele[k]->SetMarkerStyle(ratios_[k].marker_style());
          ratio_ele[k]->SetFillColor(ratios_[k].fill_color());
          ratio_ele[k]->SetFillStyle(ratios_[k].fill_style());
          if (k == 0)
          {
            ratio_ele[k]->GetXaxis()->SetLabelSize(0.07);
            ratio_ele[k]->GetXaxis()->SetTitleSize(0.1);
            ratio_ele[k]->GetYaxis()->SetTitleSize(0.1);
            ratio_ele[k]->GetYaxis()->SetTitleOffset(0.55);
            ratio_ele[k]->GetYaxis()->SetLabelSize(0.07);
            ratio_ele[k]->GetXaxis()->SetTitle(x_axis_title.c_str());
            if (custom_ratio_y_axis_range) {
              ratio_ele[k]->SetMaximum(ratio_y_axis_max);
              ratio_ele[k]->SetMinimum(ratio_y_axis_min);
            }
            ratio_ele[k]->GetYaxis()->SetTitle(ratio_y_axis_title.c_str());
            ratio_ele[k]->SetStats(false);
            if (draw_y_gridlines) lower->SetGrid(0,1);
            ratio_ele[k]->Draw();
          } else {
            ratio_ele[k]->Draw("SAME");

          }
        }
      }
    }

    canv->cd();

    if (y_axis_log) {
      if (draw_ratio_hist) {
        upper->SetLogy(true);
      } else {
        canv->SetLogy(true);
      }
    }
    canv->Update();
    canv->SaveAs(output_filename.c_str());
    delete legend;
    delete title_latex;
    delete upper;
    delete lower;
    delete canv;
    
    return 0;
  }

  void Plot::SetTdrStyle() {
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetCanvasColor(kWhite);
    gStyle->SetCanvasDefH(700); //Height of canvas
    gStyle->SetCanvasDefW(700); //Width of canvas
    gStyle->SetCanvasDefX(0);   //POsition on screen
    gStyle->SetCanvasDefY(0);

    // For the Pad:
    gStyle->SetPadBorderMode(0);
    // gStyle->SetPadBorderSize(Width_t size = 1);
    gStyle->SetPadColor(kWhite);
    gStyle->SetPadGridX(false);
    gStyle->SetPadGridY(false);
    gStyle->SetGridColor(0);
    gStyle->SetGridStyle(3);
    gStyle->SetGridWidth(1);

    // For the frame:
    gStyle->SetFrameBorderMode(0);
    gStyle->SetFrameBorderSize(0.1);
    gStyle->SetFrameFillColor(0);
    gStyle->SetFrameFillStyle(0);
    gStyle->SetFrameLineColor(1);
    gStyle->SetFrameLineStyle(1);
    gStyle->SetFrameLineWidth(0.1);

    // For the histo:
    // gStyle->SetHistFillColor(1);
    // gStyle->SetHistFillStyle(0);
    gStyle->SetHistLineColor(1);
    gStyle->SetHistLineStyle(0);
    gStyle->SetHistLineWidth(0.1);
    // gStyle->SetLegoInnerR(Float_t rad = 0.5);
    // gStyle->SetNumberContours(Int_t number = 20);

    gStyle->SetEndErrorSize(2);
    //gStyle->SetErrorMarker(20);
    gStyle->SetErrorX(0);

    gStyle->SetMarkerStyle(20);

    //For the fit/function:
    gStyle->SetOptFit(1);
    gStyle->SetFitFormat("5.4g");
    gStyle->SetFuncColor(2);
    gStyle->SetFuncStyle(1);
    gStyle->SetFuncWidth(1);

    //For the date:
    gStyle->SetOptDate(0);
    // gStyle->SetDateX(Float_t x = 0.01);
    // gStyle->SetDateY(Float_t y = 0.01);

    // For the statistics box:
    //  gStyle->SetOptFile(0);
    gStyle->SetOptStat(1);
    gStyle->SetOptStat("MRn");
    gStyle->SetStatColor(kWhite);
    gStyle->SetStatFont(42);
    gStyle->SetStatFontSize(0.04);///---> gStyle->SetStatFontSize(0.025);
    gStyle->SetStatTextColor(1);
    gStyle->SetStatFormat("6.4g");
    gStyle->SetStatBorderSize(1);
    gStyle->SetStatH(0.1);
    gStyle->SetStatW(0.2);///---> gStyle->SetStatW(0.15);

    // gStyle->SetStatStyle(Style_t style = 1001);
    // gStyle->SetStatX(Float_t x = 0);
    // gStyle->SetStatY(Float_t y = 0);

    // Margins:
    gStyle->SetPadTopMargin(0.05);
    gStyle->SetPadBottomMargin(0.10);
    gStyle->SetPadLeftMargin(0.14);
    gStyle->SetPadRightMargin(0.05);

    // For the Global title:

    gStyle->SetOptTitle(0);
    gStyle->SetTitleFont(42);
    gStyle->SetTitleColor(1);
    gStyle->SetTitleTextColor(1);
    gStyle->SetTitleFillColor(10);
    gStyle->SetTitleFontSize(0.05);
    // gStyle->SetTitleH(0); // Set the height of the title box
    // gStyle->SetTitleW(0); // Set the width of the title box
    // gStyle->SetTitleX(0); // Set the position of the title box
    // gStyle->SetTitleY(0.985); // Set the position of the title box
    // gStyle->SetTitleStyle(Style_t style = 1001);
    // gStyle->SetTitleBorderSize(2);

    // For the axis titles:

    gStyle->SetTitleColor(1, "XYZ");
    gStyle->SetTitleFont(42, "XYZ");
    gStyle->SetTitleSize(0.04, "XYZ");
    // gStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
    // gStyle->SetTitleYSize(Float_t size = 0.02);
    gStyle->SetTitleXOffset(0.9);
    gStyle->SetTitleYOffset(1.6);
    // gStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

    // For the axis labels:

    gStyle->SetLabelColor(1, "XYZ");
    gStyle->SetLabelFont(42, "XYZ");
    gStyle->SetLabelOffset(0.007, "XYZ");
    gStyle->SetLabelSize(0.03, "XYZ");

    // For the axis:

    gStyle->SetAxisColor(1, "XYZ");
    gStyle->SetStripDecimals(kTRUE);
    gStyle->SetTickLength(0.02, "XYZ");
    gStyle->SetNdivisions(510, "XYZ");
    gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
    gStyle->SetPadTickY(1);

    // Change for log plots:
    gStyle->SetOptLogx(0);
    gStyle->SetOptLogy(0);
    gStyle->SetOptLogz(0);

    // Postscript options:
    //  gStyle->SetPaperSize(20.,20.);
    // gStyle->SetLineScalePS(Float_t scale = 3);
    // gStyle->SetLineStyleString(Int_t i, const char* text);
    // gStyle->SetHeaderPS(const char* header);
    // gStyle->SetTitlePS(const char* pstitle);

    // gStyle->SetBarOffset(Float_t baroff = 0.5);
    // gStyle->SetBarWidth(Float_t barwidth = 0.5);
    // gStyle->SetPaintTextFormat(const char* format = "g");
    // gStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
    // gStyle->SetTimeOffset(Double_t toffset);
    // gStyle->SetHistMinimumZero(kTRUE);

    //   gStyle->cd();

    gROOT->ForceStyle();
  }
}
