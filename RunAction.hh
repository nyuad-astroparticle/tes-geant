#ifndef RunAction_HH
#define RunAction_HH

#include "G4UserRunAction.hh"

class RunAction : public G4UserRunAction
{
public:
    RunAction();
    ~RunAction() override;

    void BeginOfRunAction(const G4Run*) override;
    void   EndOfRunAction(const G4Run*) override;

};

#endif