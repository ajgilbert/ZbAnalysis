#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "TEfficiency.h"

#include "UserCode/HbbAnalysis/interface/YieldStats.hh"
#include "LatexTable.hh"
#include "MiscFunctions.hh"

using namespace HbbAnalysis;


int main(int argc, char* argv[]){

  std::cout << "Hello World!" << std::endl;
  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }

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


  ofstream outFile;
  outFile.open("YieldTable.tex");
  LatexTable table;
  table.AddYieldStats(stats,0,1557370,135.3);
  table.AddYieldStats(statsC,0,8606279,748.1);
  table.AddYieldStats(statsD,1,21180497);
  table.SetTargetLumi(2130);
  //table.SpecifySteps(true);
  table.ScaleMc(false);
  //table.SetStepsToShow(StringVecify(2,"Lepton Pair","Jet ID"));
  table.SetCaptionBegin("Double Electron");
  table.MakeTable(std::cout);
  outFile.close();
  std::map<std::string,int> testMap;

  return 0;
}
