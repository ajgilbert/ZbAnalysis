#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cxxabi.h>

#include "boost/any.hpp"
#include "boost/function.hpp"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TTree.h"
#include <typeinfo>
#include "EventBase.h"
#include "TreeEvent.h"
#include "TSystem.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "UserCode/HbbAnalysis/interface/HbbEvent.hh"


template <class T>
void PrintDefault() {
  T x;
  std::cout << typeid(x).name() << std::endl;
}

int main(int argc, char* argv[]){

  gSystem->Load("libFWCoreFWLite.dylib");
  gSystem->Load("libUserCodeHbbAnalysis.dylib");
  AutoLibraryLoader::enable();


  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }


  TFile f("test/AnaTree.root");
  gDirectory->cd("treeMaker/HbbAnalysis");
  TTree* tree = (TTree*)gDirectory->Get("Tree");

  HbbAnalysis::HbbEvent *hbbevent = 0;

  TFile ele_file("test/Electrons.root","RECREATE");
  TTree ele_tree("ele_tree","ele_tree");
  std::vector<HbbAnalysis::Electron> *ele_ptr;
  ele_tree.Branch("electrons",&ele_ptr);




  ajg::TreeEvent event;
  event.SetTree(tree);
  event.AddBranch<HbbAnalysis::HbbEvent>("HbbEvent");
  std::cout << "Processing " << (tree->GetEntries()) << " events." << std::endl;
  for (unsigned k =0; k < 1; ++k) {
    for (unsigned i = 0; i < tree->GetEntries(); ++i) {
      event.SetEvent(i);
      hbbevent = event.Get<HbbAnalysis::HbbEvent*>("HbbEvent");
      event.Add("test_double", double(i));
      ele_ptr = &(hbbevent->electrons());
      ele_tree.Fill();
      //hbbevent->PrintReco();
    }
  }
  ele_file.Write();
  ele_file.Close();
  event.List();

  TFile ele_read("test/Electrons.root");
  TTree* ele_rtree = (TTree*)ele_read.Get("ele_tree");
  ajg::TreeEvent ele_event;
  ele_event.SetTree(ele_rtree);
  ele_event.AddBranchPtrVec<HbbAnalysis::Electron>("electrons");

  std::vector<HbbAnalysis::Electron *> * new_ele_vec = 0;

  for (unsigned i = 0; i < ele_rtree->GetEntries(); ++i) {
    ele_event.SetEvent(i);
    new_ele_vec = &(ele_event.Get<std::vector<HbbAnalysis::Electron*> >("electrons"));
    new_ele_vec->clear();
    new_ele_vec = &(ele_event.Get<std::vector<HbbAnalysis::Electron*> >("electrons"));
    std::cout << new_ele_vec->size() << std::endl;
  }

  ele_event.List();









  
  return 0;
}
