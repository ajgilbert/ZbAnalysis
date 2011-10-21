#include <iostream>
#include <vector>
#include <map>
#include "UserCode/HbbAnalysis/interface/YieldStats.hh"
#include "UserCode/HbbAnalysis/interface/HbbEvent.hh"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TTree.h"
#include "TTreeStorage.hh"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "TSystem.h"

using namespace HbbAnalysis;


int main(int argc, char* argv[]){

  gSystem->Load("libFWCoreFWLite.so");
  gSystem->Load("libUserCodeHbbAnalysis.so");
  AutoLibraryLoader::enable();
  gSystem->ListLibraries();
  std::cout << "Hello World!" << std::endl;
  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }
  

  /*
  YieldStats stats("Z+b");
  stats.InitialiseStepNames(3,"step1","step2","step3");
  stats.InitialiseSplitNames(2, "split1","split2");
  stats.IncrementCount(1000,0,0,1.1);
  stats.IncrementCount(1000,1,1,1.2);
  stats.IncrementCount(1001,"step3","split1",5.2);
  stats.IncrementCount(10,"step3","split1",10.5);
  stats.PrintMap();

  TFile f("test.root","RECREATE");
  
  SaveViaTree<YieldStats>(f, stats, "NO_RW");
  YieldStats stats2 = LoadViaTree<YieldStats>(f,"NO_RW");
  stats2.PrintMap();
  f.Close();
  */

  TFile f("AnaTree.root");
  gDirectory->cd("/treeMaker/HbbAnalysis");
  TTree* t = (TTree*)gDirectory->Get("Tree");
  HbbAnalysis::HbbEvent* event = 0;
  t->SetBranchAddress("HbbEvent",&event);
  t->GetEntry(0);
  std::cout << "Event: " << event << std::endl;
  std::vector<HbbAnalysis::Jet>* jets = &(event->ak7pfJets());
  for (unsigned i = 0; i < jets->size(); ++i){
    std::cout << "Jet " << i << ":" << std::endl;
    HbbAnalysis::JetECorVars corrs = jets->at(i).ecorVars();
    std::map<std::string,double> vals = corrs.Levels;
    std::map<std::string,double>::const_iterator iter;
    for (iter = vals.begin(); iter != vals.end(); ++iter){
      std::cout << iter->first << "\t" << iter->second << std::endl;
    }
  }

  


  
 
  return 0;
}
