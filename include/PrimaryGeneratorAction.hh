#ifndef PrimaryGeneratorAction_HH
#define PrimaryGeneratorAction_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#ifdef ADD_RADIOACTIVE

#include "G4GeneralParticleSource.hh"
#include "G4IonTable.hh"

#else

#include "ParticleMessenger.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"

#include "vector"
#include "CRYSetup.h"
#include "CRYParticle.h"
#include "CRYGenerator.h"
#include "RNGWrapper.hh"

#endif

#include "G4SystemOfUnits.hh"
#include "G4Event.hh"

// Get instances of some of the useful G4 predefined classes
class G4ParticleGun;                                            // Get it? Because it shoots the particle XDDDDD
class G4Event;                                                  // The event is a collection of shots
#ifndef ADD_RADIOACTIVE
class G4ParticleDefinition;                                     // Store parameters of a particle
class ParticleMessenger;                                        // Class that handles user input
#endif 

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
	public:
		PrimaryGeneratorAction(const char* filename);
		~PrimaryGeneratorAction();
	
		void GeneratePrimaries(G4Event* event);
#ifndef ADD_RADIOACTIVE
		void InputCRY();
		void UpdateCRY(std::string* input);
		void CRYFromFile(G4String newFilename);
#endif
	private:

#ifdef ADD_RADIOACTIVE
		G4GeneralParticleSource* particleGun;
#else
		G4ParticleGun* particleGun;
		std::vector<CRYParticle*> *vect;
		G4ParticleTable* particleTable;
		CRYGenerator* generator;
		G4int inputState;
		ParticleMessenger* particleMessenger;
#endif

};


#endif

