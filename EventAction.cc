#include "EventAction.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Event.hh"

void EventAction::BeginOfEventAction(const G4Event* event) {}

void EventAction::EndOfEventAction(const G4Event* event)
{

    // get number of stored trajectories
    G4TrajectoryContainer* trajectoryContainer = event->GetTrajectoryContainer();

    G4int n_trajectories = 0;
    if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

    // periodic printing
    G4int eventID = event->GetEventID();
    if ( eventID < 100 || eventID % 100 == 0) {
        G4cout << ">>> Event: " << eventID  << G4endl;
        if ( trajectoryContainer ) {
        G4cout << "    " << n_trajectories
                << " trajectories stored in this event." << G4endl;
        }
        G4VHitsCollection* hc = event->GetHCofThisEvent()->GetHC(0);
        G4cout << "    "
            << hc->GetSize() << " hits stored in this event" << G4endl;
    }
}