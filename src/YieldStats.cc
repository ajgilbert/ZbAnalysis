#include "YieldStats.hh"
#include <stdarg.h>
#include <iostream>

namespace HbbAnalysis {//namespace

  YieldStats::YieldStats(std::string sampleName, std::string yieldName){
    sampleName_ = sampleName;
    yieldName_ = yieldName;
  }
    
  void YieldStats::InitialiseStepNames(std::vector<std::string> const& stepNames){
    stepNames_ = stepNames;
    BuildStepIndexMap();
  }

  void YieldStats::InitialiseStepNames(unsigned numArgs, ... ){
    stepNames_.clear();
    va_list listPointer;
    va_start(listPointer, numArgs);
    for (unsigned i = 0; i < numArgs; ++i){
      stepNames_.push_back(std::string(va_arg(listPointer,char*))); 
    }
    BuildStepIndexMap();
  }

  void YieldStats::InitialiseSplitNames(std::vector<std::string> const& splitNames){
    splitNames_ = splitNames;
    BuildSplitIndexMap();
  }

  void YieldStats::InitialiseSplitNames(unsigned numArgs, ... ){
    splitNames_.clear();
    va_list listPointer;
    va_start(listPointer, numArgs);
    for (unsigned i = 0; i < numArgs; ++i){
      splitNames_.push_back(std::string(va_arg(listPointer,char*))); 
    }
    BuildSplitIndexMap();
  }

  void YieldStats::BuildStepIndexMap(){
    for (unsigned i = 0; i < stepNames_.size(); ++i){
      stepIndexMap_[stepNames_[i]] = i;
    }
  }
  
  void YieldStats::BuildSplitIndexMap(){
    for (unsigned i = 0; i < splitNames_.size(); ++i){
      splitIndexMap_[splitNames_[i]] = i;
    }
  }

  void YieldStats::IncrementCount(unsigned run, std::string stepName, std::string splitName, double value)
  {
    if (stepIndexMap_.count(stepName) == 0 || splitIndexMap_.count(splitName) == 0){
      std::cerr << "Warning in method YieldStats::IncrementCount: attempt to increase count with unrecognised string, no increase will occur" << std::endl;
      return;
    }
    IncrementCount(run, stepIndexMap_[stepName], splitIndexMap_[splitName], value);
  }

  void YieldStats::IncrementCount(unsigned run, unsigned stepIndex, unsigned splitIndex,  double value){

    //Check if map already has key "run", if not, construct nested vector of appropriate size
    if (runIndexMap_.count(run) == 0){
      runIndexMap_[run] = yieldVector_.size();
      yieldVector_.resize(yieldVector_.size() + (stepNames_.size()*splitNames_.size()));
    }
    try{
      yieldVector_.at(runIndexMap_[run] + stepIndex + splitIndex*stepNames_.size()) += value;
    } 
    catch(std::exception& e)
    {
      std::cerr << "Exception caught in method YieldStats::IncrementCount: " << e.what() << std::endl;
    }
  }

  std::vector<std::string> YieldStats::GetStepNames() {
    return stepNames_;
  }

  std::vector<std::string> YieldStats::GetSplitNames() {
    return splitNames_;
  }

  double YieldStats::GetYieldAllRunsAllSplits(std::string stepName){
    double count = 0.0;
    std::map<unsigned, unsigned>::const_iterator iter;
    for (iter = runIndexMap_.begin(); iter != runIndexMap_.end(); ++iter){
      for (unsigned j = 0; j < splitNames_.size(); ++j){
        count += GetYield(iter->second, stepIndexMap_[stepName], j);
      }
    }
    return count;
  }
  
  double YieldStats::GetYieldFilterRunsAllSplits(
      std::string stepName, 
      unsigned runMin, 
      unsigned runMax){
    double count = 0.0;
    std::map<unsigned, unsigned>::const_iterator iter;
    for (iter = runIndexMap_.begin(); iter != runIndexMap_.end(); ++iter){
      if (iter->first < runMin || iter->first > runMax) continue;
      for (unsigned j = 0; j < splitNames_.size(); ++j){
        count += GetYield(iter->second, stepIndexMap_[stepName], j);
      }
    }
    return count;
  }
  
  double YieldStats::GetYieldAllRunsFilterSplits(
      std::string stepName, 
      std::vector<std::string> splitNames){
    double count = 0.0;
    std::map<unsigned, unsigned>::const_iterator iter;
    for (iter = runIndexMap_.begin(); iter != runIndexMap_.end(); ++iter){
      for (unsigned j = 0; j < splitNames.size(); ++j){
        count += GetYield(iter->second, stepIndexMap_[stepName], splitIndexMap_[splitNames[j]]);
      }
    }
    return count;
  }
  
  double YieldStats::GetYieldFilterRunsFilterSplits(
      std::string stepName, 
      unsigned runMin, 
      unsigned runMax, 
      std::vector<std::string> splitNames){
    double count = 0.0;
    std::map<unsigned, unsigned>::const_iterator iter;
    for (iter = runIndexMap_.begin(); iter != runIndexMap_.end(); ++iter){
      if (iter->first < runMin || iter->first > runMax) continue;
      for (unsigned j = 0; j < splitNames.size(); ++j){
        count += GetYield(iter->second, stepIndexMap_[stepName], splitIndexMap_[splitNames[j]]);
      }
    }
    return count;
  }

  double YieldStats::GetYield(unsigned runIndex, unsigned stepIndex, unsigned splitIndex){
    return yieldVector_.at(runIndex + stepIndex + splitIndex*stepNames_.size());
  }
  

  void YieldStats::PrintMap(){

    for (std::map<unsigned,unsigned>::const_iterator it = runIndexMap_.begin();
        it != runIndexMap_.end();
        ++it){

      std::cout << "---------------------" << std::endl;
      std::cout << "Run: " << it->first << std::endl;
      std::cout << "---------------------" << std::endl;
      for (unsigned i = 0; i < stepNames_.size(); ++i){
        for (unsigned k = 0; k < splitNames_.size(); ++k){
        std::cout << GetYield(it->second, i, k) << "\t";
        }
        std::cout << std::endl;
      }
    }
    std::cout << std::endl;
  }


}//namespace
