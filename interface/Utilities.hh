#ifndef HbbAnalysis_Utilities_hh
#define HbbAnalysis_Utilities_hh

#include <string>
#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>



class Utilities {

public:
  Utilities(){};
  ~Utilities(){};

  Utilities(const double aNumber, const double aError):
    number_(aNumber),
    error_(fabs(aError)),
    errorPlus_(fabs(aError)),
    errorMinus_(fabs(aError)),
    pos_(0),
    asymErrors_(false)
  {};

  Utilities(const double aNumber, const double aErrorPlus, const double aErrorMinus):
    number_(aNumber),
    errorPlus_(fabs(aErrorPlus)),
    errorMinus_(fabs(aErrorMinus)),
    pos_(0),
    asymErrors_(true)
  {
    error_ = std::max(errorPlus_,errorMinus_);
  };

  void calculate();

  double findDecade(const double aErr);

  std::string round(const double aNumber);

  void alignStrings();
  void appendZeros(unsigned int nFinal, unsigned int nInit, std::string & aStr);
  unsigned int nDigitsAfterDot(std::string aStr);


  //std::string findDigit(const double aNumber);

  inline double roundedNumber(){
    double lTmp;
    std::istringstream(roundedNumber_)>>lTmp;
    return lTmp;
  };

  inline double roundedError(){
    double lTmp;
    std::istringstream(roundedError_)>>lTmp;
    return lTmp;
  };

  inline double roundedErrorPlus(){
    double lTmp;
    std::istringstream(roundedErrorPlus_)>>lTmp;
    return lTmp;
  };

  inline double roundedErrorMinus(){
    double lTmp;
    std::istringstream(roundedErrorMinus_)>>lTmp;
    return lTmp;
  };

  inline std::string roundedResult(){

    //    std::string lRound = findDigit(roundedNumber_);
    //std::string lRoundErr = findDigit(roundedError_);
    //std::string lRoundErrPlus = findDigit(roundedErrorPlus_);
    //std::string lRoundErrMinus = findDigit(roundedErrorMinus_);
    
    std::ostringstream lTmp;
    if (!asymErrors_) lTmp << "$ " 
			   << roundedNumber_
      //<< lRound 
			   << " \\pm " 
			   << roundedError_ 
      //		   << lRoundErr 
			   << " $" ;
    else lTmp << "$ " 
	      << roundedNumber_ 
      //      << lRound 
	      << " ^{+" 
	      << roundedErrorPlus_ 
      //      << lRoundErrPlus 
	      << "} _{-" 
	      << roundedErrorMinus_ 
      //      << lRoundErrMinus 
	      << "} $" ;

    return lTmp.str();
  };



private:
  double number_;
  double error_;
  double errorPlus_;
  double errorMinus_;

  double pos_;

  //replace by std::vector<std::string> ?
  std::string roundedNumber_;
  std::string roundedError_;
  std::string roundedErrorPlus_;
  std::string roundedErrorMinus_;

  bool asymErrors_;

};


#endif//HbbAnalysis_Utilities_hh
