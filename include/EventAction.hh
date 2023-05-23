#ifndef EventAction_HH
#define EventAction_HH

#include "G4UserEventAction.hh"
#include "globals.hh"

class EventAction : public G4UserEventAction {
public:
    EventAction() = default;
    ~EventAction() override = default;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;
};

#endif