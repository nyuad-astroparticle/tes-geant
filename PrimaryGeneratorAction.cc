#include "PrimaryGeneratorAction.hh"
#include "Randomize.hh"
#include <iomanip>


PrimaryGeneratorAction::PrimaryGeneratorAction(const char* filename)
{
	// Define the particle gun
	particleGun = new G4ParticleGun();

	// Start CRYing
	std::ifstream file;
	file.open(filename,std::ios::in);
	char buffer[1000];

	// Handle the failure
	if (file.fail()){
		if (*filename != 0) G4cout << "PrimaryGeneratorAction: Failed to open CRY input file= " << filename << G4endl;
    	inputState=-1;
	} else {
		std::string setupString("");
		while(!file.getline(buffer,1000).eof()) {
			setupString.append(buffer);
			setupString.append(" ");
		}

		CRYSetup* setup  = new CRYSetup(setupString,"../data");
		generator = new CRYGenerator(setup);

		// set randim number generator
		RNGWrapper<CLHEP::HepRandomEngine>::set(CLHEP::HepRandom::getTheEngine(),&CLHEP::HepRandomEngine::flat);
		setup->setRandomFunction(RNGWrapper<CLHEP::HepRandomEngine>::rng);
		inputState=0;
	}

	// Store the cry particle properties
	vect = new std::vector<CRYParticle*>;

	// All particles in the simulation
	particleTable = G4ParticleTable::GetParticleTable();

	// Create the messenger
	particleMessenger = new ParticleMessenger(this);

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete particleGun;
	delete particleMessenger;
}

void PrimaryGeneratorAction::InputCRY()
{
	inputState = 1;
}

void PrimaryGeneratorAction::UpdateCRY(std::string* input)
{
	CRYSetup *setup = new CRYSetup(*input,"../data");

	generator = new CRYGenerator(setup);

	// set randim number generator
	RNGWrapper<CLHEP::HepRandomEngine>::set(CLHEP::HepRandom::getTheEngine(),&CLHEP::HepRandomEngine::flat);
	setup->setRandomFunction(RNGWrapper<CLHEP::HepRandomEngine>::rng);
	inputState=0;
}

void PrimaryGeneratorAction::CRYFromFile(G4String newFilename)
{
	// Read the cry input file
	std::ifstream file;
	file.open(newFilename,std::ios::in);
	char buffer[1000];

	if (file.fail()) {
		G4cout << "Failed to open input file " << newFilename << G4endl;
		G4cout << "Make sure to define the cry library on the command line" << G4endl;
		inputState=-1;
	} else {
	
	std::string setupString("");
	while ( !file.getline(buffer,1000).eof()) {
		setupString.append(buffer);
		setupString.append(" ");
	}

	CRYSetup *setup=new CRYSetup(setupString,"../data");

	generator = new CRYGenerator(setup);

	// set random number generator
	RNGWrapper<CLHEP::HepRandomEngine>::set(CLHEP::HepRandom::getTheEngine(),&CLHEP::HepRandomEngine::flat);
	setup->setRandomFunction(RNGWrapper<CLHEP::HepRandomEngine>::rng);
	inputState=0;
	}
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
	if (inputState != 0) {
		G4String* str = new G4String("CRY was not successfully initialized");
		G4Exception("PrimaryGeneratorAction","1",RunMustBeAborted,*str);
	}
	G4String particleName;
	vect->clear();
	generator->genEvent(vect);

	//....debug output
	//....debug output
  	G4cout << "\nEvent=" << anEvent->GetEventID() << " "
         << "CRY generated nparticles=" << vect->size()
         << G4endl;

	for ( unsigned j=0; j<vect->size(); j++) {
    particleName=CRYUtils::partName((*vect)[j]->id());

    //....debug output  
    G4cout << "  "          << particleName << " "
         << "charge="      << (*vect)[j]->charge() << " "
         << "energy (MeV)=" << (*vect)[j]->ke()*MeV << " "
         << "pos (m)"
         << G4ThreeVector((*vect)[j]->x(), (*vect)[j]->y(), (*vect)[j]->z())
         << " " << "direction cosines "
         << G4ThreeVector((*vect)[j]->u(), (*vect)[j]->v(), (*vect)[j]->w())
         << " " << G4endl;

    particleGun->SetParticleDefinition(particleTable->FindParticle((*vect)[j]->PDGid()));
    particleGun->SetParticleEnergy((*vect)[j]->ke()*MeV);
    particleGun->SetParticlePosition(G4ThreeVector((*vect)[j]->x()*m, (*vect)[j]->z()*m + 2.0*cm, -(*vect)[j]->y()*m));
    particleGun->SetParticleMomentumDirection(G4ThreeVector((*vect)[j]->u(), (*vect)[j]->w(), -(*vect)[j]->v()));
    particleGun->SetParticleTime((*vect)[j]->t());
    particleGun->GeneratePrimaryVertex(anEvent);
    delete (*vect)[j];
  }
}