#ifndef __ajg_Plot__
#define __ajg_Plot__

#include <vector>
#include <string>
#include <map>
#include "TFile.h"
#include "TH1F.h"

namespace ajg{

  struct TH1PlotElement;
  struct RatioPlotElement;

  class Plot {
    
    public:
      Plot(){
        draw_ratio_hist = false;
        x_axis_min = -1;
        x_axis_max = 1;
        y_axis_log = false;
      }
      int GeneratePlot();
      bool AddTH1PlotElement(ajg::TH1PlotElement element);
      bool AddRatioPlotElement(ajg::RatioPlotElement element);

      std::string x_axis_title;
      std::string y_axis_title;
      std::string ratio_y_axis_title;
      std::string title_left;
      std::string title_right;
      bool draw_ratio_hist;
      bool y_axis_log;
      double x_axis_min;
      double x_axis_max;
      std::string output_filename;

      

    private:
      std::vector<ajg::TH1PlotElement> elements_;
      std::vector<ajg::RatioPlotElement> ratios_;
      std::map<std::string,ajg::TH1PlotElement> element_map_;
      std::vector<std::string> output_formats_;
      void SetTdrStyle();




  };


  struct TH1PlotElement {
    std::string element_name;
    TFile* source_file;
    std::string hist_path;
    std::string hist_name;
    std::string legend_text;
    bool draw_hist;
    int line_color;
    int line_width;
    int line_style;
    int fill_color;
    int fill_style;
    bool draw_marker;
    int marker_color;
    int marker_style;
    double marker_size;
    bool draw_stat_error_y;
    bool draw_bin_width_x;
    double scale_factor;
    bool draw_normalised;
    unsigned rebin;
    
    TH1PlotElement() {
      element_name = "no_name";
      SetDefaults();
    }

    TH1PlotElement(std::string name) {
      element_name = name;
      SetDefaults();
    }

    TH1PlotElement(std::string name, TFile* file, std::string hist, 
        std::string h_name, std::string legend = "") {
      element_name = name;
      SetDefaults();
      source_file = file;
      hist_path = hist;
      hist_name = h_name;
      legend_text = legend;
    }

    void SetDefaults() {
      source_file = 0;
      hist_path = "";
      legend_text = "";
      draw_hist = true;
      line_color = 2;
      line_width = 1;
      line_style = 1;
      fill_color = 0;
      fill_style = 0;
      draw_marker = false;
      marker_color = 2;
      marker_style = 21;
      marker_size = 0.8;
      draw_stat_error_y = true;
      draw_bin_width_x = 0;
      scale_factor = 1.0;
      draw_normalised = false;
      rebin = 1;
    }

  };


  struct RatioPlotElement {
    std::string element_name;
    std::string hist_numerator;
    std::string hist_denominator;
    bool draw_hist;
    int line_color;
    int line_width;
    int line_style;
    int fill_color;
    int fill_style;
    bool draw_marker;
    int marker_color;
    int marker_style;
    double marker_size;
    bool draw_stat_error_y;
    bool draw_bin_width_x;
    unsigned rebin;
    
    RatioPlotElement() {
      element_name = "no_name";
      SetDefaults();
    }

    RatioPlotElement(std::string name) {
      element_name = name;
      SetDefaults();
    }

    RatioPlotElement(std::string name, std::string num, std::string den) {
      element_name = name;
      SetDefaults();
      hist_numerator = num;
      hist_denominator = den;
    }

    void SetDefaults() {
      hist_numerator = "";
      hist_denominator = "";
      draw_hist = true;
      line_color = 2;
      line_width = 1;
      line_style = 1;
      fill_color = 0;
      fill_style = 0;
      draw_marker = false;
      marker_color = 2;
      marker_style = 21;
      marker_size = 0.8;
      draw_stat_error_y = true;
      draw_bin_width_x = 0;
      rebin = 1;
    }

  };

}

#endif
