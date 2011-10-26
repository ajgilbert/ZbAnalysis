#ifndef HbbAnalysis_LatexTable_hh
#define HbbAnalysis_LatexTable_hh

#include <stdarg.h>
#include <vector>
#include <string>
#include <map>
#include "YieldStats.hh"

namespace HbbAnalysis {//namespace


  class LatexTable {


  public:
    ~LatexTable(){;}
    LatexTable();

    void RestrictToRunRange(bool arg)     { restrictToRunRange_   = arg; }
    void SpecifyBinsToSum(bool arg)       { specifyBinsToSum_     = arg; }
    void ShowSumMcColumn(bool arg)        { showSumMcColumn_      = arg; }
    void SpecifySteps(bool arg)           { specifySteps_         = arg; }
    void ShowInitialYields(bool arg)      { showInitialYields_    = arg; }
    void ShowEfficiencyErrors(bool arg)   { showEfficiencyErrors_ = arg; }
    void ScaleMc(bool arg)                { scaleMc_              = arg; }

    void AddYieldStats(YieldStats & yieldStats, bool isData);
    void AddYieldStats(YieldStats & yieldStats, bool isData, double nInitial);
    void AddYieldStats(YieldStats & yieldStats, bool isData, double nInitial, double xs);


    void SetRunRange(unsigned startRun, unsigned endRun) {
      startRun_ = startRun;
      endRun_ = endRun;
    }
    void SetBinsToSum(std::vector<std::string> const& binNames) {
      binsToSum_ = binNames;
    }
    void SetStepsToShow(std::vector<std::string> const& stepNames) { 
      stepsToShow_ = stepNames;
    }
    void SetTargetLumi(double lumi){
      targetLumi_ = lumi;
    }
    void SetCaptionBegin(std::string captionBegin){
      captionBegin_ = captionBegin;
    }

    
    void MakeTable();

  private:
    //Flags to control the design of the table
    bool restrictToRunRange_;
    bool specifyBinsToSum_;
    bool showSumMcColumn_;
    bool specifySteps_;
    bool showInitialYields_;
    bool showEfficiencyErrors_;
    bool scaleMc_;
    
    //Data used when checking above flags
    unsigned startRun_;
    unsigned endRun_;
    std::vector<std::string> binsToSum_;
    std::map<std::string, bool> isDataMap_;
    std::vector<std::string> stepsToShow_;
    std::map<std::string, double> initialYieldsMap_;
    std::map<std::string, double> crossSectionMap_;
    double targetLumi_;
    std::string captionBegin_;

    //A vector to maintain the order in which the yield maps are added 
    std::vector<std::string> yieldStatsNames_;
    //Map give YieldMap pointer from the name
    std::map<std::string, YieldStats*> yieldStatsMap_;
  };
  
}//namespace

#endif //HbbAnalysis_LatexTable_hh
