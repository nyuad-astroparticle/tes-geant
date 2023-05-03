#ifndef ActionInitialization__HH
#define ActionInitialization__HH

#include "G4VUserActionInitialization.hh"

#include "PrimaryGeneratorAction.hh" 

class MyActionInitialization : public G4VUserActionInitialization
{
public:
	MyActionInitialization();
	~MyActionInitialization();

	virtual void Build() const;
};

#endif

