//example hepmc reader

#include <utils.hh>
#include <histo.hh>

#include "HepMC/IO_GenEvent.h"
#include "HepMC/GenEvent.h"

#include <fastjet/PseudoJet.hh>
#include <fastjet/ClusterSequence.hh>
#include <fastjet/Selector.hh>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <utility>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

using namespace std;
using namespace fastjet;
using namespace FastPartons;

int main(int argc, char *argv[]) {

  if (argc != 2) {
    cout << "ERROR: Give HepMC file as argument" << endl;
    return 1;
  }
  string hepmcfile = argv[1];
  HepMC::IO_GenEvent ascii_in(hepmcfile,std::ios::in);
  HepMC::GenEvent* evt = ascii_in.read_next_event();

  double R_jet = 0.4;
  JetDefinition jet_def(antikt_algorithm, R_jet);
  Selector select_akt = SelectorAbsEtaMax(5.0) && SelectorPtMin(20.);

  double ETmiss;
  
  vector<PseudoJet> hadrons, electrons, muons, photons;

  //book histograms
  Histo h_ETmiss(0,2000,50);

  bool verbose = false;
  
  //begin event loop
  int icount = 0;
  while ( evt ) {
    
    if ( icount % 10000 == 0) cout << icount << endl;
    if (verbose) cout << "------------------------" << endl;
    if (verbose) cout << "Processing Event Number " << icount << endl;
    //    cout << "Its event weight " << evt->cross_section()->cross_section() << endl;

    PseudoJet visible(0.,0.,0.,0.);
    PseudoJet invisible(0.,0.,0.,0.);
    electrons.clear();
    muons.clear();
    photons.clear();
    hadrons.clear();
    
    //begin particle loop
    for ( HepMC::GenEvent::particle_iterator p = evt->particles_begin();
	  p != evt->particles_end(); ++p ) {
      
      //get final state particles:

      //hadrons and b-tagging
      if (isHadron(*p) && isFinal(*p)){
	int btag = isBHadron(*p) ? 1 : 0;
	PseudoJet tmp((*p)->momentum().px(),(*p)->momentum().py(), (*p)->momentum().pz(), (*p)->momentum().e());
	tmp.set_user_index(btag);
	hadrons.push_back(tmp);
	visible += tmp;
      }
      
      //photons
      if (isPhoton(*p) && isFinal(*p)){
	PseudoJet tmp((*p)->momentum().px(),(*p)->momentum().py(), (*p)->momentum().pz(), (*p)->momentum().e());
	photons.push_back(tmp);
	visible += tmp;
      }
      
      //electrons
      if (isElectron(*p) && isFinal(*p)){
	PseudoJet tmp((*p)->momentum().px(),(*p)->momentum().py(), (*p)->momentum().pz(), (*p)->momentum().e());
	electrons.push_back(tmp);
	visible += tmp;
      }
      
      //muons
      if (isMuon(*p) && isFinal(*p)){
	PseudoJet tmp((*p)->momentum().px(),(*p)->momentum().py(), (*p)->momentum().pz(), (*p)->momentum().e());
	muons.push_back(tmp);
	visible += tmp;
      }
      
    } //end particle loop
    
    //calculate ETmiss from visible final state
    ETmiss = visible.pt();
    
    //cluster hadrons into jets
    ClusterSequence cluster(hadrons, jet_def);
    vector<PseudoJet> antikT_jets = sorted_by_pt(select_akt(cluster.inclusive_jets()));

    //apply analysis cuts

    //fill histograms
    h_ETmiss.fill(ETmiss);
    
    icount++;

    //    if (icount > 1) break;
    delete evt;
    ascii_in >> evt;

  } //end event loop

  //write histograms to file
  h_ETmiss.write("ETmiss.dat");
  return 0;  
} //end main
