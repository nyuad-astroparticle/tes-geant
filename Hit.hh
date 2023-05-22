#ifndef Hit_HH
#define Hit_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class Hit : public G4VHit
{
public:
    Hit() = default;
    Hit(const Hit&) = default;
    ~Hit() override;

    Hit& operator=(const Hit&) = default;
    G4bool operator==(const Hit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    void Draw() override;
    void Print() override;

    void setTrackID(G4int trackID)                      {this->trackID = trackID;};
    void setEnergyDeposited(G4double energyDeposited)   {this->energyDeposited = energyDeposited;};
    void setPosition(G4ThreeVector position)            {this->position = position;};
    void setTime(G4double time)                         {this->time = time;};

    G4int getTrackID()              {return trackID;};
    G4double getEnergyDeposited()   {return energyDeposited;};
    G4ThreeVector getPosition()     {return position;};
    G4double getTime()              {return time;};

private:
    G4int           trackID = -1;
    G4double        energyDeposited = 0;
    G4ThreeVector   position;
    G4double        time = -1;
};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<Hit> HitsCollection;
extern G4ThreadLocal G4Allocator<Hit>* HitAllocator;

inline void* Hit::operator new(size_t)
{
    if(!HitAllocator) HitAllocator = new G4Allocator<Hit>;
    return (void*) HitAllocator->MallocSingle();
}

inline void Hit::operator delete(void* hit)
{
    HitAllocator->FreeSingle((Hit*) hit);
}

#endif