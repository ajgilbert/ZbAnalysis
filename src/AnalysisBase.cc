#include "AnalysisBase.h"
#include "UserCode/HbbAnalysis/interface/HbbEvent.hh"
#include <algorithm>
#include "TFile.h"
#include "TTree.h"

namespace ajg {

  AnalysisBase::AnalysisBase(   std::string const& analysis_name, 
                                std::vector<std::string> const& input,
                                std::string const& tree_path,
                                std::string const& tree_name,
                                unsigned const& events  ) {
    input_file_paths_ = input;
    events_to_process_ = events;
    analysis_name_ = analysis_name;
    tree_path_ = tree_path;
    tree_name_ = tree_name;
    events_processed_ = 0;
  }

  AnalysisBase::~AnalysisBase() {
      ;
  }

  void AnalysisBase::AddModule(ajg::ModuleBase *module_ptr) {
    modules_.push_back(module_ptr);
  }

  void AnalysisBase::DoEventSetup() {
    event_.AutoAddBranch<HbbAnalysis::HbbEvent>("HbbEvent");
  }

  bool AnalysisBase::PostModule(int status) {
    if (status > 0) { 
      return false;
    } else {
      return true;
    }
  }

  int AnalysisBase::RunAnalysis() {
    TFile *file_ptr = NULL;
    TTree *tree_ptr = NULL;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Module List" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::for_each(modules_.begin(), modules_.end(), boost::bind(&ModuleBase::PrintInfo,_1));
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Pre-Analysis Module Output" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::for_each(modules_.begin(), modules_.end(), boost::bind(&ModuleBase::PreAnalysis,_1));
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Beginning Main Analysis Sequence" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    for (unsigned file = 0; file < input_file_paths_.size(); ++file) {
        //Stop looping through files if user-specified events have
        //been processed
        if (events_processed_ == events_to_process_) break;

        file_ptr = new TFile(input_file_paths_[file].c_str());
        if (!file_ptr) {
          std::cerr << "Warning: Unable to open file \"" << input_file_paths_[file] <<
          "\"" << std::endl;
          continue;
        }
        gDirectory->Cd(tree_path_.c_str());
        tree_ptr = dynamic_cast<TTree*>(gDirectory->Get(tree_name_.c_str()));
        if (!tree_ptr) {
          std::cerr << "Warning: Unable to find TTree \"" << tree_name_ <<
          "\" in file \"" << input_file_paths_[file] << "\"" << std::endl;
          continue;
        }
        unsigned tree_events = tree_ptr->GetEntries();
        event_.SetTree(tree_ptr);
        DoEventSetup();
        for (unsigned evt = 0; evt < tree_events; ++evt) {
          event_.SetEvent(evt);
          for (unsigned module = 0; module < modules_.size(); ++module) {
            int status = modules_[module]->Execute(&event_);
            if (!PostModule(status)) break;
          }
          ++events_processed_;
          if (events_processed_ == events_to_process_) break;
        }
        file_ptr->Close();
        delete file_ptr;
    }
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Post-Analysis Module Output" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::for_each(modules_.begin(), modules_.end(), boost::bind(&ModuleBase::PostAnalysis,_1));
   return 0; 
  }
}