#ifndef ParticleMessenger_HH
#define ParticleMessenger_HH

#include "PrimaryGeneratorAction.hh"
#include "G4UImessenger.hh"
#include "globals.hh"
#include "G4UIcommand.hh"

class PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAString;

class ParticleMessenger : public G4UImessenger
{
	public:
		ParticleMessenger(PrimaryGeneratorAction*);
		~ParticleMessenger();
		
		void SetNewValue(G4UIcommand* command, G4String input) override;
	private:

		PrimaryGeneratorAction* primaryGenerator;	// The object to control
		G4UIdirectory* prefix; 				// prefixe of the commands 
		
		// The available Commands
		G4UIcmdWith3VectorAndUnit* setSpectrum;         // Set Set the spectrum by which to sample energies from
		G4UIcmdWithADoubleAndUnit* setEnergy;           // Set the energy of the particle for fixed energies
		G4UIcmdWithADoubleAndUnit* setZPosition;           // Set the energy of the particle for fixed energies
		G4UIcmdWithAString* selectParticle;             // Select between proton, electron, and gamma		
};
#endif
