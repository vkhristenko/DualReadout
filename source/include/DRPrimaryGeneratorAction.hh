


#ifndef DRPRIMARYGENERATORACTION_H
#define DRPRIMARYGENERATORACTION_H 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include "G4ios.hh"
#include "G4Event.hh"
#include "G4VPrimaryGenerator.hh"

#include "DRDefs.hh"

class DRPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
	public:
		//	Constructor and Destructor
		DRPrimaryGeneratorAction(RunParameters params);
		virtual ~DRPrimaryGeneratorAction();

		//	Standard func	
		void GeneratePrimaries(G4Event *anEvent);

		//	To keep things simplier
		G4ParticleGun *particleGun;
		G4String primName;
		G4double primEnergy;
		G4ThreeVector primPos;
		G4ThreeVector primDir;
		G4int verbosityLevel;

		RunParameters runParams;
};

#endif
