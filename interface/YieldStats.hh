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

    //Setters
    void SetSampleName(std::string const& sampleName);
    void SetYieldName(std::string const& yieldName);
    void SetStepNames(std::vector<std::string> const& stepNames);
    void SetBinNames(std::vector<std::string> const& binNames);

    //Getters
    std::vector<std::string> GetStepNames() const;
    std::vector<std::string> GetBinNames() const;
    std::string GetSampleName() const { return sampleName_; }

    void IncrementCount(unsigned run, unsigned binIndex, unsigned stepIndex,  double value);
    void IncrementCount(unsigned run, std::string binName, std::string stepName, double value);

    double CalculateYield(std::string stepName) const;
    double CalculateYield(std::string stepName, unsigned minRun, unsigned maxRun) const;
    double CalculateYield(std::string stepName, std::vector<std::string> binNames) const;
    double CalculateYield(std::string stepName, unsigned minRun, unsigned maxRun, std::vector<std::string> binNames) const;

    //Access Methods
    double & at(unsigned runIndex, unsigned binIndex, unsigned stepIndex);
    double at(unsigned runIndex, unsigned binIndex, unsigned stepIndex) const;

    void Print() const;
    
  private:
    std::string sampleName_;
    std::string yieldName_;
    std::vector<double> yieldVector_;
    std::vector<std::string> stepNames_;
    std::vector<std::string> binNames_;
    std::map<std::string,unsigned> stepIndexMap_;
    std::map<std::string,unsigned> binIndexMap_;
    std::map<unsigned, unsigned> runIndexMap_;
  };
  
}//namespace

#endif //HbbAnalysis_YieldStats_hh
