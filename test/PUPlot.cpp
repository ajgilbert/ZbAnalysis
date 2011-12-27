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


int main(int argc, char* argv[]){

  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }

  ajg::Plot test_plot;
  test_plot.output_filename = "ninteractions.pdf";

  TFile mc_file("/data/Zb/DYJetsToLL/4_2_4/S4/TuneZ2/bFlav/MC_PU.root");
  TFile data_file("/data/Zb/DATA_PU_TEMP.root");
  
  ///
  ajg::TH1PlotElement mc_ele("mc",&mc_file,"/","MC_PU");
  mc_ele.set_legend_text("MC - DYJetsToLL");
  SetStyle(mc_ele,4);
  mc_ele.set_draw_normalised(true);
  ///
  ajg::TH1PlotElement data_ele("data",&data_file,"/","pileup2");
  data_ele.set_legend_text("Data");
  SetStyle(data_ele,2);
  data_ele.set_draw_normalised(true);
  ///
  
  test_plot.AddTH1PlotElement(data_ele);
  test_plot.AddTH1PlotElement(mc_ele);

  test_plot.x_axis_title = "Number of Interactions";
  test_plot.y_axis_title = "Events (arb. units)";
  test_plot.x_axis_min = -0.5;
  test_plot.x_axis_max = 24.5;
  test_plot.y_axis_log = false;
  test_plot.ratio_y_axis_title = "Data/MC Ratio";
  
  test_plot.draw_ratio_hist = true;
  ajg::RatioPlotElement ratio("ratio","data","mc");
  ratio.set_marker_color(1);
  
  test_plot.AddRatioPlotElement(ratio);
  //test_plot.title_left = "Madgraph vs. aMC@NLO";
  test_plot.GeneratePlot();


  return 0;
}
