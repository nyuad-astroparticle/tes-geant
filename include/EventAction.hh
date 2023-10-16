#ifndef EventAction_HH
#define EventAction_HH

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4RunManager.hh"

class EventAction : public G4UserEventAction {
    public:
        G4bool hitTES;
        EventAction() = default;
        ~EventAction() override = default;

        void SetHitTES(G4bool value){hitTES = value;}

        void BeginOfEventAction(const G4Event* event) override;
        void EndOfEventAction(const G4Event* event) override;

    private:
};

#endif