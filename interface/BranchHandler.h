#ifndef __ZBANALYSIS__BRANCHHANDLER__
#define __ZBANALYSIS__BRANCHHANDLER__

#include "BranchHandlerBase.h"

#include <string>

#include "TTree.h"

namespace ZbAnalysis{

//! An abstract base class for the automatic handling of branches in a TTree
/*! 
 Some text. 
 */
  template <class T>
    class BranchHandler : public BranchHandlerBase{
      private:
        T* ptr_;

      public:
        BranchHandler(){
          SetBranchPtr(0);
          ptr_ = 0;
        }
        BranchHandler(TTree* tree, std::string branch_name){
          SetBranchPtr(tree->GetBranch(branch_name.c_str()));
          ptr_ = 0;
        }
        void SetAddress(){
          GetBranchPtr()->SetAddress(&ptr_);
        }
        T* GetPtr(){
          return ptr_;
        }
    };
}

#endif
