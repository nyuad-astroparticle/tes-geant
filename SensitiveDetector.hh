#ifndef SensitiveDetector_HH
#define SensitiveDetector_HH

#include "G4VSensitiveDetector.hh"

class SensitiveDetector : public G4VSensitiveDetector
{
public:
    SensitiveDetector(G4String Name);
    ~SensitiveDetector();

    G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);

    void Initialize(G4HCofThisEvent* hitContainer);
    void EndOfEvent(G4HCofThisEvent* hitContainer);
};

#endif