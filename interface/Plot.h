#ifndef __ajg_Plot__
#define __ajg_Plot__

#include <vector>
#include <string>
#include <map>
#include "TFile.h"
#include "TH1F.h"
#include "TH1PlotElement.h"
#include "RatioPlotElement.h"

namespace ajg{

  class Plot {
    
    public:
      Plot(){
        draw_ratio_hist = false;
        custom_x_axis_range = false;
        x_axis_min = -1;
        x_axis_max = -1;
        y_axis_log = false;
        custom_ratio_y_axis_range = true;
        ratio_y_axis_min = 0;
        ratio_y_axis_max = 2;
        draw_y_gridlines = true;
        legend_height = 0.05;

      }
      int GeneratePlot();
      bool AddTH1PlotElement(ajg::TH1PlotElement element);
      bool AddRatioPlotElement(ajg::RatioPlotElement element);
      void SetRatioYaxisRange(double min, double max);
      void SetXaxisRange(double min, double max);

      //Customise plot titles
      std::string title_left;
      std::string title_right;
      
      //Customise ratio plot
      bool draw_ratio_hist;
      bool draw_y_gridlines;
      std::string ratio_y_axis_title;
      bool custom_ratio_y_axis_range;
      double ratio_y_axis_min;
      double ratio_y_axis_max;

      //Customise x-axis
      std::string x_axis_title;
      bool custom_x_axis_range;
      double x_axis_min;
      double x_axis_max;
      
      //Customise y-axis
      std::string y_axis_title;
      bool y_axis_log;

      //Customise legend
      double legend_height;

      std::string output_filename;
      
    private:
      std::vector<ajg::TH1PlotElement> elements_;
      std::vector<ajg::RatioPlotElement> ratios_;
      std::map<std::string,ajg::TH1PlotElement> element_map_;
      std::vector<std::string> output_formats_;
      void SetTdrStyle();
  };


}

#endif
