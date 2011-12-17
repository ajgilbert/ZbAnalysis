#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include "boost/bind.hpp"

void adder(double x, double y){
  std::cout << (x+y) << std::endl;
}

int main(int argc, char* argv[]){

  std::cout << "Hello World!" << std::endl;
  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }
  

  typedef std::pair<double,double> p_d_d;
  std::vector<std::pair<double,double> > pairs;
  pairs.push_back(std::make_pair(5.0,4.0));
  pairs.push_back(std::make_pair(10.0,11.0));
  pairs.push_back(std::make_pair(18.0,17.0));

  std::for_each(pairs.begin(),pairs.end(),boost::bind(&adder, 
        boost::bind(&p_d_d::first, _1), 
        boost::bind(&p_d_d::second, _1)));

  return 0;
}
