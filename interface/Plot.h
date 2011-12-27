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


}

#endif
