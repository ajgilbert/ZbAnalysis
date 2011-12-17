#include "Utilities.hh"

void Utilities::calculate(){

  double lErr = 0;
  if (asymErrors_) {
    lErr = std::min(errorPlus_,errorMinus_);
  }
  else lErr = error_;

  double lSignificantFigure = findDecade(lErr);
  double lCheck = findDecade(fabs(number_));

  if (lCheck < lSignificantFigure) lSignificantFigure = lCheck;
  pos_ = lSignificantFigure;
  roundedNumber_ = round(number_);

  //std::cout << "-- roundNumber = " << roundedNumber_ << " pos " << pos_ << std::endl;
 
  if (asymErrors_) {
    roundedErrorPlus_ = round(errorPlus_);
    roundedErrorMinus_ = round(errorMinus_);
    roundedError_ = round(std::max(errorPlus_,errorMinus_));
  }
  else {
    roundedError_ = round(error_);
    roundedErrorPlus_ = roundedError_;
    roundedErrorMinus_ = roundedError_;
  }

  alignStrings();

}

double Utilities::findDecade(const double aErr) {
  int i = 0;
  for (; i<64; ++i){//loop on i
    //find first digit
    double lBig = pow(10,63-i);
    unsigned int lDivBig = static_cast<unsigned int>(aErr/lBig);
    if (lDivBig != 0) {
      i=63-i;
      //      std::cout << "-- found big for i=: " << i << std::endl;
      break;
    }
  }//loop on i
  pos_ = pow(10,i);
  if (i==64){
    //look for small numbers
    int j=0;
    for (; j<64; ++j){//loop on j
      //find first digit
      double lSmall  = pow(10,-j);
      unsigned int lDivSmall = static_cast<unsigned int>(aErr/lSmall);
      if (lDivSmall != 0){
	j = -j;
	//std::cout << "-- found small for j=: " << j << std::endl;
	break;
      }
    }//loop on j

    //std::cout << "-- found result: i=" << i << " " << pow(10,i) << std::endl;
    pos_ = pow(10,j);
  }

  return pos_;
  
}


std::string Utilities::round(const double aNumber) {
  double lTmp = static_cast<int>(aNumber/pos_+fabs(aNumber)/aNumber*0.5)*pos_;
  std::ostringstream lStr;
  lStr << lTmp;
  return lStr.str();
}

void Utilities::alignStrings() {

  unsigned int n1 = nDigitsAfterDot(roundedNumber_);
  unsigned int n2 = nDigitsAfterDot(roundedError_);
  unsigned int n3 = nDigitsAfterDot(roundedErrorPlus_);
  unsigned int n4 = nDigitsAfterDot(roundedErrorMinus_);

  unsigned int n = std::max(std::max(n1,n2),std::max(n3,n4));

  if (n1 < n) appendZeros(n,n1,roundedNumber_);
  if (n2 < n) appendZeros(n,n2,roundedError_);
  if (n3 < n) appendZeros(n,n3,roundedErrorPlus_);
  if (n4 < n) appendZeros(n,n4,roundedErrorMinus_);

}

void Utilities::appendZeros(unsigned int nFinal, unsigned int nInit, std::string & aStr) {
  unsigned int n = nFinal-nInit;
  if (nInit==0) aStr.append(".");

  //std::cout << " str " << aStr << " size " << aStr.size() << " appending " << n << std::endl;
  for (unsigned int i(0);i<n;++i){
    aStr.append("0");
  }

  //std::cout << " size after " << aStr.size() << std::endl;

}

unsigned int Utilities::nDigitsAfterDot(std::string aStr) {
  unsigned int lDot = 0;
  if (aStr.find(".")!= aStr.npos) lDot = aStr.find(".")+1;
  else lDot = aStr.size();
  //  std::cout << "-- string = " << aStr << " " 
  //    << " npos = " << aStr.npos 
  //    << " size " << aStr.size() 
  //    << " dot pos " << lDot << " result "
  //    << aStr.size()-lDot << std::endl;
  return aStr.size()-lDot;
}


//std::string Utilities::findDigit(const double aNumber){
//  std::string lStr="";
//  unsigned int lTmp = static_cast<unsigned int>(fabs(aNumber)/pos_);
//  unsigned int lNum = static_cast<unsigned int>(lTmp/10.)*10;
//  std::cout << "-- debug number=" << aNumber << ", ltmp=" << lTmp << ", lnum=" << lNum << std::endl;
//  if ( (lTmp-lNum) == 0) {
//    lStr = "0";
//    if (aNumber >= 1 && 
//	(static_cast<unsigned int>(fabs(aNumber)*10.)-
//	 static_cast<unsigned int>(fabs(aNumber))*10 == 0)
//	) lStr = ".0";
//  }
//  return lStr; 
//}
