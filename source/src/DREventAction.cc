#include "DREventAction.hh"

#include <iostream>

using namespace std;

DREventAction::DREventAction()
{
	timer = new G4Timer();
}

DREventAction::~DREventAction()
{
	delete timer;
}

void DREventAction::BeginOfEventAction(const G4Event* anEvent)
{
	G4cout << "### Starting Event: " << anEvent->GetEventID() << endl;
	timer->Start();
}

void DREventAction::EndOfEventAction(const G4Event*)
{
	timer->Stop();
	G4cout << "### Event Duration: " << *timer << G4endl;
}
