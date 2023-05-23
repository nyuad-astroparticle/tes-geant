#ifndef PrimaryGeneratorAction_HH
#define PrimaryGeneratorAction_HH

#include "ParticleMessenger.hh"

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4Event.hh"

#include "vector"
#include "CRYSetup.h"
#include "CRYParticle.h"
#include "CRYGenerator.h"
#include "RNGWrapper.hh"

// Get instances of some of the useful G4 predefined classes
class G4ParticleGun;                                            // Get it? Because it shoots the particle XDDDDD
class G4Event;                                                  // The event is a collection of shots
class G4ParticleDefinition;                                     // Store parameters of a particle
class ParticleMessenger;                                        // Class that handles user input

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
	public:
		PrimaryGeneratorAction(const char* filename);
		~PrimaryGeneratorAction();
	
		void GeneratePrimaries(G4Event* event);
		void InputCRY();
		void UpdateCRY(std::string* input);
		void CRYFromFile(G4String newFilename);

	private:
		std::vector<CRYParticle*> *vect;
		G4ParticleTable* particleTable;
		G4ParticleGun* particleGun;
		CRYGenerator* generator;
		G4int inputState;
		ParticleMessenger* particleMessenger;
};


#endif

