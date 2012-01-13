#include <iostream>
#include <vector>
#include "RangeVector.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TTree.h"

int main(int argc, char* argv[]){

  std::cout << "Hello World!" << std::endl;
  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }
  
  
  TLorentzVector tlv;  
  
  TFile f("test.root","RECREATE");
  TTree t("test","test");
  t.Branch("tlv",&tlv);
  for (unsigned i = 0; i < 200; ++i){

    tlv = TLorentzVector(double(i+1),double(i+2),double(i+3),400.0);
    std::cout << tlv.Pt() << std::endl;
    t.Fill();
  }

  

  
  
  t.Write();
  f.Close();
  
  return 0;
}
