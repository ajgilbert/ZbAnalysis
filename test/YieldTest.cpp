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

  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }

  if (argc != 2) return 0;
  std::string flav = argv[1];
  std::string altflav;
  if (flav == "ee") altflav = "El";
  if (flav == "mm") altflav = "Mu";
  
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
  
  vector<string> outputFiles = StringVecify(8,
      "Main_Yields.tex",
      "LowPU_Yields.tex",
      "MedPU_Yields.tex",
      "HighPU_Yields.tex",
      "May10_Yields.tex", 
      "PromptV4_Yields.tex",
      "Aug05_Yields.tex",
      "PromptV6_Yields.tex");


  
  ofstream outFile;
  for (unsigned i = 0; i < outputFiles.size();++i){
    outputFiles[i] = flav + "_" + outputFiles[i];
  }
  LatexTable table;


  string samplePathData = "/data/Zb/Double"+altflav+"/4_2_4/Combined/";
  TFile* f = new TFile(((samplePathData + "YieldStats_"+flav+".root").c_str()));
  if (!f) {
    std::cerr << "File Not Found: " << (samplePathData + "YieldStats_"+flav+".root");
  }

  YieldStats yieldsData = LoadViaTree<YieldStats>(*f,"PU_TP_BTAG_RW");
  yieldsData.SetSampleName("Data");
  f->Close();
  

  vector<YieldStats> yieldsMC;
  for (unsigned i = 0; i < nMC; ++i){
    TFile *f = new TFile(((samplePathsMC[i] + "YieldStats_"+flav+".root").c_str()));
  if (!f) {
    std::cerr << "File Not Found: " << (samplePathsMC[i] + "YieldStats_"+flav+".root");
  }
    yieldsMC.push_back(LoadViaTree<YieldStats>(*f,"PU_TP_BTAG_RW"));
    yieldsMC.at(i).SetSampleName(sampleNamesMC[i]);
    f->Close();
  }
  
  for (unsigned i = 0; i < nMC; ++i){
    table.AddYieldStats(yieldsMC.at(i), 0, initialMC[i], xsMC[i]);
  }

  table.AddYieldStats(yieldsData, 1);
  table.SpecifySteps(true);
  table.SetStepsToShow(StringVecify(9,"lep_pair","lep_trigmatch","jet_pteta","jet_btag_HE","jet_btag_exclusive_HE", "jet_2btag_HE","jet_btag_HP","jet_btag_exclusive_HP", "jet_2btag_HP"));
  table.SetStepRename("lep_pair","Lept. Pair");
  table.SetStepRename("lep_trigmatch","Trig. Match");
  table.SetStepRename("jet_pteta","Jet $\\mathrm{p_{T}}$,$\\eta$");
  table.SetStepRename("jet_btag_HE","$\\geq 1$ b-Tag HE");
  table.SetStepRename("jet_btag_exclusive_HE","$= 1$ b-Tag HE");
  table.SetStepRename("jet_2btag_HE","$\\geq 2$ b-Tag HE");
  table.SetStepRename("jet_btag_HP","$\\geq 1$ b-Tag HP");
  table.SetStepRename("jet_btag_exclusive_HP","$= 1$ b-Tag HP");
  table.SetStepRename("jet_2btag_HP","$\\geq 2$ b-Tag HP");
  if (flav == "ee") table.SetCaptionBegin("Double Electron");
  if (flav == "mm") table.SetCaptionBegin("Double Muon");

  table.SetTargetLumi(2111);
  table.ScaleMc(false);
  //table.SpecifyBinsToSum(true);
  //table.SetBinsToSum(StringVecify(1,"low_pu"));

  outFile.open(outputFiles[0].c_str());
  table.MakeTable(outFile);
  outFile.close();

  LatexTable table_lowpu = table;
  table_lowpu.SpecifyBinsToSum(true);
  table_lowpu.SetBinsToSum(StringVecify(1,"low_pu"));

  LatexTable table_medpu = table;
  table_medpu.SpecifyBinsToSum(true);
  table_medpu.SetBinsToSum(StringVecify(1,"med_pu"));

  LatexTable table_highpu = table;
  table_highpu.SpecifyBinsToSum(true);
  table_highpu.SetBinsToSum(StringVecify(1,"high_pu"));

  outFile.open(outputFiles[1].c_str());
  table_lowpu.MakeTable(outFile);
  outFile.close();
  outFile.open(outputFiles[2].c_str());
  table_medpu.MakeTable(outFile);
  outFile.close();
  outFile.open(outputFiles[3].c_str());
  table_highpu.MakeTable(outFile);
  outFile.close();

  LatexTable table_may10 = table;
  table_may10.RestrictToRunRange(true);
  table_may10.SetRunRange(0,163869);
  table_may10.SetTargetLumi(215);

  LatexTable table_prv4 = table;
  table_prv4.RestrictToRunRange(true);
  table_prv4.SetRunRange(163870,170825);
  table_prv4.SetTargetLumi(926);

  LatexTable table_aug05 = table;
  table_aug05.RestrictToRunRange(true);
  table_aug05.SetRunRange(170826,172619);
  table_aug05.SetTargetLumi(316);

  LatexTable table_prv6 = table;
  table_prv6.RestrictToRunRange(true);
  table_prv6.SetRunRange(172620,1000000);
  table_prv6.SetTargetLumi(654);
  
  outFile.open(outputFiles[4].c_str());
  table_may10.MakeTable(outFile);
  outFile.close();

  outFile.open(outputFiles[5].c_str());
  table_prv4.MakeTable(outFile);
  outFile.close();

  outFile.open(outputFiles[6].c_str());
  table_aug05.MakeTable(outFile);
  outFile.close();

  outFile.open(outputFiles[7].c_str());
  table_prv6.MakeTable(outFile);
  outFile.close();





  //table2.MakeTable(std::cout);

  return 0;
}
