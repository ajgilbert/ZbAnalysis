#include "HbbEventSplitter.h"
#include "boost/lexical_cast.hpp"
#include "TFile.h"


namespace ajg {

  HbbEventSplitter::HbbEventSplitter(std::string const& name) : ModuleBase(name) {
    do_particles_ = true;
    do_genjets_ = true;
    do_partonjets_ = true;
    do_electrons_ = true;
    do_muons_ = true;
    do_pfJets_ = true;
    do_vertices_ = true;
    split_every_ = 100000;
    file_name_ = "ModularTree";
    current_index_ = 1;
    processed_events_ = 0;
    outfile = NULL;
    outtree = NULL;
  }

  HbbEventSplitter::~HbbEventSplitter() {
    ;
  }

  int HbbEventSplitter::PreAnalysis() {
    SetupNewFile();
    return 0;
  }

  int HbbEventSplitter::Execute(TreeEvent *event) {
    if (processed_events_ != 0 &&
      processed_events_%split_every_ == 0) SetupNewFile();
    HbbAnalysis::HbbEvent *hbbevent = 
      event->Get<HbbAnalysis::HbbEvent*>("HbbEvent");
    particles_    = &hbbevent->particles();
    genjets_      = &hbbevent->genjets();
    partonjets_   = &hbbevent->partonjets();
    electrons_    = &hbbevent->electrons();
    muons_        = &hbbevent->muons();
    pfJets_       = &hbbevent->pfJets();
    vertices_     = &hbbevent->vertices();
    outtree->Fill();
    ++processed_events_;
    return 0;
  }

  int HbbEventSplitter::PostAnalysis() {
    outfile->cd();
    outtree->Write();
    delete outtree;
    if (outfile) outfile->Close();
    delete outfile;
    return 0;
  }

  void HbbEventSplitter::PrintInfo() {
    std::cout << "Module: " << ModuleName() << " (HbbEventSplitter)" << std::endl;
  }

  void HbbEventSplitter::SetupNewFile() {
    if (outfile) {
      outfile->cd();
      outtree->Write();
      delete outtree;
      outfile->Close();
      delete outfile;
    }
    outfile = new TFile((output_path_+file_name_+"_"
      +boost::lexical_cast<std::string>
      (current_index_)+".root").c_str(),
      "RECREATE");
      outtree = new TTree("HbbEvent","HbbEvent");
      if (do_particles_) outtree->Branch("particles_", &particles_);
      if (do_genjets_) outtree->Branch("genjets_", &genjets_);
      if (do_partonjets_) outtree->Branch("partonjets_", &partonjets_);
      if (do_electrons_) outtree->Branch("electrons_", &electrons_);
      if (do_muons_) outtree->Branch("muons_", &muons_);
      if (do_pfJets_) outtree->Branch("pfJets_", &pfJets_);
      if (do_vertices_) outtree->Branch("vertices_", &vertices_);


    ++current_index_;
  }
}
