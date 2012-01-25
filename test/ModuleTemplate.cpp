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
#include "TSystem.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "UserCode/HbbAnalysis/interface/HbbEvent.hh"

#include <iostream>
#include <fstream>

int main(int argc, char* argv[]){

  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }

  std::string name = argv[1];
  std::string header_path = argv[2];
  std::string implementation_path = argv[3];
  std::ifstream test_header;
  test_header.open( (header_path+name+".h").c_str(), std::ifstream::in );
  std::ifstream test_implementation;
  test_implementation.open( (header_path+name+".h").c_str(), std::ifstream::in );
  if (test_header.is_open() || test_implementation.is_open()) {
    std::cerr << "Error, files with this module name already exist" << std::endl;
    exit(0);
  }

  std::ofstream header;
  header.open( (header_path+name+".h").c_str() );
  std::ofstream implementation;
  implementation.open( (implementation_path+name+".cc").c_str() );

  header << "#ifndef __ajg_" << name << "__" << std::endl;
  header << "#define __ajg_" << name << "__" << std::endl;
  header << std::endl;
  header << "#include \"EventBase.h\"" << std::endl;
  header << "#include \"ModuleBase.h\"" << std::endl;
  header << "#include <string>" << std::endl;
  header << std::endl;
  header << "namespace ajg {" << std::endl;
  header << std::endl;
  header << "class " << name << " : public ModuleBase {" << std::endl;
  header << " private:" << std::endl;
  header << std::endl;
  header << " public:" << std::endl;
  header << "  " << name << "(std::string const& name);" << std::endl;
  header << "  virtual ~" << name << "();" << std::endl;
  header << std::endl;
  header << "  virtual int PreAnalysis();" << std::endl;
  header << "  virtual int Execute(TreeEvent *event);" << std::endl;
  header << "  virtual int PostAnalysis();" << std::endl;
  header << "};" << std::endl;
  header << "}" << std::endl;
  header << std::endl;
  header << "#endif" << std::endl;
  header.close();

  implementation << "#include \"" << name << ".h\"" << std::endl;
  implementation << std::endl;
  implementation << "namespace ajg {" << std::endl;
  implementation << std::endl;
  implementation << "  " << name << "::" << name << "(std::string const& name) : ModuleBase(name) {" << std::endl;
  implementation << "    ;" << std::endl;
  implementation << "  }" << std::endl;
  implementation << std::endl;
  implementation << "  " << name << "::~" << name << "() {" << std::endl;
  implementation << "    ;" << std::endl;
  implementation << "  }" << std::endl;
  implementation << std::endl;
  implementation << "  int " << name << "::" << "PreAnalysis() {" << std::endl;
  implementation << "    return 0;" << std::endl;
  implementation << "  }" << std::endl;
  implementation << std::endl;
  implementation << "  int " << name << "::" << "Execute(TreeEvent *event) {" << std::endl;
  implementation << "    return 0;" << std::endl;
  implementation << "  }" << std::endl;
  implementation << "  int " << name << "::" << "PostAnalysis() {" << std::endl;
  implementation << "    return 0;" << std::endl;
  implementation << "  }" << std::endl;
  implementation << "}" << std::endl;
  implementation.close();

  return 0;


}