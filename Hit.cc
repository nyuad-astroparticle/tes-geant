#include "Hit.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4VisAttributes.hh"
#include "G4UnitsTable.hh"

G4ThreadLocal G4Allocator<Hit>* HitAllocator = nullptr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool Hit::operator==(const Hit& right) const
{
    return (this==&right) ? true : false;
}

void Hit::Draw()
{
    G4VVisManager* particleVisManager = G4VVisManager::GetConcreteInstance();
    if (particleVisManager) {
        G4Circle circle(position);
        circle.SetScreenSize(4.0);
        circle.SetFillStyle(G4Circle::filled);
        G4Colour colour(1.,0.,0.);
        G4VisAttributes attributes(colour);
        circle.SetVisAttributes(attributes);
        particleVisManager->Draw(circle);
    }
}

void Hit::Print()
{
    G4cout
        << " trackID: " << trackID
        << " Edep: "
        << std::setw(7) << G4BestUnit(energyDeposited,"Energy")
        << " Position: "
        << std::setw(7) << G4BestUnit(position,"Length")
        << " Time: "
        << std::setw(7) << G4BestUnit(time,"Time")
        << G4endl;
}