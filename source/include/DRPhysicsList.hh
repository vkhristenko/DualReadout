#ifndef DRPHYSICSLIST_H
#define DRPHYSICSLIST_H 1

#include "globals.hh"
#include "G4VUserPhysicsList.hh"
#include "G4VPhysicsConstructor.hh"

#include "DRDefs.hh"

class G4Cerenkov;
class G4OpAbsorption;
class G4OpRayleigh;
class G4OpMieHG;
class G4OpBoundaryProcess;
class G4Scintillation;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DRPhysicsList : public G4VPhysicsConstructor
{
  public:
    DRPhysicsList();
    virtual ~DRPhysicsList();

  public:
    virtual void ConstructParticle();
    virtual void ConstructProcess();

//    virtual void SetCuts();

    //these methods Construct physics processes and register them
 //   void ConstructDecay();
//    void ConstructEM();
    void ConstructOp();
	void SetRunParameters(RunParameters);

    //for the Messenger 
    void SetVerbose(G4int);
//    void SetNbOfPhotonsCerenkov(G4int);
 
  private:
    G4Cerenkov*          fCerenkovProcess;
	G4Scintillation *fScintillationProcess;
	G4OpAbsorption *fAbsorptionProcess;
	G4OpRayleigh *fRayleighScatteringProcess;
	G4OpMieHG *fMieHGScatteringProcess;
	G4OpBoundaryProcess *fBoundaryProcess;
	RunParameters _params;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /* CPHYSICSLIST_H */
