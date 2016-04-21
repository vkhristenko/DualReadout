/*
 *	DualReadout Simulation
 *	Author: VK
 *	Date: 08/30/2014
 *	Description:
 *
 * */


#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "Randomize.hh"

#include "QBBC.hh"
//#include "QGSP.hh"

#include "DRDetectorConstruction.hh"
#include "DRPrimaryGeneratorAction.hh"
#include "DREventAction.hh"
#include "DRRunAction.hh"
#include "DRDefs.hh"
#include "DRPhysicsList.hh"
#include "DRSteppingAction.hh"

#include <time.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4ios.hh"
#include "globals.hh"
#include "G4UnitsTable.hh"

#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"

using namespace std;
using namespace CLHEP;

/*
 *	Main Function:
 *	Input Format:
 *		
 *
 */
int main(int argc, char** argv)
{
	//	Parse all the input
	//
	RunParameters runParams;
	runParams.isInteractive = atoi(argv[1]);
	runParams.iEnergy = 0;
	runParams.numEvents = 10;
	runParams.seed = 1;
	runParams.verbosity = 5;
	runParams.iPrim = 0;
	runParams.useParametrization = 0;
	runParams.drInputFileName = string("drConfig");

	if (!runParams.isInteractive)
	{
		runParams.iEnergy = atoi(argv[2]);
		runParams.numEvents = atoi(argv[3]);
		runParams.seed = atoi(argv[4]);
		runParams.verbosity = atoi(argv[5]);
		runParams.drInputFileName = argv[6];
		runParams.iPrim = atoi(argv[7]);
		runParams.useParametrization = atoi(argv[8]);
	}

	//	Initialize Random Number Generator
	//
	CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
//	CLHEP::HepRandom::setTheSeed(time(NULL));
	CLHEP::HepRandom::setTheSeed(runParams.seed);
	CLHEP::HepRandom::showEngineStatus();

	//	Initialize ROOT Output/ EM, FH, BH parts are separate...
	//	As of V5.
	//
	char rootOutFile[200];
	sprintf(rootOutFile, "DR_%d_%d_%d_%d_%d.root", runParams.iEnergy,
			runParams.seed, runParams.numEvents, runParams.iPrim,
			runParams.useParametrization);
	TFile *rootFile = new TFile(rootOutFile, "RECREATE");
	rootFile->mkdir("EM");
	rootFile->cd("EM");
	gDirectory->mkdir("S");
	gDirectory->mkdir("C");

	rootFile->cd("EM/S");
	TTree *sEMTree = new TTree("Events", "Events");
	rootFile->cd("EM/C");
	TTree *cEMTree = new TTree("Events", "Events");

	rootFile->mkdir("HAD");
	rootFile->cd("HAD");
	gDirectory->mkdir("S");
	gDirectory->mkdir("C");

	rootFile->cd("HAD/S");
	TTree *sHADTree = new TTree("Events", "Events");
	rootFile->cd("HAD/C");
	TTree *cHADTree = new TTree("Events", "Events");

	runParams.vTrees.push_back(sEMTree);
	runParams.vTrees.push_back(cEMTree);
	runParams.vTrees.push_back(sHADTree);
	runParams.vTrees.push_back(cHADTree);

	//	Initialize G4 Classes
	//
	G4RunManager *runManager = new G4RunManager;
	DRDetectorConstruction *detector = 
//		new SHDetectorConstruction(runParams, shashlikTree);
		new DRDetectorConstruction(runParams);
	runManager->SetUserInitialization(detector);
	
	G4PhysListFactory factory;
	G4VModularPhysicsList *phys = factory.GetReferencePhysList("FTFP_BERT");
	DRPhysicsList *drPhysicsList = new DRPhysicsList();
	drPhysicsList->SetRunParameters(runParams);
	phys->RegisterPhysics(drPhysicsList);	
//	SHPhysicsList *phys = new SHPhysicsList();
	runManager->SetUserInitialization(phys);

	DRPrimaryGeneratorAction *primAction = 
		new DRPrimaryGeneratorAction(runParams);
	runManager->SetUserAction(primAction);

	// optional user action Classes
	//
	DREventAction *eventAction = new DREventAction();
	DRRunAction *runAction = new DRRunAction();
	DRSteppingAction *steppingAction = new DRSteppingAction(runParams);
	runManager->SetUserAction(runAction);
	runManager->SetUserAction(eventAction);
	runManager->SetUserAction(steppingAction);


	// Init G4 Kernel
	//
	runManager->Initialize();
	G4UImanager *UI = G4UImanager::GetUIpointer();

	if (runParams.isInteractive)
	{
		G4VisManager *visManager = 0;
		#ifdef G4VIS_USE
			//	Visualization
			//
			visManager = new G4VisExecutive;
			visManager->Initialize();
		#endif

		#ifdef G4UI_USE
			G4UIExecutive *ui = new G4UIExecutive(argc, argv);
			ui->SessionStart();
			delete ui;
		#endif
	}
	else
	{
		char cmd[200];
		sprintf(cmd, "/run/beamOn %d", runParams.numEvents);
		UI->ApplyCommand(cmd);
	}

	//	Finalize
	//
	delete runManager;
//	shFile->Print();
//	shFile->Write();
//	shFile->Close();

	rootFile->Write();
	rootFile->Close();
	return 0;
} 
