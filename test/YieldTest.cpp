#include <iostream>
#include <vector>
#include <map>

#include "TEfficiency.h"

#include "YieldStats.hh"
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
  stats.SetStepNames(StringVecify(2,"Lepton Pair","Jet ID"));
  stats.SetBinNames(StringVecify(1, "all"));
  stats.IncrementCount(1,0,0,202011);
  stats.IncrementCount(1,0,1,55868);
  stats.Print();

  YieldStats statsC("Z+c","NO_RW");
  statsC.SetStepNames(StringVecify(2,"Lepton Pair","Jet ID"));
  statsC.SetBinNames(StringVecify(1, "all"));
  statsC.IncrementCount(1,0,0,933108);
  statsC.IncrementCount(1,0,1,204167);
  statsC.Print();
  
  YieldStats statsD("Data","NO_RW");
  statsD.SetStepNames(StringVecify(2,"Lepton Pair","Jet ID"));
  statsD.SetBinNames(StringVecify(1, "all"));
  statsD.IncrementCount(1,0,0,702259);
  statsD.IncrementCount(1,0,1,135967);
  statsD.Print();


  LatexTable table;
  table.AddYieldStats(stats,0,1557370,135.3);
  table.AddYieldStats(statsC,0,8606279,748.1);
  table.AddYieldStats(statsD,1,21180497);
  table.SetTargetLumi(2130);
  table.SetCaptionBegin("Double Electron");
  table.MakeTable();

  return 0;
}
