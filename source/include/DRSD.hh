#ifndef DRSD_H
#define DRSD_H 1

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "globals.hh"

#include <vector>
#include <string>

#include "TTree.h"
#include "TH1D.h"
#include "TRandom.h"

#include "DRDefs.hh"

using namespace std;

#define NUMLAYERS 500

//	Define the SD Class
//
class DRSD : public G4VSensitiveDetector
{
	public:
		DRSD(G4String, TTree* tree, RunParameters params);
		virtual ~DRSD();

		void Initialize(G4HCofThisEvent*);
		G4bool ProcessHits(G4Step*, G4TouchableHistory*);
		void EndOfEvent(G4HCofThisEvent*);
		
		//	Returns QE based on the lyambda 
		//	Interpolates the QE Array provided by Burak
		//
		double GetPENum(double lyambda);
		double ComputePE(int b1, int b2, double x);
		int GetPMT(G4String name);
		int ComputeOP(double ene, double yield);

		//	Members
		//
		Double_t numPhotonsPerLayer[NUMLAYERS];
		Double_t numPhotons;
		TTree *_tree;
		RunParameters _parameters;
		TRandom rand;
		G4String _name;


};

#endif
