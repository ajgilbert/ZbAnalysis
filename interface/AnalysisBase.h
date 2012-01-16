#ifndef __ajg_AnalysisBase__
#define __ajg_AnalysisBase__

#include <vector>
#include <string>
#include "TreeEvent.h"
#include "boost/function.hpp"
#include "boost/bind.hpp"

namespace ajg {

	class AnalysisBase {


  private:
    std::vector<std::string> input_file_paths_;
    unsigned events_to_process_;
    unsigned events_processed_;
    std::vector< boost::function<int (ajg::TreeEvent)> > modules_;




  public:
    virtual int RunAnalysis();





 };
}

#endif