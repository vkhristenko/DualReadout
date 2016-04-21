#ifndef DREVENTACTION_H
#define DREVENTACTION_H 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4Event.hh"
#include "G4Timer.hh"

class DREventAction : public G4UserEventAction
{
	public:
		DREventAction();
		~DREventAction();

		void BeginOfEventAction(const G4Event*);
		void EndOfEventAction(const G4Event*);

		G4Timer *timer;
};

#endif
