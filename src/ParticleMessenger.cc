#include  "ParticleMessenger.hh"

#ifndef ADD_THORIUM

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "PrimaryGeneratorAction.hh"


ParticleMessenger::ParticleMessenger(PrimaryGeneratorAction* primaryGeneratorAction)
	: G4UImessenger(),
	primaryGenerator(primaryGeneratorAction)
{
	prefix = new G4UIdirectory("/CRY/");
	prefix->SetGuidance("CRY Initialization");
	
	FileCmd = new G4UIcmdWithAString("/CRY/file",this);
	FileCmd->SetGuidance("Read a CRY Definition from a file");
	FileCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	InputCmd = new G4UIcmdWithAString("/CRY/input",this);
	InputCmd->SetGuidance("CRY input lines");
	InputCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	UpdateCmd = new G4UIcmdWithoutParameter("/CRY/update",this);
	UpdateCmd->SetGuidance("Update CRY definition.");
	UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
	UpdateCmd->SetGuidance("if you changed the CRY definition.");
	UpdateCmd->AvailableForStates(G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Destructor
ParticleMessenger::~ParticleMessenger()
{
	delete prefix;
	delete InputCmd;
	delete UpdateCmd;
	delete FileCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ParticleMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  if( command == InputCmd )
   { 
     primaryGenerator->InputCRY();
     (*MessInput).append(newValue);
     (*MessInput).append(" ");
   }

  if( command == UpdateCmd )
   { 
     primaryGenerator->UpdateCRY(MessInput); 
     *MessInput = "";
   }

  if( command == FileCmd )
   { primaryGenerator->CRYFromFile(newValue); }

}

#endif
