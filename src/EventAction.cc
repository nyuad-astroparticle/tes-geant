#include "EventAction.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Event.hh"
#include "TESHit.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

void EventAction::BeginOfEventAction(const G4Event* event)
{
    hitTES = false;
}

void EventAction::EndOfEventAction(const G4Event* event)
{

#ifdef FILTER_FOR_TES
    if (not hitTES) return; // when turned on it allows to keep only events that had a tes hit
#endif

    auto eventHitsCollections = event->GetHCofThisEvent();
    auto analysisManager = G4AnalysisManager::Instance();

    for (int i=0;i<eventHitsCollections->GetNumberOfCollections();i++){
        auto eventHitsCollection = static_cast<HitsCollection*> (eventHitsCollections->GetHC(i));

        for (int j=0;j<eventHitsCollection->GetSize();j++){
            TESHit* hit = (*eventHitsCollection)[j];
            
            analysisManager->FillNtupleIColumn(0,event->GetEventID());
            analysisManager->FillNtupleIColumn(1,hit->getTrackID());
            analysisManager->FillNtupleSColumn(2,hit->getParticle());
            analysisManager->FillNtupleDColumn(3,hit->getEnergyDeposited()/MeV);
            analysisManager->FillNtupleDColumn(4,hit->getPosition()[0]);
            analysisManager->FillNtupleDColumn(5,hit->getPosition()[1]);
            analysisManager->FillNtupleDColumn(6,hit->getPosition()[2]);
            analysisManager->FillNtupleDColumn(7,hit->getTime()/ns);
            analysisManager->FillNtupleSColumn(8,hit->getVolume());
            analysisManager->FillNtupleDColumn(9,hit->getInitialEnergy()/keV);
            analysisManager->FillNtupleSColumn(10,hit->getOrigin());
            analysisManager->FillNtupleIColumn(11,hit->getMigrantID());
            analysisManager->FillNtupleIColumn(12,hit->getParentID());
            analysisManager->AddNtupleRow();
        }
    }
}