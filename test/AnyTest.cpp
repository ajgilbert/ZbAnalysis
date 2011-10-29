#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "boost/any.hpp"
#include "TLorentzVector.h"

using boost::any;
using boost::any_cast;

class AnyMap {
  public:
    AnyMap() {;}

    template <class T>
      T & MakeProduct(std::string name) {
        anyMap_[name] = T();
        return any_cast<T&>(anyMap_[name]);
      }
    
    template <class T>
      T & MakeProduct(std::string name, T const& inProd) {
        anyMap_[name] = inProd;
        return any_cast<T&>(anyMap_[name]);
      }

    template <class T>
      T const& GetProduct(std::string name) {
        return any_cast<T const&>(anyMap_[name]);
      }

    template <class T>
      T & GetProductMutable(std::string name) {
        return any_cast<T &>(anyMap_[name]);
      }
  private:
    std::map<std::string, any> anyMap_;

};

int main(int argc, char* argv[]){

  std::cout << "Hello World!" << std::endl;
  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }


  AnyMap anyMap;
  
  double & a = anyMap.MakeProduct<double>("a");
  std::cout << a << std::endl;
  a = 5.5;
  std::cout << a << std::endl;

  double & b = anyMap.GetProductMutable<double>("a");

  anyMap.MakeProduct("vec",TLorentzVector(4,3,2,1));
  TLorentzVector const& vec = anyMap.GetProduct<TLorentzVector>("vec");
  vec.Print();
  
  std::cout << b << std::endl;

  
  return 0;
}
