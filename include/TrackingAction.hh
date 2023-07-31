/***************************
   ╔╦╗╦═╗╔═╗╔═╗╦╔═╦╔╗╔╔═╗
    ║ ╠╦╝╠═╣║  ╠╩╗║║║║║ ╦
    ╩ ╩╚═╩ ╩╚═╝╩ ╩╩╝╚╝╚═╝
      ╔═╗╔═╗╔╦╗╦╔═╗╔╗╔    
      ╠═╣║   ║ ║║ ║║║║    
      ╩ ╩╚═╝ ╩ ╩╚═╝╝╚╝    

Runs some checks before the
start and end of each track. 

Used to stop tracks that we
don't care about.
***************************/

#ifndef TrackingAction_hh
#define TrackingAction_hh

// The class we are building on
#include "G4UserTrackingAction.hh"

class TrackingAction : public G4UserTrackingAction {
    
    public:
        TrackingAction();                                       // Constructor
        ~TrackingAction();                                      // Destructor

        // The methods we need to override
        void  PreUserTrackingAction(const G4Track*) override;   // What to run before the track starts
        void PostUserTrackingAction(const G4Track*) override;   // What to run after the track starts
};

#endif