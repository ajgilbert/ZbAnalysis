#include "TreeEvent.h"

namespace ajg {


  TreeEvent::TreeEvent() {
    event_ = 0;
  }

  TreeEvent::~TreeEvent() {
    ;
  }


  void TreeEvent::SetEvent(unsigned event) {
    event_ = event;
    Clear();
    for (unsigned i = 0; i < auto_add_funcs_.size(); ++i) {
      auto_add_funcs_[i](event);
    }
  }

}