#ifndef __HbbAnalysis__RangeVector__
#define __HbbAnalysis__RangeVector__
#include <vector>
#include <algorithm>

//! A class that stores, and allows querying of, a vector of intervals
/*! 
  This class is designed to hold an arbitrary number of bin ranges.  In
  particular there is no requirement that the ranges are contiguous.
  As well as returning the range bounds and central values, a method is
  provided to return the appropriate bin index for a given value.  A 
  value of -1 is returned if the value is not found in any bin.
*/

class RangeVector{
  private:
    std::vector<double> lower; /*!< Stores the lower edge interval values. */
    std::vector<double> upper; /*!< Stores the upper edge interval values. */
    
  public:
    RangeVector();
    RangeVector(std::vector<double> const&, std::vector<double> const&);
    void AddUpper(std::vector<double> const&);
    void AddLower(std::vector<double> const&);
    void push_back(double, double); //lower,upper
    unsigned size();
    bool ConsistencyCheck(bool);
    double GetLower(unsigned);
    double GetUpper(unsigned);
    double GetCentral(unsigned);
    double GetWidth(unsigned);
    int GetBin(double);


};


#endif
