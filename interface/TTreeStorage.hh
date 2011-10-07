#ifndef HbbAnalysis_SaveAsTree_hh
#define HbbAnalysis_SaveAsTree_hh

#include <string>
#include "TFile.h"
#include "TTree.h"

namespace HbbAnalysis {//namespace

  template<class T>
  void SaveViaTree(TFile& file, T const& object, std::string name){
    T const* object_ptr = &object;
    file.cd();
    TTree* tree = new TTree(name.c_str(),name.c_str());
    tree->Branch(name.c_str(),&object_ptr);
    tree->Fill();
    tree->Write();
    delete tree;
  }

  template<class T>
  T LoadViaTree(TFile& file, std::string name){
    file.cd();
    TTree* tree = dynamic_cast<TTree*>(file.Get(name.c_str()));
    T* object_ptr = 0;
    tree->SetBranchAddress(name.c_str(),&object_ptr);
    tree->GetEntry(0);
    return (*object_ptr);
  }


 

}//namespace

#endif //HbbAnalysis_SaveAsTree_hh
