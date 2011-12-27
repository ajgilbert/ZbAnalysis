#include "RatioPlotElement.h"

namespace ajg {
  
  RatioPlotElement::RatioPlotElement(std::string name) {
    name_ = name;
    SetDefaults();
  }
  
  RatioPlotElement::RatioPlotElement(std::string name, 
      std::string num, std::string den) {
    name_ = name;
    SetDefaults();
    hist_numerator_ = num;
    hist_denominator_ = den;
  }

  void RatioPlotElement::SetDefaults() {
    hist_numerator_       = "";
    hist_denominator_     = "";
    draw_fill_            = true;
    fill_color_           = 0;
    fill_style_           = 0;
    draw_line_            = true;
    line_color_           = 1;
    line_width_           = 1;
    line_style_           = 1;
    draw_marker_          = false;
    marker_color_         = 2;
    marker_style_         = 21;
    marker_size_          = 0.8;
    draw_stat_error_y_    = true;
    draw_bin_width_x_     = 0;
  }







}
