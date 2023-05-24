#include "RunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"

RunAction::RunAction()
{
    // Start the analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetVerboseLevel(0);
    
    // Create a Default filename that can be changed by the user using UI commands
    G4String defaultFilename = "TES.csv";
    // analysisManager->SetDefaultFileType("csv");
    analysisManager->SetNtupleDirectoryName("output");
    analysisManager->SetFileName(defaultFilename);
    // analysisManager->SetNtupleMerging(true);

    // Create the structure of the data as an Ntuple (Table)
    analysisManager->CreateNtuple("hits","TES Hits by Cosmic Rays");
    analysisManager->CreateNtupleIColumn("EventID");
    analysisManager->CreateNtupleIColumn("TrackID");
    analysisManager->CreateNtupleSColumn("Particle");
    analysisManager->CreateNtupleDColumn("EnergyDeposited");
    analysisManager->CreateNtupleDColumn("XPosition");
    analysisManager->CreateNtupleDColumn("YPosition");
    analysisManager->CreateNtupleDColumn("ZPosition");
    analysisManager->CreateNtupleDColumn("LocalTime");
    analysisManager->CreateNtupleSColumn("Volume");
    analysisManager->FinishNtuple();
}

RunAction::~RunAction() = default;

void RunAction::BeginOfRunAction(const G4Run* run)
{
    // Print that you are staring a run
    if (isMaster) G4cout << ">>> Run " << run->GetRunID() << " starting..." << G4endl;

    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Reset();
    G4String filename = analysisManager->GetFileName();
    analysisManager->OpenFile(filename);
}

void RunAction::EndOfRunAction(const G4Run* run)
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile(false);
}