// This file is temporary because i have to leave in 5 minutes

// // Filename: MyPrimaryGeneratorAction.cc

// #include "MyPrimaryGeneratorAction.hh"
// #include "G4Event.hh"
// #include "G4GeneralParticleSource.hh"
// #include "G4IonTable.hh"
// #include "G4ParticleDefinition.hh"

// MyPrimaryGeneratorAction::MyPrimaryGeneratorAction()
// {
//     fParticleGun = new G4GeneralParticleSource();
// }

// MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction()
// {
//     delete fParticleGun;
// }

// void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
// {
//     // Set up first General Particle Source (GPS) for Thorium-232
//     G4ParticleDefinition* thorium232 = G4IonTable::GetIonTable()->GetIon(90, 232, 0);
//     fParticleGun->SetParticleDefinition(thorium232);
//     fParticleGun->GetCurrentSource()->GetEneDist()->SetMonoEnergy(0.0 * keV);

//     // Position and confine within the copper box
//     fParticleGun->GetCurrentSource()->GetPosDist()->SetPosDisType("Volume");
//     fParticleGun->GetCurrentSource()->GetPosDist()->SetPosDisShape("Para");
//     fParticleGun->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(0, -13.3 * cm, 0));
//     fParticleGun->GetCurrentSource()->GetPosDist()->SetHalfX(20 * cm);
//     fParticleGun->GetCurrentSource()->GetPosDist()->SetHalfY(20 * cm);
//     fParticleGun->GetCurrentSource()->GetPosDist()->SetHalfZ(20 * cm);
//     fParticleGun->GetCurrentSource()->GetPosDist()->SetPosRot1(G4ThreeVector(1, 0, 0));
//     fParticleGun->GetCurrentSource()->GetPosDist()->SetPosRot2(G4ThreeVector(0, 0, 1));
//     fParticleGun->GetCurrentSource()->SetConfine("AluminiumBox");

//     // Generate the first particle
//     fParticleGun->GeneratePrimaryVertex(anEvent);

//     // Set up second General Particle Source (GPS) for Thorium-230
//     G4ParticleDefinition* thorium230 = G4IonTable::GetIonTable()->GetIon(90, 230, 0);
//     fParticleGun->SetParticleDefinition(thorium230);
//     fParticleGun->GetCurrentSource()->GetEneDist()->SetMonoEnergy(0.0 * keV);

//     // Position and confine within the copper box (same as the first source)
//     fParticleGun->GetCurrentSource()->GetPosDist()->SetPosDisType("Volume");
//     fParticleGun->GetCurrentSource()->GetPosDist()->SetPosDisShape("Para");
//     fParticleGun->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(0, -13.3 * cm, 0));
//     fParticleGun->GetCurrentSource()->GetPosDist()->SetHalfX(20 * cm);
//     fParticleGun->GetCurrentSource()->GetPosDist()->SetHalfY(20 * cm);
//     fParticleGun->GetCurrentSource()->GetPosDist()->SetHalfZ(20 * cm);
//     fParticleGun->GetCurrentSource()->GetPosDist()->SetPosRot1(G4ThreeVector(1, 0, 0));
//     fParticleGun->GetCurrentSource()->GetPosDist()->SetPosRot2(G4ThreeVector(0, 0, 1));
//     fParticleGun->GetCurrentSource()->SetConfine("AluminiumBox");

//     // Generate the second particle
//     fParticleGun->GeneratePrimaryVertex(anEvent);
// }
