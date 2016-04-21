#include "DRRunAction.hh"

DRRunAction::DRRunAction()
{
	timer = new G4Timer;
}

DRRunAction::~DRRunAction()
{
	delete timer;
}

void DRRunAction::BeginOfRunAction(const G4Run* aRun)
{
	G4cout << "### Run " << aRun->GetRunID() << " start. " << G4endl;
	timer->Start();
}

void DRRunAction::EndOfRunAction(const G4Run *aRun)
{
	timer->Stop();
	G4cout << "Number of Events: " << aRun->GetNumberOfEvent()
		<< " took " << *timer << G4endl;
}
