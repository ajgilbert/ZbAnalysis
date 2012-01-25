#ifndef __ajg_HbbEventSplitter__
#define __ajg_HbbEventSplitter__

#include "EventBase.h"
#include "ModuleBase.h"
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "UserCode/HbbAnalysis/interface/HbbEvent.hh"

namespace ajg {

class HbbEventSplitter : public ModuleBase {
 private:

  TFile *outfile;
  TTree *outtree;
  unsigned current_index_;
  unsigned processed_events_;
  std::vector<HbbAnalysis::GenParticle> *particles_;
  std::vector<HbbAnalysis::GenJet> *genjets_;
  std::vector<HbbAnalysis::GenJet> *partonjets_;
  std::vector<HbbAnalysis::Electron> *electrons_;
  std::vector<HbbAnalysis::Muon> *muons_;
  std::vector<HbbAnalysis::Jet> *pfJets_;
  std::vector<HbbAnalysis::Vertex> *vertices_;

 public:
  HbbEventSplitter(std::string const& name);
  virtual ~HbbEventSplitter();

  virtual int PreAnalysis();
  virtual int Execute(TreeEvent *event);
  virtual int PostAnalysis();
  virtual void PrintInfo();
  void SetupNewFile();

  bool do_particles_;
  bool do_genjets_;
  bool do_partonjets_;
  bool do_electrons_;
  bool do_muons_;
  bool do_pfJets_;
  bool do_vertices_;
  std::string output_path_;
  std::string file_name_;
  unsigned split_every_;
};
}

#endif
