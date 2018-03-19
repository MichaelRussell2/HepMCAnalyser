# HepMCAnalyser

A C++ program for analysing hepmc files

## Prerequisites

   * [FastJet](http://fastjet.fr/) v3.x.x  
   * [HepMC](http://lcgapp.cern.ch/project/simu/HepMC/) v2.x.x  
   * and that's it!  

## Instructions

   1. Add path to HepMC headers and libraries to Makefile  
   2. FastJet headers and libraries will be found automatically with `fastjet-config`  
   3. Book histograms, add cuts etc. in analysis.cc  
   4. `make` to compile, then run `analysis <eventfile.hepmc>` to plot events  
