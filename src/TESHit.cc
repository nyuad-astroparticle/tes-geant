#include "TESHit.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4VisAttributes.hh"
#include "G4UnitsTable.hh"

G4ThreadLocal G4Allocator<TESHit>* HitAllocator = nullptr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool TESHit::operator==(const TESHit& right) const
{
    return (this==&right) ? true : false;
}

void TESHit::Draw()
{
    G4VVisManager* particleVisManager = G4VVisManager::GetConcreteInstance();
    if (particleVisManager) {
        G4Circle circle(position);
        circle.SetScreenSize(4.0);
        circle.SetFillStyle(G4Circle::filled);
        G4Colour colour(.64,.92,.21);
        G4VisAttributes attributes(colour);
        circle.SetVisAttributes(attributes);
        particleVisManager->Draw(circle);
    }
}

void TESHit::Print()
{
    if( verboseLevel > 0) G4cout
        << " trackID: "     << trackID
        << " Particle: "    << particle
        << " Einitial: "    << std::setw(7) << G4BestUnit(initialEnergy,    "Energy")
        << " Edep: "        << std::setw(7) << G4BestUnit(energyDeposited,  "Energy")
        << " Position: "    << std::setw(7) << G4BestUnit(position,         "Length")
        << " Time: "        << std::setw(7) << G4BestUnit(time,             "Time")
        << " Volume: " << volume
        << G4endl;
}