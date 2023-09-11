#include "PrimaryGeneratorAction.hh"
#include "Randomize.hh"
#include <iomanip>


PrimaryGeneratorAction::PrimaryGeneratorAction(const char* filename)
{
	// Define the particle gun
#ifdef ADD_THORIUM
	particleGun = new G4GeneralParticleSource();
#else
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
#endif 
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete particleGun;
#ifndef ADD_THORIUM
	delete particleMessenger;
#endif
}

#ifndef ADD_THORIUM
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

#endif

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
#ifdef ADD_THORIUM

	// Set up first General Particle Source (GPS) for Thorium-232
	G4ParticleDefinition* thorium232 = G4IonTable::GetIonTable()->GetIon(90, 232, 0);
	particleGun->SetParticleDefinition(thorium232);
	particleGun->GetCurrentSource()->GetEneDist()->SetMonoEnergy(0.0 * keV);

	// Position and confine within the copper box
	particleGun->GetCurrentSource()->GetPosDist()->SetPosDisType("Volume");
	particleGun->GetCurrentSource()->GetPosDist()->SetPosDisShape("Para");
	particleGun->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector( -35.2 * cm / 2 - 2*mm - 1*cm - 0.5*cm/2 -2 * mm, -698.771 * mm + 11.5 * cm, 0));
	// particleGun->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(0, 0, 0));
	particleGun->GetCurrentSource()->GetPosDist()->SetHalfX(0.25 * cm);
	particleGun->GetCurrentSource()->GetPosDist()->SetHalfY(1.5 * cm);
	particleGun->GetCurrentSource()->GetPosDist()->SetHalfZ(1.5 * cm);
	particleGun->GetCurrentSource()->GetPosDist()->SetPosRot1(G4ThreeVector(1, 0, 0));
	particleGun->GetCurrentSource()->GetPosDist()->SetPosRot2(G4ThreeVector(0, 0, 1));
	// particleGun->GetCurrentSource()->GetPosDist()->ConfineSourceToVolume("logicCopperBox_PV");

	// Generate the first particle
	particleGun->GeneratePrimaryVertex(anEvent);

#else
	if (inputState != 0) {
		G4String* str = new G4String("CRY was not successfully initialized");
		G4Exception("PrimaryGeneratorAction","1",RunMustBeAborted,*str);
	}
	G4String particleName;
	vect->clear();
	generator->genEvent(vect);

	//....debug output
	//....debug output
  	// G4cout << "\nEvent=" << anEvent->GetEventID() << " "
    //      << "CRY generated nparticles=" << vect->size()
    //      << G4endl;

	for ( unsigned j=0; j<vect->size(); j++) {
    particleName=CRYUtils::partName((*vect)[j]->id());

    //....debug output  
    // G4cout << "  "          << particleName << " "
    //      << "charge="      << (*vect)[j]->charge() << " "
    //      << "energy (MeV)=" << (*vect)[j]->ke()*MeV << " "
    //      << "pos (m)"
    //      << G4ThreeVector((*vect)[j]->x(), (*vect)[j]->y(), (*vect)[j]->z())
    //      << " " << "direction cosines "
    //      << G4ThreeVector((*vect)[j]->u(), (*vect)[j]->v(), (*vect)[j]->w())
    //      << " " << G4endl;

    particleGun->SetParticleDefinition(particleTable->FindParticle((*vect)[j]->PDGid()));
    particleGun->SetParticleEnergy((*vect)[j]->ke()*MeV);
    particleGun->SetParticlePosition(G4ThreeVector((*vect)[j]->x()*m, (*vect)[j]->z()*m + 60.0*cm, -(*vect)[j]->y()*m));
    particleGun->SetParticleMomentumDirection(G4ThreeVector((*vect)[j]->u(), (*vect)[j]->w(), -(*vect)[j]->v()));
    particleGun->SetParticleTime((*vect)[j]->t());
    particleGun->GeneratePrimaryVertex(anEvent);
    delete (*vect)[j];
  }
#endif
}