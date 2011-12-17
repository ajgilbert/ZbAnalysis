#include <iostream>
#include <vector>
#include <string>
#include "boost/regex.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/functional/hash.hpp"
#include <limits>

using namespace std;

int main(int argc, char* argv[]){

  std::cout << "Hello World!" << std::endl;
  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }
  



  std::string pattern = "453.*";
  boost::regex e(pattern);
  std::string test("XYZ");
  std::cout << boost::regex_match(boost::lexical_cast<std::string>(45300),e) << std::endl;
  
  

  
  
  return 0;
}
