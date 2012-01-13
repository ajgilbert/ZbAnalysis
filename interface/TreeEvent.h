#ifndef __ajg_TreeEvent__
#define __ajg_TreeEvent__

#include <map>
#include <string>
#include <iostream>
#include "boost/any.hpp"
#include "EventBase.h"
#include "BranchHandler.h"
#include "boost/function.hpp"
#include "boost/bind.hpp"
#include "TTree.h"



namespace ajg {


  class TreeEvent : public EventBase {

  private:
    std::map<std::string, BranchHandlerBase*> handlers_;
    std::vector<boost::function<void (unsigned)> > auto_add_funcs_;
    TTree *tree_;

    template <class T>
    void AutoCopy(std::string name, unsigned event) {
      handlers_[name]->GetEntry(event);
      T* ptr = (dynamic_cast<BranchHandler<T>* >(handlers_[name]))->GetPtr();
      ForceAdd(name, ptr);
    }






  public:
    TreeEvent();
    virtual ~TreeEvent();

    template <class T>
    void AutoAddBranch(std::string name) {
      BranchHandler<T> * handler = new BranchHandler<T>(tree_, name);
      handler->SetAddress();
      handlers_[name] = handler;
      auto_add_funcs_.push_back(boost::bind(
        &TreeEvent::AutoCopy<T>,this, name, _1));
    }

    void SetEvent(unsigned event);

    void SetTree(TTree *tree) { tree_ = tree; }



  
    


  };
}

#endif
