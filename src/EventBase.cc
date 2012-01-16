#include "EventBase.h"
#include <string>
#include <algorithm>
#include <map>
#include <cxxabi.h>


namespace ajg {

  EventBase::EventBase() {
    ;
  }

  EventBase::~EventBase() {
    ;
  }

  bool EventBase::Exists(std::string const& name) {
    if (products_.count(name)) {
      return true;
    } else {
      return false;
    }
  }

  void EventBase::List() {
    std::map<std::string, boost::any>::const_iterator it;
    for (it = products_.begin(); it != products_.end(); ++it) {
      int status;
      std::string realname = abi::__cxa_demangle(it->second.type().name(), 0, 0, &status);
      std::cout << it->first << "\t\t\t" << realname << std::endl;
    }
  }

  void EventBase::Clear() {
    products_.clear();
  }

  unsigned int EventBase::Remove(std::string const& name) {
    if (!Exists(name)) {
      return 1;
    } else {
      products_.erase(name);
      return 0;
    }
  }
 
}