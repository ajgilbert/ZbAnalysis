#ifndef __ajg_ModuleBase__
#define __ajg_ModuleBase__

#include "TreeEvent.h"
#include <string>

namespace ajg {

	class ModuleBase {

 private:
   std::string module_name_;
   unsigned events_processed_;

 public:
  ModuleBase(std::string const& name);
  virtual ~ModuleBase();
  inline void IncreaseProcessedCount() { ++events_processed_; }
  inline unsigned EventsProcessed() { return events_processed_; }

  virtual int PreAnalysis() = 0;
  virtual int Execute(EventBase *) = 0;
  virtual int PostAnalysis() = 0;

};
}

#endif