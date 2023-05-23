#ifndef SensitiveDetector_HH
#define SensitiveDetector_HH

#include "G4VSensitiveDetector.hh"
#include "Hit.hh"

class SensitiveDetector : public G4VSensitiveDetector
{
public:
    SensitiveDetector(const G4String& name, const G4String& hitsCollectionName);
    ~SensitiveDetector() override = default;

    G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);

    void Initialize(G4HCofThisEvent* hitsCollection);
    void EndOfEvent(G4HCofThisEvent* hitsCollection);

private:
    HitsCollection* hitsCollection = nullptr;
};

#endif