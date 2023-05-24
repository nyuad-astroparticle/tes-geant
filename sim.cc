//importing relevent thingies that i have made

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

// importing mandatory g4 thingies
#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
int main(int argc,char**  argv){

	// Evaluate the arguments
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {ui = new G4UIExecutive(argc,argv);}     // If no macro file has been created Create the UI

	auto runManager = G4RunManagerFactory::CreateRunManager(); // creating a run manager
	runManager->SetUserInitialization(new MyDetectorConstruction);
	runManager->SetUserInitialization(new MyPhysicsList);
	runManager->SetUserInitialization(new MyActionInitialization);

	runManager->Initialize();

	G4UImanager* uiManager = G4UImanager::GetUIpointer(); // get the pointer of the ui manager duh

	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();

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

	// deleting the run manager
	delete visManager;
	delete runManager;
	return 0;
}
