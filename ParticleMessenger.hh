#ifndef ParticleMessenger_HH
#define ParticleMessenger_HH

#include "PrimaryGeneratorAction.hh"
#include "G4UImessenger.hh"
#include "globals.hh"
#include "G4UIcommand.hh"

class PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;

class ParticleMessenger : public G4UImessenger
{
	public:
		ParticleMessenger(PrimaryGeneratorAction*);
		~ParticleMessenger();
		
		void SetNewValue(G4UIcommand* command, G4String input);
	private:
		PrimaryGeneratorAction*      	primaryGenerator;
		G4UIdirectory*               	CRYDir;
		G4UIcmdWithAString*          	FileCmd; 
		G4UIcmdWithAString*          	InputCmd;
		G4UIcmdWithoutParameter*     	UpdateCmd;
		std::string* 					MessInput;	
};
#endif
