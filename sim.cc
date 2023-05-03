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

	auto runManager = G4RunManagerFactory::CreateRunManager(); // creating a run manager
	runManager->SetUserInitialization(new MyDetectorConstruction);
	runManager->SetUserInitialization(new MyPhysicsList);
	runManager->SetUserInitialization(new MyActionInitialization);

	runManager->Initialize();

	G4UIExecutive *ui = new G4UIExecutive(argc, argv);

	G4UImanager* UI = G4UImanager::GetUIpointer(); // get the pointer of the ui manager duh

	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();


	// starting a run
	UI->ApplyCommand("/vis/open OGL");
	UI->ApplyCommand("/vis/drawVolume");
	UI->ApplyCommand("/vis/viewer/set/autoRefresh true");
	UI->ApplyCommand("/vis/scene/add/trajectories smooth");


	ui->SessionStart();	
	// deleting the run manager
	delete runManager;
	return 0;
}
