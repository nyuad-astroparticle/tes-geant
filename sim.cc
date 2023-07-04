//importing relevent thingies that i have made

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

// importing mandatory g4 thingies
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"


#ifdef MPI
#include "G4MPImanager.hh"
#include "G4MPIsession.hh"
#include "G4RunManager.hh"
#else
#include "G4RunManagerFactory.hh"
#endif

// If you are not in multithreaded mode assume you are in MPI mode

int main(int argc,char**  argv){

	// Evaluate the arguments
    G4UIExecutive* ui = nullptr;

#ifdef MPI 
	G4MPImanager* mpiManager    = new G4MPImanager(argc,argv);
    mpiManager->SetVerbose(1);

    G4MPIsession* session       = mpiManager->GetMPIsession();
    G4String prompt             = "[40;01;33mG4MPI[40;31m(%s)[40;36m[%/][00;30m:";
    session-> SetPrompt(prompt);

    G4RunManager* runManager    = new G4RunManager();
#else
    if (argc == 1) {ui = new G4UIExecutive(argc,argv);}     // If no macro file has been created Create the UI
    auto runManager = G4RunManagerFactory::CreateRunManager(); // creating a run manager
#endif
	runManager->SetUserInitialization(new MyDetectorConstruction);
	runManager->SetUserInitialization(new MyPhysicsList);
	runManager->SetUserInitialization(new MyActionInitialization);

	runManager->Initialize();

    G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();

#ifdef MPI
    session->SessionStart();
#else
	G4UImanager* uiManager = G4UImanager::GetUIpointer(); // get the pointer of the ui manager duh

	// Process the macro file or strat GUI
    if (!ui){
        // Don't print anything
        uiManager->ApplyCommand("/run/verbose 0");
		uiManager->ApplyCommand("/hits/verbose 0");

        //Run the commands in batch mode
        for (int i=1;i<argc;i++){                               // For each input
            G4String command  = "/control/execute ";            // The command to execute it in Geant4
            G4String filename = argv[1];                        // The input filename
            uiManager->ApplyCommand(command + filename);        // Execute it
        }
    } else {
        // Increase verbosity
        uiManager->ApplyCommand("/run/verbose 1");

        // Start the UI
        // starting a run
		uiManager->ApplyCommand("/vis/open OGL");
		uiManager->ApplyCommand("/vis/drawVolume");
		uiManager->ApplyCommand("/vis/viewer/set/autoRefresh true");
		uiManager->ApplyCommand("/vis/scene/add/trajectories smooth");
        ui->SessionStart();
        delete ui;
    }
#endif

	// deleting the run manager
	delete visManager;
#ifdef MPI
    delete mpiManager;
#endif
	delete runManager;
	return 0;
}
