#include "ModuleBase.h"

namespace ajg {
	
	ModuleBase::ModuleBase(std::string const& name) {
		module_name_ = name;
		events_processed_ = 0;
	}

	ModuleBase::~ModuleBase() {
		;
	}
}