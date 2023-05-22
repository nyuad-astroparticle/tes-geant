#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh" 

MyActionInitialization::MyActionInitialization(){}


MyActionInitialization::~MyActionInitialization(){}


void MyActionInitialization::Build() const
{
	PrimaryGeneratorAction *generator = new PrimaryGeneratorAction("");
	SetUserAction(generator);
}

