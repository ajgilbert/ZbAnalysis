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
#include "AnalysisBase.h"
#include "ElectronDemoModule.h"
#include "HbbEventSplitter.h"
#include "TreeEvent.h"
#include "TSystem.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "UserCode/HbbAnalysis/interface/HbbEvent.hh"


int main(int argc, char* argv[]){

  gSystem->Load("libFWCoreFWLite.dylib");
  gSystem->Load("libUserCodeHbbAnalysis.dylib");
  AutoLibraryLoader::enable();

  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }

  std::vector<std::string> files;
  files.push_back("test/AnaTree.root");

  ajg::AnalysisBase test_ana("test analysis",
    files, "/treeMaker/HbbAnalysis", "Tree", 10);

  //ajg::ElectronDemoModule electronDemoModule("ElectronDemoModule");
  ajg::HbbEventSplitter hbbEventSplitter("HbbEventSplitter");
  hbbEventSplitter.output_path_ = "test/";
  hbbEventSplitter.split_every_ = 2;
  //test_ana.AddModule(&electronDemoModule);
  test_ana.AddModule(&hbbEventSplitter);
  test_ana.RunAnalysis();













  
  return 0;
}
