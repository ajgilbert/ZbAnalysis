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
    LatexTable(){
      runRestricted_ = false;
      startRun_ = 0;
      endRun_ = 0;
      splitRestricted_ = false;
    }
    void AddYieldStats(std::string name, YieldStats & yieldStats);
    void MakeTable();
    void RestrictToRun(unsigned run);
    void RestrictToRunRange(unsigned startRun, unsigned endRun);
    void CombineSplitsByName(std::vector<std::string> splitNames);
    void CombineAllSplits();



    /*
    void InitialiseStepNames(unsigned, ... );
    void InitialiseSplitNames(std::vector<std::string> const& splitNames);
    void InitialiseSplitNames(unsigned numArgs, ... );
    void IncrementCount(unsigned run, std::string stepName, std::string splitName, double value);
    void IncrementCount(unsigned run, unsigned stepIndex, unsigned splitIndex,  double value);

    void PrintMap();
    */
    


  private:
    unsigned startRun_;
    unsigned endRun_;
    bool runRestricted_;

    std::vector<std::string> selectedSplits_;
    bool splitRestricted_;
    
    //A vector to maintain the order in which the yield maps are added 
    std::vector<std::string> yieldStatsNames_;
    //Map give YieldMap pointer from the name
    std::map<std::string, YieldStats*> yieldStatsMap_;

    /*
    std::string sampleName_;
    std::string yieldName_;
    std::vector<double> yieldVector_;
    std::vector<std::string> stepNames_;
    std::vector<std::string> splitNames_;

    std::map<std::string,unsigned> stepIndexMap_;
    std::map<std::string,unsigned> splitIndexMap_;
    std::map<unsigned, unsigned> runIndexMap_;

    void BuildStepIndexMap();
    void BuildSplitIndexMap();
    */
    

  };
  
}//namespace

#endif //HbbAnalysis_LatexTable_hh
