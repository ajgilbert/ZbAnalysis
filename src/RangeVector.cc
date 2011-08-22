#include "RangeVector.h"
#include <vector>
#include <algorithm>
#include <iostream>


RangeVector::RangeVector(){
  ;
}

RangeVector::RangeVector(std::vector<double> const& _lower, std::vector<double> const& _upper){
  lower = _lower;
  upper = _upper;
}

void RangeVector::AddUpper(std::vector<double> const& _upper){
  upper = _upper;
}

void RangeVector::AddLower(std::vector<double> const& _lower){
  lower = _lower;
}

void RangeVector::push_back(double _lower, double _upper){
  lower.push_back(_lower);
  upper.push_back(_upper);
}

unsigned RangeVector::size() {
  if (lower.size() == upper.size()) {
    return lower.size();
  } else {
    return 0;
  }
}

bool RangeVector::ConsistencyCheck(bool output){
  if (upper.size() != lower.size()){
    if (output) std::cout << "Error: Size mismatch between upper and lower vectors" << std::endl;
    return false;
  }
  if ((upper.size()==0) || (lower.size()==0)){
    if (output) std::cout << "Error: Range vector is empty" << std::endl;
    return false;
  }
  for (unsigned i = 0; i < upper.size(); ++i){
    if (upper[i] < lower[i]){
      if (output) std::cout << "Error: Bin " << i << " has " <<  upper[i] << " for the upper value and " << lower[i] << " for the lower value." << std::endl;
      return false;
    }
  }
    return true;
}

double RangeVector::GetLower(unsigned i){
  return lower.at(i);
}
double RangeVector::GetUpper(unsigned i){
  return upper.at(i);
}

double RangeVector::GetCentral(unsigned i){
  return (upper.at(i) + lower.at(i)) / 2.0;
}

double RangeVector::GetWidth(unsigned i){
  return (upper.at(i) - lower.at(i));
}

int RangeVector::GetBin(double val){
  std::vector<double>::iterator result;
  result = std::upper_bound(upper.begin(),upper.end(), val);
  if (result==upper.end()){
    return -1;
  } else {
    unsigned index = int(result - upper.begin());
    if ( (val >= lower.at(index)) && (val < upper.at(index)) ){
      return index;
    } else {
      return -1;
    }
  }
}



