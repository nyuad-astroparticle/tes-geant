#ifndef RunAction_HH
#define RunAction_HH

#include "G4UserRunAction.hh"
#include "G4String.hh"
#include "PrimaryGeneratorAction.hh"

class RunAction : public G4UserRunAction
{
    friend class RunActionMaster;
    
    public:
        RunAction(PrimaryGeneratorAction * aGenerator);
        ~RunAction() override;
        PrimaryGeneratorAction * generator = nullptr;
        

        void BeginOfRunAction(const G4Run*) override;
        void   EndOfRunAction(const G4Run*) override;
    
    private:
        static void BookAnalysis(G4String filename = "TEST.csv", G4bool ntupleMerging = false);

};

#endif