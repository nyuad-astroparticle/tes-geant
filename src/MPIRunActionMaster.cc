#ifdef MPI_ENABLE

#include "G4MPImanager.hh"
#include "G4MPIntupleMerger.hh"
#include "G4AnalysisManager.hh"
#include "RunAction.hh"
#include "G4Run.hh"

#include "MPIRunActionMaster.hh"

RunActionMaster::RunActionMaster(G4bool mergeNtuple) : G4UserRunAction(), 
    ntupleMerger(nullptr)
{   
    // Sets the merging of Ntuples for MPI
    if (mergeNtuple && G4MPImanager::GetManager()->GetTotalSize() >= 2) {
        G4int numberOfReducedNtupleFiles    = 0;
        G4bool rowWise                      = true;
        ntupleMerger = new G4MPIntupleMerger(numberOfReducedNtupleFiles, rowWise);
    }

    // Initializes the Analysis manager;
    G4String defaultFilename = "TES";
    G4cout << "Booking Analysis" << G4endl;
    RunAction::BookAnalysis(defaultFilename,mergeNtuple);
    G4cout << "Analysis Booked" << G4endl;
}

RunActionMaster::~RunActionMaster() 
{
    delete ntupleMerger;
}

G4Run* RunActionMaster::GenerateRun()
{
    return new G4Run;
}

void RunActionMaster::BeginOfRunAction(const G4Run* run)
{
    G4cout << ">>> Run " << run->GetRunID() << " starting..." << G4endl;

    auto analysisManager = G4AnalysisManager::Instance();
    // analysisManager->Reset();
    G4String filename = analysisManager->GetFileName();
    filename += "-run";
    filename += std::to_string(run->GetRunID());
    filename += "-rank";
    filename += std::to_string(G4MPImanager::GetManager()->GetRank());
    analysisManager->OpenFile(filename);
}

void RunActionMaster::EndOfRunAction(const G4Run* run)
{
    G4cout << ">>> Run " << run->GetRunID() << " ended...\n>>> Merging..." << G4endl;

    auto analysisManager    = G4AnalysisManager::Instance();
    const G4int rank        = G4MPImanager::GetManager()->GetRank();

    if (! G4MPImanager::GetManager()->IsExtraWorker() ) {
        // When the rank is zero add the last entries and close the files
        if (rank == 0) {
            analysisManager->Write();
            analysisManager->CloseFile(false);
        }
    }

    if (rank == 0) {
        analysisManager->OpenFile("MERGED");
        analysisManager->Write();
        analysisManager->CloseFile();
    }


}

#endif