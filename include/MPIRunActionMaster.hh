/*******************************************************
╔╦╗╔═╗╦  ╦═╗╦ ╦╔╗╔  ╔═╗╔═╗╔╦╗╦╔═╗╔╗╔  ╔╦╗╔═╗╔═╗╔╦╗╔═╗╦═╗
║║║╠═╝║  ╠╦╝║ ║║║║  ╠═╣║   ║ ║║ ║║║║  ║║║╠═╣╚═╗ ║ ║╣ ╠╦╝
╩ ╩╩  ╩  ╩╚═╚═╝╝╚╝  ╩ ╩╚═╝ ╩ ╩╚═╝╝╚╝  ╩ ╩╩ ╩╚═╝ ╩ ╚═╝╩╚═
********************************************************/

#ifndef MPIRUNACTIONMASTER_HH
#define MPIRUNACTIONMASTER_HH

#ifdef MPI_ENABLE
#include "G4UserRunAction.hh"
#include "MPIRunActionMaster.hh"


class G4MPIntupleMerger;

class RunActionMaster : public G4UserRunAction 
{

    public:
        RunActionMaster(G4bool mergeNtuple, PrimaryGeneratorAction * aGenerator );
        ~RunActionMaster();

        PrimaryGeneratorAction * generator = nullptr;

        virtual G4Run*  GenerateRun();
        virtual void    BeginOfRunAction(const G4Run* run);
        virtual void    EndOfRunAction(const G4Run* run);

    private:
        G4MPIntupleMerger* ntupleMerger;
};

#endif
#endif
