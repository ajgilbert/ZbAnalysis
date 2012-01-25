#include "ElectronDemoModule.h"
#include "UserCode/HbbAnalysis/interface/HbbEvent.hh"

namespace ajg {

  ElectronDemoModule::ElectronDemoModule(std::string const& name) : ModuleBase(name) {
    ;
  }

  ElectronDemoModule::~ElectronDemoModule() {
    ;
  }

  int ElectronDemoModule::PreAnalysis() {
    std::cout << "Some pre analysis stuff" << std::endl;
    return 0;
  }

  int ElectronDemoModule::Execute(TreeEvent *event) {
    event->List();
    std::vector<HbbAnalysis::Electron *> & electrons =
      event->Get<std::vector<HbbAnalysis::Electron*> >("electrons");
    std::cout << "Found " << electrons.size() << " electrons." << std::endl;
    return 0;
  }

  int ElectronDemoModule::PostAnalysis() {
    std::cout << "Some post analysis stuff" << std::endl;
    return 0;
  }

  void ElectronDemoModule::PrintInfo() {
    std::cout << "Module: " << ModuleName() << " (ElectronDemoModule)" << std::endl;
  }
}
