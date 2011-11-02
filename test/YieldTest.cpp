#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "TEfficiency.h"

#include "UserCode/HbbAnalysis/interface/YieldStats.hh"
#include "LatexTable.hh"
#include "MiscFunctions.hh"
#include "UserCode/HbbAnalysis/ZbbSel/interface/TTreeStorage.hh"
#include "TFile.h"
#include "TSystem.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"

using namespace HbbAnalysis;
using namespace std;


int main(int argc, char* argv[]){
  gSystem->Load("libFWCoreFWLite.so");
  gSystem->Load("libUserCodeHbbAnalysis.so");
  AutoLibraryLoader::enable();

  std::cout << "Hello World!" << std::endl;
  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }
/*
  YieldStats stats("Z+b","NO_RW");
  stats.SetStepNames(StringVecify(4,"Lepton Pair","Jet ID","1 SSVHE Tag","2 SSVHE Tags"));
  stats.SetBinNames(StringVecify(1, "all"));
  stats.IncrementCount(1,0,0,202011);
  stats.IncrementCount(1,0,1,55868);
  stats.IncrementCount(1,0,2,1434);
  stats.IncrementCount(1,0,3,4);
  stats.Print();

  YieldStats statsC("Z+c","NO_RW");
  statsC.SetStepNames(StringVecify(4,"Lepton Pair","Jet ID","1 SSVHE Tag","2 SSVHE Tags"));
  statsC.SetBinNames(StringVecify(1, "all"));
  statsC.IncrementCount(1,0,0,933108);
  statsC.IncrementCount(1,0,1,204167);
  statsC.IncrementCount(1,0,2,3427);
  statsC.IncrementCount(1,0,3,32);
  statsC.Print();
  
  YieldStats statsD("Data","NO_RW");
  statsD.SetStepNames(StringVecify(4,"Lepton Pair","Jet ID","1 SSVHE Tag","2 SSVHE Tags"));
  statsD.SetBinNames(StringVecify(1, "all"));
  statsD.IncrementCount(1,0,0,702259);
  statsD.IncrementCount(1,0,1,135967);
  statsD.IncrementCount(1,0,2,100);
  statsD.IncrementCount(1,0,3,1);
  statsD.Print();
  */
  unsigned nMC = 7;

  vector<string> samplePathsMC = StringVecify(nMC,
      "/data/Zb/TTJets/4_2_4/S4/TuneZ2/",
      "/data/Zb/ZZ/4_2_4/S4/TuneZ2/",
      "/data/Zb/WZ/4_2_4/S4/TuneZ2/",
      "/data/Zb/WW/4_2_4/S4/TuneZ2/",
      "/data/Zb/DYJetsToLL/4_2_4/S4/TuneZ2/lFlav/", 
      "/data/Zb/DYJetsToLL/4_2_4/S4/TuneZ2/cFlav/",
      "/data/Zb/DYJetsToLL/4_2_4/S4/TuneZ2/bFlav/");

  vector<string> sampleNamesMC = StringVecify(nMC,
      "tt",
      "ZZ",
      "WZ",
      "WW",
      "Z+l",
      "Z+c",
      "Z+b");
  
  vector<double> initialMC = Vecify<double>(nMC,
      3701947.,
      4187885.,
      4265243.,
      4225916.,
      36277961.,
      36277961.,
      36277961.);

  vector<double> xsMC = Vecify<double>(nMC,
      157.5,
      6.4,
      19.79,
      43.0,
      3048.0,
      3048.0,
      3048.0);


  ofstream outFile;
  outFile.open("YieldTable.tex");
  LatexTable table;


  string samplePathData = "/data/Zb/DoubleMu/4_2_4/Combined/";
  TFile* f = new TFile(((samplePathData + "YieldStats_mm.root").c_str()));
  if (!f) {
    std::cerr << "File Not Found: " << (samplePathData + "YieldStats_mm.root");
  }

  YieldStats yieldsData = LoadViaTree<YieldStats>(*f,"PU_TP_BTAG_RW");
  yieldsData.SetSampleName("Data");
  f->Close();
  

  vector<YieldStats> yieldsMC;
  for (unsigned i = 0; i < nMC; ++i){
    TFile *f = new TFile(((samplePathsMC[i] + "YieldStats_mm.root").c_str()));
  if (!f) {
    std::cerr << "File Not Found: " << (samplePathsMC[i] + "YieldStats_mm.root");
  }
    yieldsMC.push_back(LoadViaTree<YieldStats>(*f,"PU_TP_RW"));
    yieldsMC.at(i).SetSampleName(sampleNamesMC[i]);
    f->Close();
  }
  
  for (unsigned i = 0; i < nMC; ++i){
    std::cout << initialMC[i] << std::endl;
    table.AddYieldStats(yieldsMC.at(i), 0, initialMC[i], xsMC[i]);
  }
  table.AddYieldStats(yieldsData, 1);
  table.SpecifySteps(true);
  table.SetStepsToShow(StringVecify(6,"lep_pair","lep_trigmatch","jet_pteta","jet_btag_HE","jet_btag_exclusive_HE", "jet_2btag_HE"));
  table.SetCaptionBegin("Double Muon");
  LatexTable table2 = table;

  table.SetTargetLumi(2111);
  //table.RestrictToRunRange(true);
  //table.SetRunRange(0,168437);
  table2.SetTargetLumi(970);
  table2.RestrictToRunRange(true);
  table2.SetRunRange(168438,1000000);
  //table.ScaleMc(false);
  //table.SpecifyBinsToSum(true);
  //table.SetBinsToSum(StringVecify(1,"low_pu"));

  table.MakeTable(std::cout);
  table2.MakeTable(std::cout);
  outFile.close();

  return 0;
}
