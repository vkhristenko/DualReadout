#ifndef DRSTEPPINGACTION_H
#define DRSTEPPINGACTION_H 1

#include "globals.hh"
#include "G4UserSteppingAction.hh"

#include "DRDefs.hh"

class DRSteppingAction : public G4UserSteppingAction
{
  public:
    DRSteppingAction(RunParameters);
    virtual ~DRSteppingAction();

    virtual void UserSteppingAction(const G4Step*);

	RunParameters runParams;
};

#endif

