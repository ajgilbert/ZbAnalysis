#include "LatexTable.hh"
#include "YieldStats.hh"
#include <stdarg.h>
#include <iostream>

namespace HbbAnalysis {//namespace

  void LatexTable::AddYieldStats(std::string name, YieldStats & yieldStats) {
    yieldStatsNames_.push_back(name);
    if (yieldStatsMap_.count(name) == 0) {
      yieldStatsMap_[name] = &(yieldStats);
    } else {
      std::cout << "Warning: Attempt to add a YieldStats with name \"" << name << "\" failed.  A YieldMap with this name has already been added." << std::endl;
    }
  }

  void LatexTable::CombineSplitsByName(std::vector<std::string> splitNames){
    selectedSplits_ = splitNames;
    splitRestricted_ = true;
  }

  void LatexTable::CombineAllSplits(){
    splitRestricted_ = false;
  }

  void LatexTable::RestrictToRun(unsigned run){
    runRestricted_ = true;
    startRun_ = run;
    endRun_ = run;
  }
  
  void LatexTable::RestrictToRunRange(unsigned startRun, unsigned endRun){
    runRestricted_ = true;
    startRun_ = startRun;
    endRun_ = endRun;
  }

  


  void LatexTable::MakeTable(){ 
    
    unsigned nSamples = yieldStatsNames_.size();

    std::vector<std::string> stepNames;  
    if (nSamples > 0) {
      stepNames = yieldStatsMap_[yieldStatsNames_[0]]->GetStepNames();
    }
  
    //Print start boilerplate:
    std::cout << "\\begin{table}" << std::endl;
    std::cout << "{\\tiny" << std::endl;
    std::cout << "\\caption{DUMMY\\_CAPTION}" << std::endl;
    std::cout << "\\begin{tabular}{|l";
    for (unsigned i = 0; i < nSamples; ++i) std::cout << "|c";
    std::cout << "|}" << std::endl;
    std::cout << "\\hline" << std::endl;
    std::cout << "Step "; 
    for (unsigned i = 0; i < nSamples; ++i) {
      std::cout << "& " << yieldStatsNames_[i] << " ";
    }
    std::cout << "\\\\" << std::endl;
    std::cout << "\\hline" << std::endl;

    for (unsigned i = 0; i < stepNames.size(); ++i){

      std::cout << stepNames[i] << " ";
      for (unsigned j = 0; j < nSamples; ++j) {
        double count = 0.0;
        if (runRestricted_) {
          if (splitRestricted_) {
            count = yieldStatsMap_[yieldStatsNames_[j]]->CalculateYield(stepNames[i], startRun_, endRun_, selectedSplits_);
          } else {
            count = yieldStatsMap_[yieldStatsNames_[j]]->CalculateYield(stepNames[i], startRun_, endRun_);
          }
        } else {
          if (splitRestricted_){
            count = yieldStatsMap_[yieldStatsNames_[j]]->CalculateYield(stepNames[i], selectedSplits_);
          } else {
            count = yieldStatsMap_[yieldStatsNames_[j]]->CalculateYield(stepNames[i]);
          }
        }
        
        std::cout << "& $" << count << " \\pm 0.0$ ";
      }
      std::cout << "\\\\" << std::endl;

    }
    std::cout << "\\hline" << std::endl;

    //Print end boilerplate:
    std::cout << "\\end{tabular}" << std::endl;
    std::cout << "}" << std::endl;
    std::cout << "\\end{table}" << std::endl;

    

  }



}//namespace
