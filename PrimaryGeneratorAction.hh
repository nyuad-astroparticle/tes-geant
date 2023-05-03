#ifndef PrimaryGeneratorAction_HH
#define PrimaryGeneratorAction_HH

#include "ParticleMessenger.hh"

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

// Get instances of some of the useful G4 predefined classes
class G4ParticleGun;                                            // Get it? Because it shoots the particle XDDDDD
class G4Event;                                                  // The event is a collection of shots
class G4ParticleDefinition;                                     // Store parameters of a particle
class ParticleMessenger;                                        // Class that handles user input

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
	public:
		PrimaryGeneratorAction();
		~PrimaryGeneratorAction();

		void setParticle(G4ParticleDefinition* particle);           // Sets the particle
		void setRandomizeEnergy(G4bool randomizeEnergy);            // Sets if the energy is randomized from a given spectrum or not
		void setEnergy(G4double energy);                            // Sets the fixed Energy
		void setEnergy(G4ThreeVector spectrumFit, G4double unit);   // Sets the Parameters for sampling the energy
		void setZPosition(G4double zPosition);   // Sets the Parameters for sampling the energy
		virtual void GeneratePrimaries(G4Event*);
	private:
		G4ParticleGun* particleGun;                                 // The particle Gun Used
		ParticleMessenger* particleMessenger;                       // Handles the parameters of the run
		G4ParticleDefinition* particle;                             // The particle to shoot
		G4double energy;                                            // Particle energy if needed
		G4double zPosition;                                            // Particle energy if needed
		G4bool randomizeEnergy;                                     // Decides if energy is randomized based on parameters or fixed
		G4double randomUnit;                                        // Energy unit to be used if the energy is set randomly
		G4ThreeVector spectrumFit;                                  // Parameters for randomizing energy
		G4double SampleEnergy();                                    // Samples an energy at random given the spectrumFit Parameters
		G4ThreeVector SampleStartPosition();                        // Samples a starting position outside of the detector
		G4ThreeVector SampleMomentumDirection(); // Samples momentum direction so that the particle hits the detector
};


#endif

