#include <iostream>
#include <vector>
#include <string>
#include "RangeVector.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TH1F.h"

int main(int argc, char* argv[]){

  std::cout << "Hello World!" << std::endl;
  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }

  std::string path = "/jet_2btag_HE_MET/Pairs/bb";
  std::string name = "p_Vis_pt";
  std::string outfile = argv[1];

  std::vector<std::string> filepaths;
  filepaths.push_back("/data/Zb/DYJetsToLL/4_2_4/S4/TuneZ2/bFlav/jes_central_ee_PF_SSVHE.root");
  filepaths.push_back("/data/Zb/DYJetsToLL/4_2_4/S4/TuneZ2/cFlav/jes_central_ee_PF_SSVHE.root");
  filepaths.push_back("/data/Zb/DYJetsToLL/4_2_4/S4/TuneZ2/lFlav/jes_central_ee_PF_SSVHE.root");
  filepaths.push_back("/data/Zb/TTJets/4_2_4/S4/TuneZ2/jes_central_ee_PF_SSVHE.root");
  filepaths.push_back("/data/Zb/ZZ/4_2_4/S4/TuneZ2/jes_central_ee_PF_SSVHE.root");
  
  filepaths.push_back("/data/Zb/DYJetsToLL/4_2_4/S4/TuneZ2/bFlav/jes_plus_ee_PF_SSVHE.root");
  filepaths.push_back("/data/Zb/DYJetsToLL/4_2_4/S4/TuneZ2/cFlav/jes_plus_ee_PF_SSVHE.root");
  filepaths.push_back("/data/Zb/DYJetsToLL/4_2_4/S4/TuneZ2/lFlav/jes_plus_ee_PF_SSVHE.root");
  filepaths.push_back("/data/Zb/TTJets/4_2_4/S4/TuneZ2/jes_plus_ee_PF_SSVHE.root");
  filepaths.push_back("/data/Zb/ZZ/4_2_4/S4/TuneZ2/jes_plus_ee_PF_SSVHE.root");
  
  filepaths.push_back("/data/Zb/DYJetsToLL/4_2_4/S4/TuneZ2/bFlav/jes_minus_ee_PF_SSVHE.root");
  filepaths.push_back("/data/Zb/DYJetsToLL/4_2_4/S4/TuneZ2/cFlav/jes_minus_ee_PF_SSVHE.root");
  filepaths.push_back("/data/Zb/DYJetsToLL/4_2_4/S4/TuneZ2/lFlav/jes_minus_ee_PF_SSVHE.root");
  filepaths.push_back("/data/Zb/TTJets/4_2_4/S4/TuneZ2/jes_minus_ee_PF_SSVHE.root");
  filepaths.push_back("/data/Zb/ZZ/4_2_4/S4/TuneZ2/jes_minus_ee_PF_SSVHE.root");
  
  std::vector<std::string> newname;
  newname.push_back("DYbflav_central");
  newname.push_back("DYcflav_central");
  newname.push_back("DYlflav_central");
  newname.push_back("TTJets_central");
  newname.push_back("ZZ_central");

  newname.push_back("DYbflav_plus");
  newname.push_back("DYcflav_plus");
  newname.push_back("DYlflav_plus");
  newname.push_back("TTJets_plus");
  newname.push_back("ZZ_plus");

  newname.push_back("DYbflav_minus");
  newname.push_back("DYcflav_minus");
  newname.push_back("DYlflav_minus");
  newname.push_back("TTJets_minus");
  newname.push_back("ZZ_minus");
  TFile f((outfile+".root").c_str(),"RECREATE");
  for (unsigned i = 0; i < filepaths.size(); ++i) {
    TFile g(filepaths[i].c_str());
    g.cd();
    gDirectory->cd(path.c_str());
    TH1F *hp = ((TH1F*)gDirectory->Get(name.c_str()));
    hp->SetName(newname[i].c_str());
    f.cd();
    hp->Write();
    g.Close();
  }
  
  f.Close();
  
  return 0;
}
