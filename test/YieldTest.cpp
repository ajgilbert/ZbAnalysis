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
 
  TEfficiency eff;
  double total = 21180497;
  //double total = 702259;
  double pass = 135967;
  double upperEff = eff.ClopperPearson(total,pass,0.683 ,1);
  double lowerEff = eff.ClopperPearson(total,pass,0.683 ,0);
  std::cout << pass << "/" << total << ": " << pass/total << std::endl;
  std::cout << "--Upper: " << upperEff << "\t" << upperEff*total << "\t" << (upperEff*total)-pass << std::endl;
  std::cout << "--Lower: " << lowerEff << "\t" << lowerEff*total << "\t" << (lowerEff*total)-pass << std::endl;


  YieldStats stats("Z+b","NO_RW");
  stats.SetStepNames(StringVecify(4,"step1","step2","step3","step4"));
  stats.SetBinNames(StringVecify(3, "split1","split2","split3"));
  stats.IncrementCount(1000,0,0,1);
  stats.IncrementCount(1000,1,1,2);
  stats.IncrementCount(2000,3,0,3);
  stats.IncrementCount(2000,2,2,4);
  stats.IncrementCount(3000,1,2,5);
  stats.IncrementCount(3000,0,1,6);
  stats.Print();

  YieldStats statsD("Data","NO_RW");
  statsD.SetStepNames(StringVecify(4,"step1","step2","step3","step4"));
  statsD.SetBinNames(StringVecify(3, "split1","split2","split3"));
  statsD.IncrementCount(1000,2,2,1);
  statsD.IncrementCount(1000,1,0,2);
  statsD.IncrementCount(2000,0,2,3);
  statsD.IncrementCount(2000,0,1,4);
  statsD.IncrementCount(3000,1,1,5);
  statsD.IncrementCount(3000,3,2,6);
  statsD.Print();


  LatexTable table;
  table.AddYieldStats("Z+b",stats);
  table.AddYieldStats("Data",statsD);
  //table.RestrictToRunRange(2000,3000);
  //std::vector<std::string> splits;
  //splits.push_back("split2");
  //table.CombineSplitsByName(splits);
  table.MakeTable();

  return 0;
}
