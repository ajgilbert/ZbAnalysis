#include <iostream>
#include <vector>
#include "YieldStats.hh"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TTree.h"
#include "TTreeStorage.hh"

using namespace HbbAnalysis;


int main(int argc, char* argv[]){

  std::cout << "Hello World!" << std::endl;
  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }
  
 
  //YieldStats stats("teststats");
  //stats.InitialiseStepNames(3,"step1","step2","step3");
  //stats.InitialiseSplitNames(1, "all");
  //stats.IncrementCount(1000,0,0,1.1);
  //stats.IncrementCount(1000,1,0,1.2);
  //stats.IncrementCount(1001,"step3","all",5.2);
  //stats.PrintMap();

  TLorentzVector vec(1,2,3,4);
  TFile f("test.root","RECREATE");
  
  SaveViaTree<TLorentzVector>(f, vec, "tempvector");
  TLorentzVector vec2 = LoadViaTree<TLorentzVector>(f,"tempvector");
  vec2.Print();


  
 
  return 0;
}
