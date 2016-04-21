#include "DRSD.hh"
#include "G4UnitsTable.hh"
#include "G4TrackStatus.hh"
#include "G4VProcess.hh"

#include <iostream>

using namespace std;
using namespace CLHEP;

//	Constructor
//
DRSD::DRSD(G4String name, TTree *tree, RunParameters params)
	: G4VSensitiveDetector(name),
	_tree(tree),
	_parameters(params),
	_name(name)
{
//	_tree->Branch("numPhotons", &numPhotons, "numPhotons/D");
	_tree->Branch("numPhootonsPerLayer", 
			numPhotonsPerLayer, "numPhotonsPerLayer[300]/D");
}

//	Destructor
//
DRSD::~DRSD()
{

}

//	Initialize
//
void DRSD::Initialize(G4HCofThisEvent*)
{
	//	Clear
	//
	for (int ilayer=0; ilayer<NUMLAYERS; ilayer++)
		numPhotonsPerLayer[ilayer] = 0;
	numPhotons = 0;
}

//	Process Hits
//
G4bool DRSD::ProcessHits(G4Step *aStep, G4TouchableHistory*)
{
//	if (_parameters.useParametrization==0 || 
//			(_parameters.useParametrization==1 && (_name=="SD_EM_C" || 
//												   _name=="SD_HAD_C")))
//	{
		if (aStep->GetTrack()->GetParticleDefinition()->GetParticleName() == 
			"opticalphoton")
		{
			if (_parameters.verbosity>1)
			{
				G4cout << "### " << _name << " : Optical Photon..." << G4endl;
				G4cout << "### Creator Process Name: " 
					<<	aStep->GetTrack()->GetCreatorProcess()->GetProcessName() 
					<< G4endl;
				G4cout << "### Energy==" << aStep->GetTrack()->GetTotalEnergy()/eV 
					<< G4endl;
			}

			//
			//	Get the layer...
			//
			G4TouchableHandle touchable = 
				aStep->GetPreStepPoint()->GetTouchableHandle();
			int ilayer = touchable->GetCopyNumber(1);
			if (_parameters.verbosity>1)
				G4cout << "### ilayer=" << ilayer << endl;
	
			G4double totE = aStep->GetPreStepPoint()->GetTotalEnergy();
			G4double totE1 = aStep->GetTrack()->GetTotalEnergy();
//			cout << totE/eV << "  " << totE1/eV << endl;
			Double_t lyambda = 1239.8/(totE/eV);

			if (_name=="SD_EM_C" || _name=="SD_HAD_C")
				if (lyambda>=250 && lyambda<=600)
				{
					numPhotonsPerLayer[ilayer]++;
					numPhotons++;
				}
			if (_name=="SD_EM_S" || _name=="SD_HAD_S")
				if (lyambda>=325 && lyambda<=550)
				{
					numPhotonsPerLayer[ilayer]++;
					numPhotons++;
				}
	
			//
			//	Collect upon generation
			//
			aStep->GetTrack()->SetTrackStatus(fStopAndKill);
		}
//	}
/*	else
	{

		if (aStep->GetTrack()->GetParticleDefinition()->GetParticleName() !=
				"opticalphoton")
		{
			double thisDep = aStep->GetTotalEnergyDeposit()/MeV;
			int gen = ComputeOP(thisDep, 32000);

			G4double totE = aStep->GetPreStepPoint()->GetTotalEnergy();
			Double_t lyambda = 1239.8/(totE/eV);
			if (lyambda>=320 && lyambda<=675)
				numPhotons += gen;
				
		}
	}
*/
	return true;
}

int DRSD::ComputeOP(double ene, double yield)
{
	int genPhotons = 0;
	double mean = ene*yield;
	double sigma = sqrt(mean);
	genPhotons = floor(rand.Gaus(mean, sigma));

	return genPhotons;
}

//	Get the PMT ID by name
//
int DRSD::GetPMT(G4String name)
{
	int pos_ = name.find("_");
	string strID = name.substr(pos_+1, name.length());
	return atoi(strID.c_str());
}

//	Get the Number of Photoelectrons
//
double DRSD::GetPENum(G4double lyambda)
{
/*	//	For wavelength ourside of our range...
	//
	if ((lyambda > QPE[numBins-1][0]*nm) or (lyambda < QPE[0][0]*nm))
		return 0;

	//	If lyambda is equal to lower edge of our spectrum
	//
	if (lyambda == QPE[0][0]*nm)
		return QPE[0][1];

	//	If lyamda is equal to the upper edge of our spectrum
	//
	if (lyambda == QPE[numBins-1][0]*nm)
		return QPE[numBins - 1][1];

	//	Proceed... Find the right bin for interpolation
	//
	int l2pos = 0;
	while (lyambda > QPE[l2pos][0]*nm)
		l2pos++;
	double pes = ComputePE(l2pos-1, l2pos, lyambda/nm);

	return pes;
	*/
	return 0;
}

//	Interpolate/Compute QPE
//
double DRSD::ComputePE(int b1, int b2, double x)
{
/*	double x1 = QPE[b1][0];
	double x2 = QPE[b2][0];
	double y1 = QPE[b1][1];
	double y2 = QPE[b2][1];
	double y = y1 + (y2 - y1)*(x - x1)/(x2 - x1);
	return y;
	*/
}

//	Finalize the event
//
void DRSD::EndOfEvent(G4HCofThisEvent*)
{
	cout << "### Name= " << _name << " photons=" << numPhotons << endl;
	_tree->Fill();
}
