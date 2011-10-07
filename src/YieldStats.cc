#include "YieldStats.hh"
#include <stdarg.h>
#include <iostream>

namespace HbbAnalysis {//namespace

  YieldStats::YieldStats(std::string yieldName){
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
    for (unsigned i = 0; i < stepNames_.size(); ++i){
      std::cout << stepNames_[i] << std::endl; 
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
    for (unsigned i = 0; i < splitNames_.size(); ++i){
      std::cout << splitNames_[i] << std::endl; 
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
    if (runMap_.count(run) == 0){
      runMap_[run] = std::vector<std::vector<double> >(stepNames_.size(),std::vector<double>(splitNames_.size(),0.0));
    }
    try{
      runMap_[run].at(stepIndex).at(splitIndex) += value;
    } 
    catch(std::exception& e)
    {
      std::cerr << "Exception caught in method YieldStats::IncrementCount: " << e.what() << std::endl;
    }
  }

  void YieldStats::PrintMap(){

    for (YieldStats::YieldMap::const_iterator it = runMap_.begin();
        it != runMap_.end();
        ++it){

      std::cout << "---------------------" << std::endl;
      std::cout << it->first << std::endl;
      std::cout << "---------------------" << std::endl;
      for (unsigned i = 0; i < (it->second).size(); ++i){
        for (unsigned j = 0; j < (it->second).at(i).size(); ++j){
          std::cout << (it->second).at(i).at(j) << "\t";
        }
        std::cout << std::endl;
      }
      std::cout << std::endl;
    }

  }

}//namespace
