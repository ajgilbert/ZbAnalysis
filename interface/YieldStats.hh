#ifndef HbbAnalysis_YieldStats_hh
#define HbbAnalysis_YieldStats_hh

#include <stdarg.h>
#include <vector>
#include <string>
#include <map>

namespace HbbAnalysis {//namespace


  class YieldStats {


  public:
    typedef std::map<unsigned, std::vector<std::vector<double> > > YieldMap;

    YieldStats(std::string yieldName);
    ~YieldStats(){;}
    YieldStats(){;}
    void InitialiseStepNames(std::vector<std::string> const& stepNames);
    void InitialiseStepNames(unsigned, ... );
    void InitialiseSplitNames(std::vector<std::string> const& splitNames);
    void InitialiseSplitNames(unsigned numArgs, ... );
    void IncrementCount(unsigned run, std::string stepName, std::string splitName, double value);
    void IncrementCount(unsigned run, unsigned stepIndex, unsigned splitIndex,  double value);

    void PrintMap();
    


  private:
    std::string yieldName_;
    YieldMap runMap_;
    std::vector<std::string> stepNames_;
    std::vector<std::string> splitNames_;
    std::map<std::string,unsigned> stepIndexMap_;
    std::map<std::string,unsigned> splitIndexMap_;
    void BuildStepIndexMap();
    void BuildSplitIndexMap();

  };
  
}//namespace

#endif //HbbAnalysis_YieldStats_hh
