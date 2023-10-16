#ifndef ActionInitialization__HH
#define ActionInitialization__HH

#include "DetectorConstruction.hh"
#include "G4VUserActionInitialization.hh"


class MyActionInitialization : public G4VUserActionInitialization
{
public:
	MyActionInitialization(MyDetectorConstruction * aDetector);
	~MyActionInitialization();

	void Build() const override;
	void BuildForMaster() const override;
private:
	MyDetectorConstruction * fDetector = nullptr;
};

#endif

