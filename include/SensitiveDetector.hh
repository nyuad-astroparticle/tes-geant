#ifndef SensitiveDetector_HH
#define SensitiveDetector_HH

#include "G4VSensitiveDetector.hh"
#include "TESHit.hh"
// #include "EventAction.hh"
#include "ActionInitialization.hh"

class SensitiveDetector : public G4VSensitiveDetector
{
public:
    SensitiveDetector(const G4String& name, const G4String& hitsCollectionName, MyActionInitialization * action);
    ~SensitiveDetector();

    G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;

    void Initialize(G4HCofThisEvent* hitsCollection) override;
    void EndOfEvent(G4HCofThisEvent* hitsCollection) override;

private:
    HitsCollection* hitsCollection = nullptr;
    MyActionInitialization * action = nullptr;
};

#endif