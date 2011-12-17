#include <iostream>
#include <vector>
#include "RangeVector.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TTree.h"
#include "BranchHandler.h"
#include "/Users/Andrew/Code/ZbAnalysis/interface/LatexTable.hh"

using ZbAnalysis::BranchHandler;

class dummyclass {

public:
  dummyclass() {
    x = 1;
  }
  
  double GetX(){
    return x;
  }
  
private:
  double x;
  
};

int main(int argc, char* argv[]){

  std::cout << "Hello World!" << std::endl;
  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }
  
  
  TLorentzVector tlv;
  
  TFile f("test.root");
  TTree* t = (TTree*)f.Get("test");

  ZbAnalysis::BranchHandler<TLorentzVector> br(t,"tlv");
  br.SetAddress();
  ZbAnalysis::BranchHandlerBase* ba = &br;
  for (unsigned i = 0; i < 100; ++i){

    ba->GetEntry(i);
    
    TLorentzVector* tlv = (dynamic_cast<BranchHandler<TLorentzVector>* >(ba))->GetPtr();
    tlv->Print();
  }

  f.Close();
  HbbAnalysis::LatexTable abc;
  

  
  return 0;
}
