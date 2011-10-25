#include "YieldStats.hh"
#include "MiscFunctions.hh"
#include <stdarg.h>
#include <iostream>

namespace HbbAnalysis {//namespace

  YieldStats::YieldStats(std::string sampleName, std::string yieldName) {
    sampleName_ = sampleName;
    yieldName_ = yieldName;
  }
  
  //Setters
  void YieldStats::SetSampleName(std::string const& sampleName) {
    sampleName_ = sampleName;
  }
  void YieldStats::SetYieldName(std::string const& yieldName) {
    yieldName_ = yieldName;
  }
    
  void YieldStats::SetStepNames(std::vector<std::string> const& stepNames) {
    stepNames_ = stepNames;
    for (unsigned i = 0; i < stepNames_.size(); ++i){
      stepIndexMap_[stepNames_[i]] = i;
    }
  }

  void YieldStats::SetBinNames(std::vector<std::string> const& binNames) {
    binNames_ = binNames;
    for (unsigned i = 0; i < binNames_.size(); ++i){
      binIndexMap_[binNames_[i]] = i;
    }
  }
  
  //Getters
  std::vector<std::string> YieldStats::GetStepNames() const {
    return stepNames_;
  }

  std::vector<std::string> YieldStats::GetBinNames() const {
    return binNames_;
  }
  
  void YieldStats::IncrementCount(unsigned run, unsigned binIndex, unsigned stepIndex,  double value){

    //Check if map already has key "run", if not, construct nested vector of appropriate size
    if (runIndexMap_.count(run) == 0){
      runIndexMap_[run] = yieldVector_.size();
      yieldVector_.resize(yieldVector_.size() + (binNames_.size()*stepNames_.size()));
    }
    at(runIndexMap_[run], binIndex, stepIndex) += value;
  }
  
  void YieldStats::IncrementCount(unsigned run, std::string binName, std::string stepName, double value)
  {
    if (stepIndexMap_.count(stepName) == 0 || binIndexMap_.count(binName) == 0){
      std::cerr << 
        "Warning: Attempt to increment count with unrecognised string" << std::endl;
      return;
    }
    IncrementCount(run, binIndexMap_[binName], stepIndexMap_[stepName], value);
  }

  double & YieldStats::at(unsigned runIndex, unsigned binIndex, unsigned stepIndex) {
    try {
      return yieldVector_.at(runIndex + binIndex + (stepIndex*binNames_.size())); 
    } 
    catch (std::exception& e)
    {
      std::cerr << "Exception caught attempting to access invalid yield: " << e.what() << std::endl;
      throw;
    }
  };

  double YieldStats::at(unsigned runIndex, unsigned binIndex, unsigned stepIndex) const {
    try {
      return yieldVector_.at(runIndex + binIndex + (stepIndex*binNames_.size())); 
    } 
    catch (std::exception& e)
    {
      std::cerr << "Exception caught attempting to access invalid yield: " << e.what() << std::endl;
      return 0;
    }
  }

  double YieldStats::CalculateYield(std::string stepName) const {
    return CalculateYield(stepName, 0, std::numeric_limits<unsigned>::max(), binNames_);
  }
  
  double YieldStats::CalculateYield(std::string stepName, unsigned minRun, unsigned maxRun) const {
    return CalculateYield(stepName, minRun, maxRun, binNames_);
  }
  
  double YieldStats::CalculateYield(std::string stepName, std::vector<std::string> binNames) const {
    return CalculateYield(stepName, 0, std::numeric_limits<unsigned>::max(), binNames);
  }
  
  double YieldStats::CalculateYield(std::string stepName, 
                                    unsigned minRun, unsigned maxRun, 
                                    std::vector<std::string> binNames) const {
    double count = 0.0;
    std::map<unsigned, unsigned>::const_iterator iter;
    for (iter = runIndexMap_.begin(); iter != runIndexMap_.end(); ++iter){
      if (iter->first < minRun || iter->first > maxRun) continue;
      for (unsigned j = 0; j < binNames.size(); ++j){
        count += at(iter->second, binIndexMap_.find(binNames[j])->second, stepIndexMap_.find(stepName)->second);
      }
    }
    return count;
  }


  void YieldStats::Print() const {
    for (std::map<unsigned,unsigned>::const_iterator it = runIndexMap_.begin();
        it != runIndexMap_.end();
        ++it){
      std::cout << "---------------------" << std::endl;
      std::cout << "Run: " << it->first << std::endl;
      std::cout << "---------------------" << std::endl;
      for (unsigned i = 0; i < stepNames_.size(); ++i){
        for (unsigned k = 0; k < binNames_.size(); ++k){
        std::cout << at(it->second, k, i) << "\t";
        }
        std::cout << std::endl;
      }
    }
    std::cout << std::endl;
  }


}//namespace
