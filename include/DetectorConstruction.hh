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

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		MyDetectorConstruction(const G4GDMLParser& parser);
		~MyDetectorConstruction();

		G4VPhysicalVolume *Construct() override;
		void ConstructSDandField() override;

	private:
		G4LogicalVolume* substrateLogical 		= nullptr;
		G4LogicalVolume* paddleLogical			= nullptr;
		G4LogicalVolume* crossLogical			= nullptr;
		G4LogicalVolume* logicSiliconSubstrate 	= nullptr;
		G4LogicalVolume* logicSiliconOxide 		= nullptr;
		G4LogicalVolume* logicSiliconNitride 	= nullptr;
		G4LogicalVolume* logicSaber				= nullptr;
		G4LogicalVolume* logicLong				= nullptr;
		G4LogicalVolume* logicShort				= nullptr;
		G4LogicalVolume* logicCopperPlate		= nullptr;
		
		const G4GDMLParser & GDMLParser;

};
#endif

