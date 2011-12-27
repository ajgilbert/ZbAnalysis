#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Plot.h"


using namespace std;

void SetStyle(ajg::TH1PlotElement & ele, unsigned color) {
  ele.set_marker_color(color);
  ele.set_line_color(color);
  ele.set_draw_fill(true);
  ele.set_draw_stat_error_y(true);
  return;
}

void SetStyle(ajg::RatioPlotElement & ele, unsigned color) {
  ele.set_marker_color(color);
  ele.set_line_color(color);
  ele.set_draw_stat_error_y(true);
  return;
}


int main(int argc, char* argv[]){

  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }


  ajg::Plot test_plot;
  test_plot.output_filename = "initial_quark_pt.pdf";
  std::string hist_name = "pt_initial_quark";

  TFile amcatnlo_file("amcatnlo_ee_gj.root");
  TFile madgraph_file("madgraph_ee_gj.root");
  TFile madgraph_pj_file("madgraph_ee_pj.root");
  TFile amcatnlo_pj_file("amcatnlo_ee_pj.root");
  TFile mcfm_file("mcfmPlotter.root");
  
  ///
  ajg::TH1PlotElement amcatnlo_ele("amcatnlo",&amcatnlo_file,"/",hist_name);
  amcatnlo_ele.set_scale_factor(16.1/129807);
  amcatnlo_ele.set_legend_text("aMC@NLO");
  amcatnlo_ele.set_rebin_factor(5);
  SetStyle(amcatnlo_ele,2);
  ///
  ajg::TH1PlotElement madgraph_ele("madgraph",&madgraph_file,"/",hist_name);
  madgraph_ele.set_scale_factor(135.4/300000.);
  madgraph_ele.set_legend_text("Madgraph");
  madgraph_ele.set_rebin_factor(5);
  SetStyle(madgraph_ele,9);
  ///
  ajg::TH1PlotElement madgraph_pj_ele("madgraph_pj",&madgraph_pj_file,"/",hist_name);
  madgraph_pj_ele.set_scale_factor(135.4/300000.);
  madgraph_pj_ele.set_legend_text("Madgraph (Parton Jet)");
  madgraph_pj_ele.set_rebin_factor(5);
  SetStyle(madgraph_pj_ele,38);
  /*
  ///
  ajg::TH1PlotElement amcatnlo_pj_ele("amcatnlo_pj",&amcatnlo_pj_file,"/",hist_name);
  amcatnlo_pj_ele.set_scale_factor(16.1/129807);
  amcatnlo_pj_ele.set_legend_text("aMC@NLO (Parton Jet)");
  amcatnlo_pj_ele.set_rebin_factor(5);
  SetStyle(amcatnlo_pj_ele,46);
  //
  */
  ajg::TH1PlotElement mcfm_ele("mcfm",&mcfm_file,"/","pT_MCFM");
  mcfm_ele.set_scale_factor(1/1000.);
  mcfm_ele.set_legend_text("MCFM");
  mcfm_ele.set_rebin_factor(5);
  SetStyle(mcfm_ele,11);
  ///
  
  test_plot.AddTH1PlotElement(amcatnlo_ele);
  //test_plot.AddTH1PlotElement(amcatnlo_pj_ele);
  test_plot.AddTH1PlotElement(madgraph_ele);
  test_plot.AddTH1PlotElement(madgraph_pj_ele);
  test_plot.AddTH1PlotElement(mcfm_ele);

  //test_plot.x_axis_title = "#eta";
  test_plot.x_axis_title = "p_{T} (GeV)";
  test_plot.y_axis_title = "Events";
  test_plot.x_axis_min = 5;
  test_plot.x_axis_max = 120;
  test_plot.y_axis_log = true;
  test_plot.ratio_y_axis_title = "MC/MCFM Ratio";
  

  test_plot.draw_ratio_hist = true;
  ajg::RatioPlotElement amcatnlo_ratio("amcatnlo_ratio","amcatnlo","mcfm");
  SetStyle(amcatnlo_ratio,2);
  ajg::RatioPlotElement mg_ratio("mg_ratio","madgraph","mcfm");
  SetStyle(mg_ratio,9);
  ajg::RatioPlotElement mg_pj_ratio("mg_pj_ratio","madgraph_pj","mcfm");
  SetStyle(mg_pj_ratio,38);
  /*
  ajg::RatioPlotElement amcatnlo_pj_ratio("amcatnlo_pj_ratio","amcatnlo_pj","mcfm");
  SetStyle(amcatnlo_pj_ratio,46);
  */
  test_plot.AddRatioPlotElement(mg_pj_ratio);
  test_plot.AddRatioPlotElement(mg_ratio);
  test_plot.AddRatioPlotElement(amcatnlo_ratio);
  //test_plot.AddRatioPlotElement(amcatnlo_pj_ratio);
  test_plot.title_left = "Madgraph vs. aMC@NLO";
  test_plot.GeneratePlot();

  /*
  //reco_gen_jet_resp_25_35
  ajg::Plot reco_gen_jet_resp_25_35_plot;
  reco_gen_jet_resp_25_35_plot.output_filename = "reco_gen_jet_resp_25_35.pdf";
  madgraph_ele.hist_name = "reco_gen_jet_resp_25_35";
  madgraph_ele.rebin = 2;
  madgraph_ele.draw_normalised = true;
  amcatnlo_ele.hist_name = "reco_gen_jet_resp_25_35";
  amcatnlo_ele.rebin = 2;
  amcatnlo_ele.draw_normalised = true;
  reco_gen_jet_resp_25_35_plot.x_axis_title = "Reco Jet p_{T} / Gen Jet p_{T} ";
  reco_gen_jet_resp_25_35_plot.y_axis_title = "Events";
  reco_gen_jet_resp_25_35_plot.y_axis_log = false;
  reco_gen_jet_resp_25_35_plot.ratio_y_axis_title = "aMC/MG";
  //reco_gen_jet_resp_25_35_plot.draw_ratio_hist = true;
  reco_gen_jet_resp_25_35_plot.AddTH1PlotElement(madgraph_ele);
  reco_gen_jet_resp_25_35_plot.AddTH1PlotElement(amcatnlo_ele);
  //ajg::RatioPlotElement am_ratio("am_ratio","amcatnlo","madgraph");
  //SetStyle(am_ratio,1);
  //reco_gen_jet_resp_25_35_plot.AddRatioPlotElement(am_ratio);
  reco_gen_jet_resp_25_35_plot.title_left = "Madgraph vs. aMC@NLO";
  reco_gen_jet_resp_25_35_plot.title_right = "Gen Jet: 25 < p_{T} < 35 GeV";
  reco_gen_jet_resp_25_35_plot.GeneratePlot();

  */
  
  
  
  
  return 0;
}
