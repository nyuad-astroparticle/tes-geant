#include "ActionInitialization.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh" 
#include "DetectorConstruction.hh"


#ifdef ADD_RADIOACTIVE
#include "TrackingAction.hh"
#endif

#ifdef MPI_ENABLE
#include "MPIRunActionMaster.hh"
#endif

MyActionInitialization::MyActionInitialization(MyDetectorConstruction * aDetector) : fDetector(aDetector)
{
}


MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::BuildForMaster() const
{
	#ifndef MPI_ENABLE
	SetUserAction(new RunAction(new PrimaryGeneratorAction("")));	
	#else
	SetUserAction(new RunActionMaster(true, new PrimaryGeneratorAction("")));
	#endif
}

void MyActionInitialization::Build() const
{
	PrimaryGeneratorAction* generator = new PrimaryGeneratorAction("");
	
	#ifndef MPI_ENABLE
	SetUserAction(new RunAction(generator));	
	#else
	SetUserAction(new RunActionMaster(true,generator));
	#endif
	
	EventAction * eventAction = new EventAction();
	fDetector->passEventAction(eventAction);
	SetUserAction(eventAction);
	SetUserAction(generator);
	#ifdef ADD_RADIOACTIVE
	SetUserAction(new TrackingAction);
	#endif
}

