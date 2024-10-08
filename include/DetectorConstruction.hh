#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh

#include "G4VUserDetectorConstruction.hh" // the g4 class that we will bulild upon
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4RotationMatrix.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"					 
#include "SensitiveDetector.hh"
#include "G4SDManager.hh" 
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4GDMLParser.hh"
#include "G4UserLimits.hh"
#include "EventAction.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		MyDetectorConstruction(const G4GDMLParser& parser);
		~MyDetectorConstruction();

		void passEventAction(EventAction * anEventAction){eventAction = anEventAction;}
		G4VPhysicalVolume *Construct() override;
		void ConstructSDandField() override;

	private:
		const G4GDMLParser & GDMLParser;
		EventAction * eventAction = nullptr;
};
#endif

