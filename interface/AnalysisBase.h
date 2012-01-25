#ifndef __ajg_AnalysisBase__
#define __ajg_AnalysisBase__

#include <vector>
#include <string>
#include "TreeEvent.h"
#include "ModuleBase.h"
#include "boost/function.hpp"
#include "boost/bind.hpp"

namespace ajg {

	class AnalysisBase {

  private:
    std::string analysis_name_;
    std::vector<std::string> input_file_paths_;
    std::string tree_path_;
    std::string tree_name_;
    unsigned events_to_process_;
    unsigned events_processed_;
    std::vector<ajg::ModuleBase *> modules_;
    ajg::TreeEvent event_;

  public:
    AnalysisBase(   std::string const& analysis_name, 
                    std::vector<std::string> const& input,
                    std::string const& tree_path,
                    std::string const& tree_name,
                    unsigned const& events     );

    
    void AddModule(ajg::ModuleBase *module_ptr);
    inline std::string analysis_name() { return analysis_name_; }
    inline std::string tree_path() { return tree_path_; }
    inline std::string tree_name() { return tree_name_; }
    virtual ~AnalysisBase();
    virtual int RunAnalysis();
    virtual void DoEventSetup();
    virtual bool PostModule(int status);
 };
}

#endif