#ifndef HbbAnalysis_YieldStats_hh
#define HbbAnalysis_YieldStats_hh

#include <stdarg.h>
#include <vector>
#include <string>
#include <map>

namespace HbbAnalysis {//namespace


  class YieldStats {


  public:
    YieldStats(std::string sampleName, std::string yieldName);
    ~YieldStats(){;}
    YieldStats(){;}
    void InitialiseStepNames(std::vector<std::string> const& stepNames);
    void InitialiseStepNames(unsigned, ... );
    void InitialiseSplitNames(std::vector<std::string> const& splitNames);
    void InitialiseSplitNames(unsigned numArgs, ... );
    void IncrementCount(unsigned run, std::string stepName, std::string splitName, double value);
    void IncrementCount(unsigned run, unsigned stepIndex, unsigned splitIndex,  double value);

    double GetYield(unsigned runIndex, unsigned stepIndex, unsigned splitIndex);
    std::vector<std::string> GetStepNames();
    std::vector<std::string> GetSplitNames();
    double GetYieldAllRunsAllSplits(std::string stepName);
    double GetYieldFilterRunsAllSplits(std::string stepName, unsigned runMin, unsigned runMax);
    double GetYieldAllRunsFilterSplits(std::string stepName, std::vector<std::string> splitNames);
    double GetYieldFilterRunsFilterSplits(std::string stepName, unsigned runMin, unsigned runMax, std::vector<std::string> splitnames);
    
    
    //double GetYieldAllRuns(unsigned stepIndex, unsigned splitIndex);


    void PrintMap();
    


  private:
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

  };
  
}//namespace

#endif //HbbAnalysis_YieldStats_hh
