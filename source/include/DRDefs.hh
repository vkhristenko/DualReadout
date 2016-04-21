#ifndef DRDEFS_H
#define DRDEFS_H

#include "globals.hh"
#include <vector>
#include "TROOT.h"
#include "TFile.h"
#include "TApplication.h"
#include "TTree.h"

#include "G4ThreeVector.hh"
#include "G4Material.hh"

using namespace std;

struct RunParameters
{
	int iEnergy;
	int iPrim;
	string drInputFileName;
	int numLayers;
	int isInteractive;
	int verbosity;
	int seed;
	int numEvents;
	int useParametrization;

	//
	//	This is some output info
	//
	TFile *rootFile;
	vector<TTree*> vTrees;
};

struct DRParameters
{
	G4double fullEMAbsZ;
	G4double fullEMAbsX;
	G4double fullEMAbsY;

	G4double fullEMScintZ;
	G4double fullEMScintX;
	G4double fullEMScintY;

	G4double fullEMCerZ;
	G4double fullEMCerX;
	G4double fullEMCerY;

	int numEMLayers;
	G4Material* mEMAbs;
	int emOnOff;

	G4double fullHADAbsZ;
	G4double fullHADAbsX;
	G4double fullHADAbsY;

	G4double fullHADScintZ;
	G4double fullHADScintX;
	G4double fullHADScintY;

	G4double fullHADCerZ;
	G4double fullHADCerX;
	G4double fullHADCerY;

	int numHADLayers;
	G4Material *mHADAbs;
	int hadOnOff;
};

#endif 
