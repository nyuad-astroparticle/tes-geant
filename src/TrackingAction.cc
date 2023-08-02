/************************
•     ┓             •    
┓┏┳┓┏┓┃┏┓┏┳┓┏┓┏┓╋┏┓╋┓┏┓┏┓
┗┛┗┗┣┛┗┗ ┛┗┗┗ ┛┗┗┗┻┗┗┗┛┛┗
    ┛                    
     Tracking Action

Used to stop tracks that 
we don't want to simulate
from generating
************************/

// The relevant header
#include "TrackingAction.hh"

// Other Useful headers
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"

// Constructor
TrackingAction::TrackingAction() : G4UserTrackingAction()
{}

//----------------------- 8< -------------[ cut here ]------------------------

// Destructor
TrackingAction::~TrackingAction()
{}

//----------------------- 8< -------------[ cut here ]------------------------

// What to do before the track is generated
void TrackingAction::PreUserTrackingAction(const G4Track* track)
{
    // Get the particle this track is about
    G4ParticleDefinition* particle = track->GetDefinition();

    // If the particle is an ion
    if (particle->GetPDGCharge() > 2.){
        G4Track* tr = (G4Track*) track;

        // and it isn't the original atom
        if (track->GetTrackID() > 35){
            // Kill that track
            tr->SetTrackStatus(fStopAndKill);
        }
        else {
            tr->SetKineticEnergy(0.);
            tr->SetTrackStatus(fStopButAlive);

        }
    }
}

//----------------------- 8< -------------[ cut here ]------------------------

// What to do after the track is generated
void TrackingAction::PostUserTrackingAction(const G4Track* track)
{}