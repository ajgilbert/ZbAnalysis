#include <iostream>
#include <vector>
#include "RangeVector.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TTree.h"
#include "Math/Vector4D.h"
#include "Math/Vector4Dfwd.h"
#include "Math/VectorUtil.h"
#include "UserCode/AGilbert/interface/Candidate.hh"
#include "UserCode/AGilbert/interface/CompositeCandidate.hh"



struct tree_struct {
  static TTree *x;
};

TTree* tree_struct::x = 0;



int main(int argc, char* argv[]){
  using ROOT::Math::VectorUtil::DeltaPhi;


  std::cout << "Hello World!" << std::endl;
  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }

  std::cout << tree_struct::x << std::endl;
  tree_struct::x = new TTree("Bus","Bus");
  std::cout << tree_struct::x << std::endl;

  
  
  TLorentzVector tlv;
  tlv.DeltaPhi(tlv);
  
  ROOT::Math::PtEtaPhiEVector vec(25.,2.1,0.4,40);

  TFile f("test.root","RECREATE");
  TTree t("test","test");
  t.Branch("tlv",&tlv);
  t.Branch("newtlv", &vec);
  //Ele event: 995533734
  //ROOT::Math::PtEtaPhiEVector ele1(71.249,0.20535,-0.211156,72.7567);
  //ROOT::Math::PtEtaPhiEVector ele2(42.7506,-0.499311,-2.39774,48.1914);
  //Ele event: 429605927
  //ROOT::Math::PtEtaPhiEVector ele1(62.6136,-2.0064,-2.8834,237.024);
  //ROOT::Math::PtEtaPhiEVector ele2(41.5933,-0.299638,-2.12474,43.4745);
  //Ele event: 9611088
  //ROOT::Math::PtEtaPhiEVector ele1(89.1892,0.108128,-3.095,89.7111);
  //ROOT::Math::PtEtaPhiEVector ele2(36.3354,1.62464,3.02502,95.8087);
  //Mu Event: 541770685
  //ROOT::Math::PtEtaPhiEVector ele1(56.555,-0.146111,-2.63534,57.1608);
  //ROOT::Math::PtEtaPhiEVector ele2(41.8467,0.51185,1.53697,47.4492);
  //Mu Event: 349317711
  ROOT::Math::PtEtaPhiEVector ele1(96.255,-0.79535,-3.02593,128.339);
  ROOT::Math::PtEtaPhiEVector ele2(43.4676,-0.320496,-1.23963,45.7194);
    

  ROOT::Math::PtEtaPhiEVector Z = ele1 + ele2;
  std::cout << "M_LL:" << Z.mass() << std::endl;

  for (unsigned i = 0; i < 0; ++i){

    tlv = TLorentzVector(double(i+1),double(i+2),double(i+3),400.0);
    t.Fill();
    agilbert::Candidate cand(ROOT::Math::PtEtaPhiEVector(25,0.0,-1.5,25));
    agilbert::Candidate cand2(ROOT::Math::PtEtaPhiEVector(25,0.0,+1.5,25));
    agilbert::Candidate cand3(ROOT::Math::PtEtaPhiEVector(50,0.0,-2.0,50));
    agilbert::Candidate cand4(ROOT::Math::PtEtaPhiEVector(50,0.0,+2.0,50));
    agilbert::CompositeCandidate comp;
    comp.AddCandidate("electron1", &cand);
    comp.AddCandidate("electron2", &cand2);
    agilbert::CompositeCandidate comp2;
    comp2.AddCandidate("electron3", &cand3);
    comp2.AddCandidate("electron4", &cand4);
    agilbert::CompositeCandidate comp3;
    comp3.AddCandidate("comb1", &comp);
    comp3.AddCandidate("comb2", &comp2);

    comp3.Print();
    agilbert::CompositeCandidate comp4;
    comp4.AddCandidate("electron1", &cand);
    comp4.AddCandidate("electron2", &cand2);
    comp4.AddCandidate("electron3", &cand3);
    comp4.AddCandidate("electron4", &cand4);
    comp4.Print();
    std::cout << ROOT::Math::VectorUtil::DeltaPhi(comp3,comp4) << std::endl;




}

  

  
  
  t.Write();
  f.Close();
  
  return 0;
}
