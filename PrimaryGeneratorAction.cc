#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
	// Set the energy picking parameters
	randomizeEnergy     = false;
	spectrumFit         = G4ThreeVector(1,1,1);
	energy              = 1.0 * MeV;
	randomUnit          = MeV;
	zPosition           = 0 * m;

	
	// Set Up the particle Gun
	G4int numberOfParticles = 10;
	particleGun             = new G4ParticleGun(numberOfParticles);
	
	// Set particle gun default parameters (they should change according to user input during the run)
	particle = G4ParticleTable::GetParticleTable()->FindParticle("mu-");     // Proton as default particle
	particleGun->SetParticleDefinition(particle);                               // Particle Definition
	particleGun->SetParticleMomentumDirection(G4ThreeVector(1,0,0));            // Momentum Direction
	particleGun->SetParticleEnergy(energy);                                    // Initial Energy
	particleGun->SetParticlePosition(G4ThreeVector(-1.0*cm,0.0*cm,0*cm));     // Initial Position
	
	
	// Start a Messenger
	particleMessenger   = new ParticleMessenger(this); 
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete particleGun;
	delete particleMessenger;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
	particleGun->SetParticleDefinition(particle);
    
	// Set the position of the particle gun
	particleGun->SetParticlePosition(G4ThreeVector(0. * m, 0. * m, zPosition*m));
	
	// Set the momentum direction
	G4ThreeVector momentumDirection = SampleMomentumDirection();
	particleGun->SetParticleMomentumDirection(momentumDirection);
	
	// Set the Kinetic energy
	G4double particleEnergy = SampleEnergy();
	particleGun->SetParticleEnergy(particleEnergy);

	
	// Keep track of the data at the event level
	
	// Now add generate the particles to the event
	particleGun->GeneratePrimaryVertex(anEvent);
}

G4ThreeVector PrimaryGeneratorAction::SampleStartPosition()
{
	return G4ThreeVector(0. * m, 0. * m, 5. *m);
}

G4ThreeVector PrimaryGeneratorAction::SampleMomentumDirection()
{
	return G4ThreeVector(0., 0., -1.);
}

G4double PrimaryGeneratorAction::SampleEnergy()
{
	return 1 *GeV;
}

void PrimaryGeneratorAction::setParticle(G4ParticleDefinition* particle){
	this->particle = particle;
}

void PrimaryGeneratorAction::setRandomizeEnergy(G4bool randomizeEnergy){
	this->randomizeEnergy = randomizeEnergy;
}

void PrimaryGeneratorAction::setEnergy(G4double energy){
	// Stop the simulation from randomizing the energy
	setRandomizeEnergy(false);
	
	// Set the fixed energy
	this->energy = energy;
}

void PrimaryGeneratorAction::setEnergy(G4ThreeVector spectrumFit, G4double unit){
    // Start the randomization of the energy
    setRandomizeEnergy(true);

    // Set the energy sampling parameters
    this->spectrumFit = spectrumFit;
    this->randomUnit  = unit;
}
void PrimaryGeneratorAction::setZPosition(G4double zPosition){
	this->zPosition = zPosition;
}
