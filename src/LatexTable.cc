#include "LatexTable.hh"
#include "YieldStats.hh"
#include "TEfficiency.h"
#include <stdarg.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

namespace HbbAnalysis {//namespace
      
  LatexTable::LatexTable() {
    //Set Flag Defaults
    restrictToRunRange_   = false;
    specifyBinsToSum_     = false;
    showSumMcColumn_      = true;
    specifySteps_         = false;
    showInitialYields_    = true;
    showEfficiencyErrors_ = true;
    scaleMc_              = true;
    //Set other sensible defaults
    startRun_ = 0;
    endRun_ = std::numeric_limits<unsigned>::max();
    targetLumi_ = -1;
  }

  void LatexTable::AddYieldStats(YieldStats & yieldStats, bool isData) {
    std::string name = yieldStats.GetSampleName();
    yieldStatsNames_.push_back(name);
    if (yieldStatsMap_.count(name) == 0) {
      yieldStatsMap_[name] = &(yieldStats);
      isDataMap_[name] = isData;
    } else {
      std::cout << "Warning: Attempt to add a YieldStats with name \"" << name << "\" failed.  A YieldMap with this name has already been added." << std::endl;
    }
  }

  void LatexTable::AddYieldStats(YieldStats & yieldStats, bool isData, double nInitial) {
    AddYieldStats(yieldStats, isData);
    initialYieldsMap_[yieldStats.GetSampleName()] = nInitial;
  }

  void LatexTable::AddYieldStats(YieldStats & yieldStats, bool isData, double nInitial, double xs) {
    AddYieldStats(yieldStats, isData);
    initialYieldsMap_[yieldStats.GetSampleName()] = nInitial;
    crossSectionMap_[yieldStats.GetSampleName()] = xs;
}

  void LatexTable::MakeTable(){ 
   TEfficiency eff;

    //Determine the number of samples
    unsigned nSamples = yieldStatsNames_.size();
    
    //For now take list of steps from the first yieldStats object added
    std::vector<std::string> stepNames;  
    if (nSamples > 0) {
      stepNames = yieldStatsMap_[yieldStatsNames_[0]]->GetStepNames();
    }
  
    //Print start boilerplate:
    std::cout << "\\begin{table}" << std::endl;
    std::cout << "{\\" << std::endl;
    std::cout << "\\caption{";
    if (captionBegin_ == "") {
      std::cout << "Yields for ";
    } else {
      std::cout << captionBegin_ << " yields for ";
    }
    std::cout << targetLumi_ << " $\\mathrm{pb^{-1}}$ of data.";
    std::cout << "}" << std::endl;
    std::cout << "\\begin{tabular}{|l";

    //Specify the desired number of columns
    for (unsigned i = 0; i < nSamples; ++i) std::cout << "|c";
    //Add an additional column if showSumMcColumn is set
    if (showSumMcColumn_) std::cout << "|c";
    std::cout << "|}" << std::endl;

    //Find last MC sample, or if none found, the last sample
    unsigned SumMcColumnIdx = nSamples - 1;
    for (unsigned i = 0; i < nSamples; ++i) {
     if (!isDataMap_[yieldStatsNames_[i]]) SumMcColumnIdx = i; 
    }

    //hline for the top of the table
    std::cout << "\\hline" << std::endl;

    //Print the sample names row
    std::cout << "Step "; 
    for (unsigned i = 0; i < nSamples; ++i) {
      std::cout << "& " << yieldStatsNames_[i] << " ";
    if (showSumMcColumn_ && i == SumMcColumnIdx) std::cout << "& Sum MC ";
    }
    std::cout << "\\\\" << std::endl;

    //hline under sample names row
    std::cout << "\\hline" << std::endl;

    //Loop through steps
    for (unsigned i = 0; i < stepNames.size(); ++i){
      double sumMC = 0.0;
      double sumMCErrSq = 0.0;

      std::cout << stepNames[i] << " ";
      for (unsigned j = 0; j < nSamples; ++j) {
        double count = 0.0;
        //Based on whether there is run or bin filtering, get the yield
        if (restrictToRunRange_) {
          if (specifyBinsToSum_) {
            count = yieldStatsMap_[yieldStatsNames_[j]]->CalculateYield(stepNames[i], startRun_, endRun_, binsToSum_);
          } else {
            count = yieldStatsMap_[yieldStatsNames_[j]]->CalculateYield(stepNames[i], startRun_, endRun_);
          }
        } else {
          if (specifyBinsToSum_){
            count = yieldStatsMap_[yieldStatsNames_[j]]->CalculateYield(stepNames[i], binsToSum_);
          } else {
            count = yieldStatsMap_[yieldStatsNames_[j]]->CalculateYield(stepNames[i]);
          }
        }
        //Now the yield is obtained
        double error = 0.0;
        double sf = 1.0;
        if (showEfficiencyErrors_) {
          if (isDataMap_[yieldStatsNames_[j]]) {
            error = sqrt(count);
          } else {
            if (initialYieldsMap_.count(yieldStatsNames_[j]) != 0) {
              double init = initialYieldsMap_[yieldStatsNames_[j]];
              if (init >= count) {
                error = (eff.ClopperPearson(init+0.5,count+0.5,0.683 ,1)*init)-count;
              }//If numerator is less than denominator
            }//If an initial yield has been set for this sample
          }
        }//If showEfficiencyErrors flag is set
        
        if (scaleMc_ && !isDataMap_[yieldStatsNames_[j]]) {
          if (targetLumi_ > 0 && crossSectionMap_.count(yieldStatsNames_[j]) != 0
              && initialYieldsMap_.count(yieldStatsNames_[j]) != 0) {
            sf = (crossSectionMap_[yieldStatsNames_[j]] * targetLumi_) 
              / initialYieldsMap_[yieldStatsNames_[j]];
          }//If we have a cross-section, initial yield and target lumi
        }//If scaleMc flag is set and the sample is actually MC

        count *= sf;
        error *= sf;
        sumMC += count;
        sumMCErrSq += (error*error);
        std::cout << "& $" << std::fixed << std::setprecision(0) << count;
        if (showEfficiencyErrors_) std::cout << "\\pm " << error;
        std::cout << "$ ";

        if (showSumMcColumn_ && j == SumMcColumnIdx){
          std::cout << "& $" << sumMC;
          if (showEfficiencyErrors_) std::cout << "\\pm " << sqrt(sumMCErrSq);
          std::cout << "$ ";
        }
      }//Loop through samples
      std::cout << "\\\\" << std::endl;

    }
    std::cout << "\\hline" << std::endl;

    //Print end boilerplate:
    std::cout << "\\end{tabular}" << std::endl;
    std::cout << "}" << std::endl;
    std::cout << "\\end{table}" << std::endl;

    

  }



}//namespace
