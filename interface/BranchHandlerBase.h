#ifndef __ZBANALYSIS__BRANCHHANDLERBASE__
#define __ZBANALYSIS__BRANCHHANDLERBASE__

#include "TBranch.h"

//! An abstract base class for the automatic handling of branches in a TTree
/*! 
 Some text. 
 */
namespace ZbAnalysis{

  class BranchHandlerBase{
    private:
      TBranch* branch_ptr_;

    public:
      virtual void SetAddress() = 0;
      void GetEntry(unsigned i){
        branch_ptr_->GetEntry(i);
      }
      void SetBranchPtr(TBranch* ptr){
        branch_ptr_ = ptr;
      }

      TBranch* GetBranchPtr(){
        return branch_ptr_;
      }

  };
}

#endif
