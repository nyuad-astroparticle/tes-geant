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

	G4Box *solidWorld = new G4Box("solidWorld", 10.0*m, 10.0*m, 10.0*m);

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
			G4ThreeVector(0.,-20. * cm,0.),	// Placed at the center of the world volume
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
			G4ThreeVector(0, -2.5/2*cm + aluminiumThickness + siliconThickness/2 - 20. * cm, 0),
			substrateLogical,
			"Silicon",
			logicWorld,
			false,
			0,
			false);

//----------------Creating Aluminum Cylinder------------------------------------
	
	G4double cylinderThickness = 3.0*mm;

	G4Tubs *solidOuterCylinder = new G4Tubs(
			"solidOuterCylinder",
			0.*cm,
			(35.2/2) * cm,
			(70.0/2.)*cm,
			0.0 * deg, 360.0*deg
			);

	G4Tubs *solidInnerCylinder = new G4Tubs(
			"solidInnerCylinder",
			0.*cm,
			(35.2/2) * cm - cylinderThickness,
			(70.0/2.)*cm - 2*cylinderThickness,
			0.0 * deg, 360.0*deg
			);
	G4SubtractionSolid * solidCylinder = new G4SubtractionSolid(
			"solidCylinder",
			solidOuterCylinder,
			solidInnerCylinder,
			0,
			G4ThreeVector(0.*mm, 0.*mm, 0.*mm)
			);
	G4LogicalVolume * logicalCylinder = new G4LogicalVolume(
			solidCylinder,
			boxMat,
			"logicalCylinder");
	G4RotationMatrix* rotationMatrix = new G4RotationMatrix();
	rotationMatrix->rotateX(90. * deg);

	G4VPhysicalVolume * physCylinder = new G4PVPlacement(
			rotationMatrix,
			G4ThreeVector(0, 0, 0),
			  logicalCylinder,
			  "physCylinder",
			  logicWorld,
			  false,
			  0,
			  false);
//----------------Creating Scintillator Paddles------------------------------
	G4double a;
	G4double z;

	G4double density;                         // Density of material
	G4int ncomponents,number_of_atoms;        // Number of different elements, atoms
	G4Material* polystyrene = new G4Material("polystyrene",density= 1.05*g/cm3, ncomponents=2);

	G4Element* C  = new G4Element("Carbon",     "C",    z=6.,   a=12.01*g/mole);
  	G4Element* H  = new G4Element("Hydrogen",   "H",    z=1.,   a=1.008*g/mole);

    	polystyrene->AddElement(C, number_of_atoms=8);
    	polystyrene->AddElement(H, number_of_atoms=8);

	G4Box * solidPaddle = new G4Box(
			"solidPaddle",
			20./2.*cm,
			1./2.*cm,
			60./2.*cm);
	G4LogicalVolume * logicalPaddle = new G4LogicalVolume(
			solidPaddle,
			polystyrene,
			"logicalPaddle");
	G4VPhysicalVolume * physPaddleBottom = new G4PVPlacement(
			0, 
			G4ThreeVector(0, -(35.2 + 1. + 2.)*cm, 0),
			logicalPaddle,
			"physPaddleBottom",
			logicWorld,
			false,
			0,
			false);
	G4VPhysicalVolume * physPaddleTop = new G4PVPlacement(
			0, 
			G4ThreeVector(0, (35.2 + 1./2. + 2.)*cm, 0),
			logicalPaddle,
			"physPaddleTop",
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
	logicalCylinder->SetVisAttributes(green);
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
