#ifndef ActionInitialization__HH
#define ActionInitialization__HH

#include "G4VUserActionInitialization.hh"
#include "EventAction.hh"


class MyActionInitialization : public G4VUserActionInitialization
{
public:
	MyActionInitialization();
	~MyActionInitialization();

	void Build() const override;
	void BuildForMaster() const override;
	EventAction * eventAction = nullptr;
private:
};

#endif

