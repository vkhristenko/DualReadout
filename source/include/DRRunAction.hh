#ifndef DRRUNACTION_H
#define DRRUNACTION_H 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4Run.hh"
#include "G4Timer.hh"

class DRRunAction : public G4UserRunAction
{
	public:
		DRRunAction();
		~DRRunAction();

		void BeginOfRunAction(const G4Run* aRun);
		void EndOfRunAction(const G4Run* aRun);

		G4Timer *timer;
};

#endif
