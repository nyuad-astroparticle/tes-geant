#include  "ParticleMessenger.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

ParticleMessenger::ParticleMessenger(PrimaryGeneratorAction* primaryGeneratorAction)
	: G4UImessenger(),
	primaryGenerator(primaryGeneratorAction)
{
	prefix = new G4UIdirectory("/haloscope/");
	prefix->SetGuidance("Control the particle parameters");

	// Set energy
	setEnergy = new G4UIcmdWithADoubleAndUnit("/haloscope/setEnergy",this);                // Command Name
	setEnergy->SetGuidance("Set the enrgy of the particle");                            // Guidance Line 1
	setEnergy->SetGuidance(" turns off random energy sampling");                        // Guidance Line 2
	setEnergy->SetParameterName("energy",false);                                        // Single un-omittable parameter
	setEnergy->SetUnitCategory("Energy");                                               // Unit cateogry
	setEnergy->SetDefaultValue(100);                                                    // Default Value
	setEnergy->SetDefaultUnit("MeV");                                                   // Unit for default value
	setEnergy->AvailableForStates(G4State_Idle);                                        // Available only when nothing is currently running
	
	// Set Spectrum
	setSpectrum = new G4UIcmdWith3VectorAndUnit("/haloscope/setSpectrum",this);            // Command Name
	setSpectrum->SetGuidance("Sets the fit parameters for sampling an energy spectrum");// Guidance Line 1
	setSpectrum->SetGuidance(" turns on random energy sampling");                       // Guidance Line 2
	setSpectrum->SetParameterName("A","B","C",false);                                   // Parameter Names, all un-omittable
	setEnergy->SetUnitCategory("Energy");                                               // Unit cateogry
	setEnergy->SetDefaultUnit("MeV");                                                   // Unit for default value
	setSpectrum->SetDefaultValue(G4ThreeVector(1,1,1));                                 // Default values
	setSpectrum->AvailableForStates(G4State_Idle);                                      // Available only when nothing is currently running
	
	//Select Particle
	selectParticle = new G4UIcmdWithAString("/haloscope/selectParticle",this);             // Command Name
	selectParticle->SetGuidance("Select the particle to shoot");                        // Guidance Line 1
	selectParticle->SetGuidance(" between proton, electron, and gamma");                // Guidance Line 2
	selectParticle->SetParameterName("particleName",false);                             // Single Unskippable Parameter
	selectParticle->SetDefaultValue("proton");                                          // Default Value
	selectParticle->SetCandidates("proton electron gamma muon");                        // Available Options (seperated by single spaces)
	selectParticle->AvailableForStates(G4State_Idle);                                   // Available only when nothing is currently running

	//Select Particle
	setZPosition = new G4UIcmdWithADoubleAndUnit("/haloscope/setZPosition",this);   	  // Command Name
	setZPosition->SetGuidance("Set the Z position");   		                 	   // Guidance Line 1
	setZPosition->SetGuidance(" of the particle gun");            		   		 // Guidance Line 2
	setZPosition->SetParameterName("zPosition",false);                      	          // Single Unskippable Parameter
	setZPosition->SetUnitCategory("Position");
	setZPosition->SetDefaultValue(0.5);                   	                       // Default Value
	setZPosition->SetDefaultUnit("m");			        	                // Available Options (seperated by single spaces)
	setZPosition->AvailableForStates(G4State_Idle);                                 	  // Available only when nothing is currently running

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Destructor
ParticleMessenger::~ParticleMessenger()
{
	delete prefix;
	delete setSpectrum;
	delete setEnergy;
	delete selectParticle;
	delete setZPosition;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Handle invoking the actuall command 
void ParticleMessenger::SetNewValue(G4UIcommand* command, G4String input)
{
    // Create an ugly nested if else block to do so
	if (command == setEnergy){                                          // Set Energy Command
	    G4double newEnergy  = setEnergy->GetNewDoubleValue(input);      // Get the new energy
	    G4double newUnit    = setEnergy->GetNewUnitValue(input);        // Get the new unit
	    primaryGenerator->setEnergy(newEnergy*newUnit);                 // Set the energy of the particles
	}
	
	else if (command == setSpectrum){                                   // Set Spectrum Command
	    G4ThreeVector newFit = setSpectrum->GetNew3VectorValue(input);  // Get the new parameters
	    G4double newUnit     = setSpectrum->GetNewUnitValue(input);     // Get the new unit
	    primaryGenerator->setEnergy(newFit, newUnit);                   // Set the energy of the primary generator to sample the spectrum
	}
	
	else if (command == selectParticle){                                // Select Particle Command
	    G4String newParticle = input;                                   // Get the particle as it is
	    auto particleTable = G4ParticleTable::GetParticleTable();       // Get the particle table
	
	    // Find which particle it is
	    if (!input.compare("proton"))
	        primaryGenerator->setParticle(particleTable->FindParticle("proton"));       // Set the particle to a proton
	    else if (!input.compare("electron"))
	        primaryGenerator->setParticle(particleTable->FindParticle("e-"));           // Set the particle to an electron
	    else if (!input.compare("gamma")) 
	        primaryGenerator->setParticle(particleTable->FindParticle("gamma"));        // Set the particle to a photon
	    else if (!input.compare("muon")) 
	        primaryGenerator->setParticle(particleTable->FindParticle("mu-"));        // Set the particle to a photon
    }
	else if (command == setZPosition){
		G4double newZPosition = setZPosition->GetNewDoubleValue(input);
		G4double newUnit = setZPosition->GetNewUnitValue(input);
		primaryGenerator->setZPosition(newZPosition);
	}

}
