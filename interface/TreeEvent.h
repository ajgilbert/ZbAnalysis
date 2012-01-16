#ifndef __ajg_TreeEvent__
#define __ajg_TreeEvent__

#include <map>
#include <string>
#include <iostream>


#include "EventBase.h"
#include "BranchHandler.h"
#include "boost/function.hpp"
#include "boost/bind.hpp"
#include "TTree.h"



namespace ajg {

  class TreeEvent : public EventBase {

  private:
    std::map<std::string, BranchHandlerBase*> handlers_;
    std::map<std::string, boost::function<void (unsigned)> > on_demand_funcs_;
    std::vector<boost::function<void (unsigned)> > auto_add_funcs_;
    TTree *tree_;
    unsigned event_;

    template <class T>
    void AutoCopy(std::string name, unsigned event) {
      handlers_[name]->GetEntry(event);
      T* ptr = (dynamic_cast<BranchHandler<T>* >(handlers_[name]))->GetPtr();
      ForceAdd(name, ptr);
    }

    template <class T>
    void AutoCopyPtrVec(std::string name, unsigned event) {
      handlers_[name]->GetEntry(event);
      std::vector<T> *ptr = (dynamic_cast<BranchHandler<std::vector<T> >* >(handlers_[name]))->GetPtr();
      std::vector<T *> temp_vec(ptr->size(), NULL);
      for (unsigned i = 0; i < ptr->size(); ++i) {
        temp_vec[i] = &((*ptr)[i]);
      }
      ForceAdd(name, temp_vec);
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

    template <class T>
    void AddBranch(std::string name) {
      BranchHandler<T> * handler = new BranchHandler<T>(tree_, name);
       handler->SetAddress();
      handlers_[name] = handler;
      on_demand_funcs_[name] = boost::bind(
        &TreeEvent::AutoCopy<T>,this, name, _1);
    }

    template <class T>
    void AddBranchPtrVec(std::string name) {
      BranchHandler<std::vector<T> > * handler = 
        new BranchHandler<std::vector<T> >(tree_, name);
       handler->SetAddress();
      handlers_[name] = handler;
      on_demand_funcs_[name] = boost::bind(
        &TreeEvent::AutoCopyPtrVec<T>,this, name, _1);
    }



    template <class T>
    T & Get(std::string const& name) {
      if (Exists(name)) {
        return EventBase::Get<T>(name);
      } else {
        if (on_demand_funcs_.count(name)) {
          on_demand_funcs_[name](event_);
          return EventBase::Get<T>(name);
        } else {
        std::cerr << "Error: Attempt to get product with name \"" 
        << name << "\" failed, no product with this name exists."
        << std::endl;
        std::cerr << "An exception will be thrown." << std::endl;
          throw;          
        }
      }
      
    }

    void SetEvent(unsigned event);

    void SetTree(TTree *tree) { tree_ = tree; }



  
    


  };
}

#endif
