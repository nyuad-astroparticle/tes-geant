#include "DetectorConstruction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();
//------------------Creating the world volume-----------------------------------
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

	G4Box *solidWorld = new G4Box("solidWorld", 1*m, 1*m, 1*m);

	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

	G4VPhysicalVolume * physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

//------------------Creating the aluminium box---------------------------------
	G4double aluminiumThickness = 3.0*mm;

	G4Material *boxMat = nist->FindOrBuildMaterial("G4_Cu");

	G4Box *solidOuterAluminiumBox = new G4Box("solidOuterAluminiumBox", 2.5/2*cm, 2.5/2*cm, 5.0/2*cm);
	G4Box *solidInnerAluminiumBox = new G4Box("solidInnerAluminiumBox", (2.5*cm - 2*aluminiumThickness)/2, (2.5*cm - 2*aluminiumThickness)/2, (5.0*cm - 2*aluminiumThickness)/2);
	G4SubtractionSolid *solidAluminiumBox = new G4SubtractionSolid("solidAluminiumBox", solidOuterAluminiumBox, solidInnerAluminiumBox, 0, G4ThreeVector(0.*mm, 0.*mm, 0.*mm));



	G4LogicalVolume *logicAluminiumBox = new G4LogicalVolume(solidAluminiumBox, boxMat, "logicAluminiumBox");

	G4VPhysicalVolume *physAluminiumBox = new G4PVPlacement(
			0,				// no rotation
			G4ThreeVector(0.,0.,0.),	// Placed at the center of the world volume
			logicAluminiumBox, 		// it's locical volume
			"AluminiumBox", 		// It's name
			logicWorld,			// logic volume of the mother
			false, 				// no boolean operator
			0, 				// copy number
			false); 				// checking for overlaps

//----------------Creating Silicon thingy------------------------------------

	G4double siliconThickness = 0.5*mm;

	G4Material *siliconMat =  nist->FindOrBuildMaterial("G4_Si");

	G4Box *solidSilicon = new G4Box("solidSilicon", 1./2 * cm, siliconThickness/2,1./2 * cm);

	substrateLogical = new G4LogicalVolume(solidSilicon, siliconMat, "logicalSilicon");

	G4VPhysicalVolume * physSilicon = new G4PVPlacement(
			0,
			G4ThreeVector(0, -2.5/2*cm + aluminiumThickness + siliconThickness/2, 0),
			substrateLogical,
			"Silicon",
			logicWorld,
			false,
			0,
			false);

//----------------Setting atributes before returning the mother volume--------
	G4VisAttributes* blue       = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0, 0.3));
    	blue->SetVisibility(true);
    	G4VisAttributes* red        = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0, 0.3));
    	red->SetVisibility(true);
    	G4VisAttributes* green      = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0, 0.2));
    	green->SetVisibility(true);
    	G4VisAttributes* white      = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.2));
    	white->SetVisibility(true);
    	G4VisAttributes* yellow     = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.1));
    	yellow->SetVisibility(true);
		G4VisAttributes* invisible  = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
    	invisible->SetVisibility(false);

	logicWorld->SetVisAttributes(invisible);
	logicAluminiumBox->SetVisAttributes(red);
	substrateLogical->SetVisAttributes(yellow);

//---------------Returning the mother volume---------------------------------
	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	auto detector = new SensitiveDetector("/SiliconSubstrate","SilliconHitsCollection");
	G4SDManager::GetSDMpointer()->AddNewDetector(detector);
	SetSensitiveDetector(substrateLogical,detector);
}