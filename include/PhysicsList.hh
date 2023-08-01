/************************************
        ╔═╗╦ ╦╦ ╦╔═╗╦╔═╗╔═╗
        ╠═╝╠═╣╚╦╝╚═╗║║  ╚═╗
        ╩  ╩ ╩ ╩ ╚═╝╩╚═╝╚═╝
            ╦  ╦╔═╗╔╦╗     
            ║  ║╚═╗ ║      
            ╩═╝╩╚═╝ ╩      

Define all the physical interactions
needed for the simulation.

Includes Radioactive Decay and some
stuff for correctly releasing energy
in metals.
************************************/

#ifndef PhysicsList_hh
#define PhysicsList_hh

// Geant4 Classes that we are using
#include "G4VModularPhysicsList.hh"

class PhysicsList : public G4VModularPhysicsList
{
    public:
        PhysicsList();      // Constructor
        ~PhysicsList();     // Destructor

        void ConstructProcess() override;
};

#endif