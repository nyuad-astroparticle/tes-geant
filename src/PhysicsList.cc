/************************
•     ┓             •    
┓┏┳┓┏┓┃┏┓┏┳┓┏┓┏┓╋┏┓╋┓┏┓┏┓
┗┛┗┗┣┛┗┗ ┛┗┗┗ ┛┗┗┗┻┗┗┗┛┛┗
    ┛                    
       Physics List
************************/

// Include the relevant header file
#include "PhysicsList.hh" 

// Geant4 Physics Lists Constructors we are using
// #include "G4EmStandardPhysics.hh"
#include "G4EmLivermorePhysics.hh"
// #include "G4EmPenelopePhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

// Other Useful Headers
#include "G4EmParameters.hh"

// Constructor
PhysicsList::PhysicsList() : G4VModularPhysicsList()
{
	// RegisterPhysics (new G4EmStandardPhysics());
	RegisterPhysics (new G4EmLivermorePhysics());
	// RegisterPhysics (new G4EmPenelopePhysics());
	RegisterPhysics (new G4OpticalPhysics());
	RegisterPhysics (new G4DecayPhysics());
	RegisterPhysics (new G4RadioactiveDecayPhysics());
}

//----------------------- 8< -------------[ cut here ]------------------------

// Destructor
PhysicsList::~PhysicsList()
{}

//----------------------- 8< -------------[ cut here ]------------------------

// Override to enable Fluorecence and stuff
void PhysicsList::ConstructProcess()
{
	// Call parent method
	G4VModularPhysicsList::ConstructProcess();

	// Get the Geant4 Object that manages the EM Physics
	G4EmParameters* emParameters = G4EmParameters::Instance();

	// Enable Fluorescence, Pixe, and AUger Scattering
	emParameters->SetFluo(false);
	emParameters->SetPixe(true);
	emParameters->SetAuger(false);
}