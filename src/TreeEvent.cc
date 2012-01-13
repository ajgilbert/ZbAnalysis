#include "TreeEvent.h"
#include <string>
#include <algorithm>
#include <map>
#include <cxxabi.h>


namespace ajg {


  TreeEvent::TreeEvent() {
    ;
  }

  TreeEvent::~TreeEvent() {
    ;
  }


  void TreeEvent::SetEvent(unsigned event) {
    for (unsigned i = 0; i < auto_add_funcs_.size(); ++i) {
      auto_add_funcs_[i](event);
    }
  }



}