#ifndef TESHit_HH
#define TESHit_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class TESHit : public G4VHit
{
public:
    TESHit() = default;
    TESHit(const TESHit&) = default;
    ~TESHit() override = default;

    TESHit& operator=(const TESHit&) = default;
    G4bool operator==(const TESHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    void Draw() override;
    void Print() override;

    void setTrackID(G4int trackID)                      {this->trackID = trackID;};
    void setParticle(G4String particle)                 {this->particle = particle;};
    void setEnergyDeposited(G4double energyDeposited)   {this->energyDeposited = energyDeposited;};
    void setPosition(G4ThreeVector position)            {this->position = position;};
    void setTime(G4double time)                         {this->time = time;};
    void setVolume(G4String volume)                     {this->volume = volume;};
    void setInitialEnergy(G4double initialEnergy)       {this->initialEnergy = initialEnergy;};
    void setOrigin(G4String originVolume)               {this->originVolume = originVolume;};
    void setMigrantID       (G4int migrantID)           {this->migrantID = migrantID; };
    void setParentID(G4int parentID)                    {this->parentID = parentID; };
    void setProcessName(G4String processName)           {this->processName = processName;}


    G4int           getTrackID()            {return trackID;};
    G4String        getParticle()           {return particle;};
    G4double        getEnergyDeposited()    {return energyDeposited;};
    G4ThreeVector   getPosition()           {return position;};
    G4double        getTime()               {return time;};
    G4String        getVolume()             {return volume;};
    G4double        getInitialEnergy()      {return initialEnergy;};
    G4String        getOrigin()             {return originVolume;};
    G4int           getMigrantID()          {return migrantID;};
    G4int           getParentID()           {return parentID;};
    G4String        getProcessName()        {return processName;};


private:
    G4int           trackID             = -1;
    G4String        particle            ="";
    G4double        energyDeposited     = 0;
    G4ThreeVector   position;
    G4double        time                = -1;
    G4String        volume              = "";
    G4int           verboseLevel        = 0;
    G4double        initialEnergy       = 0;
    G4String        originVolume        = "";
    G4int           migrantID           = -1;
    G4int           parentID            = -1;
    G4String        processName         = "";
};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

using HitsCollection = G4THitsCollection<TESHit>;
extern G4ThreadLocal G4Allocator<TESHit>* HitAllocator;

inline void* TESHit::operator new(size_t)
{
    if(!HitAllocator) HitAllocator = new G4Allocator<TESHit>;
    return (void*) HitAllocator->MallocSingle();
}

inline void TESHit::operator delete(void* hit)
{
    HitAllocator->FreeSingle((TESHit*) hit);
}

#endif