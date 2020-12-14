#!/bin/sh
export LHAPDF_DATA_PATH="/cvmfs/sft.cern.ch/lcg/external/lhapdfsets/current/"
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${PWD}/HepTools/LHAPDF/local/lib
alias compile="g++ -O3 -I/home/choij/workspace/ParticlePhysics/HepTools/LHAPDF-6.3.0/../LHAPDF/local/include -L/home/choij/workspace/ParticlePhysics/HepTools/LHAPDF-6.3.0/../LHAPDF/local/lib -lLHAPDF -pthread -std=c++14 -m64 -I/usr/include/root -L/usr/lib64/root -lGui -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic"
