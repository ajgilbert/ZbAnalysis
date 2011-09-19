#include <iostream>
#include <vector>
#include "RangeVector.h"
#include "TLorentzVector.h"
#include "UserCode/HbbAnalysis/interface/HbbEvent.hh"


int main(int argc, char* argv[]){

  std::cout << "Hello World!" << std::endl;
  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }
  RangeVector rangevec;
  TLorentzVector tlv(1,2,3,4);
  std::cout << tlv.Eta() << std::endl;
  HbbAnalysis::BaseVars baseVars;
  baseVars.E = 25.0;
  return 0;
}
