#ifndef __ajg_ElectronDemoModule__
#define __ajg_ElectronDemoModule__

#include "EventBase.h"
#include "ModuleBase.h"
#include <string>

namespace ajg {

class ElectronDemoModule : public ModuleBase {
 private:

 public:
  ElectronDemoModule(std::string const& name);
  virtual ~ElectronDemoModule();

  virtual int PreAnalysis();
  virtual int Execute(TreeEvent *event);
  virtual int PostAnalysis();
  virtual void PrintInfo();
};
}

#endif
