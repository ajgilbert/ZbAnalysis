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
#include "TreeEvent.h"


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

template <class T>
void PrintDefault() {
  T x;
  std::cout << typeid(x).name() << std::endl;
}

int main(int argc, char* argv[]){

  std::cout << "Hello World!" << std::endl;
  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }

  int status;
  boost::any abc = std::vector<TLorentzVector*>();
  std::string realname = abi::__cxa_demangle(abc.type().name(), 0, 0, &status);
  
  std::cout << abc.type().name() << std::endl;
  std::cout << realname << std::endl;
  std::cout << status << std::endl;

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

  boost::function<void (void)> f1 = &PrintDefault<double>;
  boost::function<void (void)> f2 = &PrintDefault<int>;
  f1();
  f2();

  ajg::EventBase base;
  double x = 10;
  std::vector<int> t_vec(4,10);
  base.Add("test_object", x);
  base.Add("some_vector", &t_vec);
  base.Add("some_function", &f1);
  std::cout << "Listing Products in Event:" << std::endl;
  base.List();

  TFile f("test.root");
  TTree* tree = (TTree*)f.Get("test");



  ajg::TreeEvent event;
  event.SetTree(tree);
  event.AutoAddBranch<TLorentzVector>("tlv");
  for (unsigned i = 0; i < tree->GetEntries(); ++i) {
  event.SetEvent(i);
    TLorentzVector *tlv = event.Get<TLorentzVector*>("tlv");
      tlv->Print();


}
  event.List();
  //double z = base.Get<double>("test_object");






  
  return 0;
}
