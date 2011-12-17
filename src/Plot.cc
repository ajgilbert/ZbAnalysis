
#include "Plot.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TPaveStats.h"
#include "TPad.h"
#include <vector>
#include <iostream>

namespace ajg{



      bool Plot::AddTH1PlotElement(ajg::TH1PlotElement element) {
       if (element_map_.count(element.element_name) == 0) {
         elements_.push_back(element);
         element_map_[element.element_name] = element;
         return true;
       } else {
         std::cerr << "Error: Cannot add TH1PlotElement with name \"" <<
           element.element_name << "\", name already in use." << std::endl;
         return false;
       }
      }
      
      bool Plot::AddRatioPlotElement(ajg::RatioPlotElement element) {
         ratios_.push_back(element);
         return true;
      }
      
      int Plot::GeneratePlot() {
        SetTdrStyle();

        TLegend leg(0.60,0.80,0.90,0.90,NULL,"brNDC");
        unsigned n_in_legend = 0;

        unsigned n_elements = elements_.size();
        std::vector<TH1F*> histos;
        histos.resize(n_elements);
        for (unsigned i = 0; i < n_elements; ++i) {
          TH1PlotElement & ele = elements_[i];
          ele.source_file->cd();
          gDirectory->cd(ele.hist_path.c_str());
          histos[i] = dynamic_cast<TH1F*>(gDirectory->Get(ele.hist_name.c_str()));
        }

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
        unsigned max_bin_hist = 0;
        for (unsigned i = 0; i < n_elements; ++i) {
          TH1PlotElement & ele = elements_[i];

          //This is a fix for histograms with negative bin content
          //for which Sumw2 has not already been called
          for (int j = 0; j < histos[i]->GetNbinsX(); ++j) {
            if (histos[i]->GetBinContent(j) < 0) 
              histos[i]->SetBinContent(j,0.0);
          }
          histos[i]->Sumw2();
          if (!ele.draw_normalised) {
            histos[i]->Scale(ele.scale_factor);
          } else {
            histos[i]->Scale(1./histos[i]->Integral());
          }
          
          histos[i]->Rebin(ele.rebin);
          histos[i]->SetLineColor(ele.line_color);
          histos[i]->SetLineWidth(ele.line_width);
          histos[i]->SetLineStyle(ele.line_style);
          histos[i]->SetMarkerColor(ele.marker_color);
          histos[i]->SetMarkerSize(ele.marker_size);
          histos[i]->SetMarkerStyle(ele.marker_style);
          histos[i]->SetFillColor(ele.fill_color);
          histos[i]->SetFillStyle(ele.fill_style);
          histos[i]->SetStats(true);
          
          if (ele.legend_text != ""){
            ++n_in_legend;
            std::string leg_options = "";
            if (ele.draw_hist) leg_options += "fl";
            if (ele.draw_marker || ele.draw_stat_error_y) leg_options += "p";
            leg.AddEntry(histos[i],ele.legend_text.c_str(),leg_options.c_str());
          }
          std::string draw_options = "";
          if (ele.draw_hist) draw_options += "HIST";
          if (ele.draw_marker) draw_options += "P";
          if (ele.draw_stat_error_y) draw_options += "E1";


          for (int j = 0; j < histos[i]->GetNbinsX(); ++j) {

            bool bin_in_range = true;
            if (x_axis_min > 0 && x_axis_max > 0) {
              if ((histos[i]->GetBinLowEdge(j) < x_axis_min)
                  || (histos[i]->GetXaxis()->GetBinUpEdge(j) > x_axis_max))
                bin_in_range = false;
            }

            if (bin_in_range) {
              if (histos[i]->GetBinContent(j) > max_bin_content) {
                max_bin_content = histos[i]->GetBinContent(j);
                max_bin_hist = i;
              }
            }
          }
       

          if (i == 0) {
            histos[i]->GetXaxis()->SetTitle(x_axis_title.c_str());
              if (x_axis_min > 0 && x_axis_max > 0){
                histos[i]->GetXaxis()->SetRangeUser(x_axis_min,x_axis_max);
              }
            //histos[i]->GetXaxis()->SetLabelSize(0.0);
            //histos[i]->GetXaxis()->SetTitleSize(0.0);
            histos[i]->GetYaxis()->SetTitle(y_axis_title.c_str());
            histos[i]->SetName("Madgraph");
            histos[i]->Draw(draw_options.c_str());
            canv->Update();
            TPaveStats *st = (TPaveStats*)histos[i]->FindObject("stats");
            st->SetX1NDC(0.65); 
            st->SetX2NDC(0.89); 
            st->SetY1NDC(0.6); 
            st->SetY2NDC(0.75); 
          } else {
            histos[i]->SetName("aMC@NLO");
            histos[i]->Draw(("SAMES"+draw_options).c_str());
            canv->Update();
            TPaveStats *st = (TPaveStats*)histos[i]->FindObject("stats");
            st->SetX1NDC(0.65); 
            st->SetX2NDC(0.89); 
            st->SetY1NDC(0.45); 
            st->SetY2NDC(0.6); 
          }
          


        }
        
        TLatex *title_latex = new TLatex();
        title_latex->SetNDC();
        title_latex->SetTextSize(0.03);
        title_latex->SetTextAlign(31);
        title_latex->DrawLatex(0.95,0.96,title_right.c_str());
        title_latex->SetTextAlign(11);
        title_latex->DrawLatex(0.16,0.96,title_left.c_str());


        //canv->Draw();
        if (y_axis_log) {
          histos[0]->SetMaximum(max_bin_content*1.5);
        } else {
          histos[0]->SetMaximum(max_bin_content*1.1);
        }

        canv->Update();
        
        leg.SetBorderSize(1);
        leg.SetTextFont(42);
        leg.SetLineColor(0);
        leg.SetLineStyle(1);
        leg.SetLineWidth(1);
        leg.SetFillColor(0);
        leg.SetFillStyle(1001);
        leg.Draw();

        if (draw_ratio_hist) {
          canv->cd();
          lower->SetTopMargin(0.02);
          lower->SetBottomMargin(0.23);
          lower->Draw();
          lower->cd();
          std::vector<TH1F*> ratio_ele;
          ratio_ele.resize(ratios_.size());
          for (unsigned k = 0; k < ratios_.size(); ++k) {
            TH1F* num = 0;
            TH1F* den = 0;
            for (unsigned m = 0; m < elements_.size(); ++m) {
              if (elements_[m].element_name == ratios_[k].hist_numerator)
                num = histos[m];
              if (elements_[m].element_name == ratios_[k].hist_denominator)
                den = histos[m];
            }
            if (num && den) {
              ratio_ele[k] = (TH1F*)num->Clone();
              if (x_axis_min > 0 && x_axis_max > 0){
                ratio_ele[k]->GetXaxis()->SetRangeUser(x_axis_min,x_axis_max);
              }
              ratio_ele[k]->Divide(den);
              ratio_ele[k]->SetLineColor(ratios_[k].line_color);
              ratio_ele[k]->SetLineWidth(ratios_[k].line_width);
              ratio_ele[k]->SetLineStyle(ratios_[k].line_style);
              ratio_ele[k]->SetMarkerColor(ratios_[k].marker_color);
              ratio_ele[k]->SetMarkerSize(ratios_[k].marker_size);
              ratio_ele[k]->SetMarkerStyle(ratios_[k].marker_style);
              ratio_ele[k]->SetFillColor(ratios_[k].fill_color);
              ratio_ele[k]->SetFillStyle(ratios_[k].fill_style);
              if (k == 0)
              {
                ratio_ele[k]->GetXaxis()->SetLabelSize(0.07);
                ratio_ele[k]->GetXaxis()->SetTitleSize(0.1);
                ratio_ele[k]->GetYaxis()->SetTitleSize(0.1);
                ratio_ele[k]->GetYaxis()->SetTitleOffset(0.55);
                ratio_ele[k]->GetYaxis()->SetLabelSize(0.07);
                ratio_ele[k]->GetXaxis()->SetTitle(x_axis_title.c_str());
                ratio_ele[k]->SetMaximum(6);
                ratio_ele[k]->SetMinimum(0);
                ratio_ele[k]->GetYaxis()->SetTitle(ratio_y_axis_title.c_str());
                ratio_ele[k]->SetStats(false);
                lower->SetGrid(0,1);
                ratio_ele[k]->Draw();
              } else {
                ratio_ele[k]->Draw("SAME");

              }
            }
          }
        }

        canv->cd();

        if (y_axis_log) upper->SetLogy(true);
        canv->Update();
        canv->SaveAs(output_filename.c_str());

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
        gStyle->SetPadBottomMargin(0.13);
        gStyle->SetPadLeftMargin(0.16);
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
