/*******************************************************
╔╦╗╔═╗╦  ╦═╗╦ ╦╔╗╔  ╔═╗╔═╗╔╦╗╦╔═╗╔╗╔  ╔╦╗╔═╗╔═╗╔╦╗╔═╗╦═╗
║║║╠═╝║  ╠╦╝║ ║║║║  ╠═╣║   ║ ║║ ║║║║  ║║║╠═╣╚═╗ ║ ║╣ ╠╦╝
╩ ╩╩  ╩  ╩╚═╚═╝╝╚╝  ╩ ╩╚═╝ ╩ ╩╚═╝╝╚╝  ╩ ╩╩ ╩╚═╝ ╩ ╚═╝╩╚═
********************************************************/

#ifndef MPIRUNACTIONMASTER_HH
#define MPIRUNACTIONMASTER_HH

#ifdef MPI_ENABLE
#include "G4UserRunAction.hh"

class G4MPIntupleMerger;

class RunActionMaster : public G4UserRunAction 
{

    public:
        RunActionMaster(G4bool mergeNtuple);
        ~RunActionMaster();

        virtual G4Run*  GenerateRun();
        virtual void    BeginOfRunAction(const G4Run* run);
        virtual void    EndOfRunAction(const G4Run* run);

    private:
        G4MPIntupleMerger* ntupleMerger;
};

#endif
#endif
