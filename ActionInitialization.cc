#include "ActionInitialization.hh"
#include "EventAction.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh" 

MyActionInitialization::MyActionInitialization(){}


MyActionInitialization::~MyActionInitialization(){}

void MyActionInitialization::BuildForMaster() const
{
	SetUserAction(new RunAction());	
}

void MyActionInitialization::Build() const
{
	PrimaryGeneratorAction* generator = new PrimaryGeneratorAction("");
	SetUserAction(new RunAction());
	SetUserAction(new EventAction());
	SetUserAction(generator);
}

