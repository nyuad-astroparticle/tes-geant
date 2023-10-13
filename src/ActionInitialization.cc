#include "ActionInitialization.hh"
#include "EventAction.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh" 

#ifdef ADD_THORIUM
#include "TrackingAction.hh"
#endif

#ifdef MPI_ENABLE
#include "MPIRunActionMaster.hh"
#endif

MyActionInitialization::MyActionInitialization()
{
	eventAction = new EventAction();
}


MyActionInitialization::~MyActionInitialization()
{
	delete eventAction;
}

void MyActionInitialization::BuildForMaster() const
{
	#ifndef MPI_ENABLE
	SetUserAction(new RunAction());	
	#else
	SetUserAction(new RunActionMaster(true));
	#endif
}

void MyActionInitialization::Build() const
{
	PrimaryGeneratorAction* generator = new PrimaryGeneratorAction("");
	
	#ifndef MPI_ENABLE
	SetUserAction(new RunAction());	
	#else
	SetUserAction(new RunActionMaster(true));
	#endif
	
	// eventAction = new EventAction();
	SetUserAction(eventAction);
	SetUserAction(generator);
	#ifdef ADD_THORIUM
	SetUserAction(new TrackingAction);
	#endif
}

