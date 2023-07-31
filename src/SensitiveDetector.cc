#include "SensitiveDetector.hh"
#include "G4SDManager.hh"

SensitiveDetector::SensitiveDetector(const G4String& name, const G4String& hitsCollectionName)
: G4VSensitiveDetector(name)
{
    collectionName.insert(hitsCollectionName);
}

void SensitiveDetector::Initialize(G4HCofThisEvent* hitsCollection)
{
    this->hitsCollection = new HitsCollection(SensitiveDetectorName, collectionName[0]);

    G4int hitsCollectionId = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);   
    hitsCollection->AddHitsCollection(hitsCollectionId,this->hitsCollection);
}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history)
{
    G4double edep = step->GetTotalEnergyDeposit();

    if(edep == 0.0) return false;

    auto hit = new TESHit();
    hit->setTrackID(step->GetTrack()->GetTrackID());
    hit->setParticle(step->GetTrack()->GetParticleDefinition()->GetParticleName());
    hit->setEnergyDeposited(edep);
    hit->setPosition(step->GetPostStepPoint()->GetPosition());
    hit->setTime(step->GetPostStepPoint()->GetLocalTime());
    hit->setVolume(step->GetPreStepPoint()->GetPhysicalVolume()->GetName());
    hit->setInitialEnergy   (step->GetTrack()->GetTotalEnergy());

    hitsCollection->insert(hit);

    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* hitsCollection){
    if ( verboseLevel>1 ) {
     G4int nofHits = this->hitsCollection->entries();
     G4cout << G4endl
            << "-------->Hits Collection: in this event they are " << nofHits
            << " hits in the tracker chambers: " << G4endl;
     for ( G4int i=0; i<nofHits; i++ ) (*(this->hitsCollection))[i]->Print();
  }
}