#include "DetectorConstruction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
	fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");


	fMessenger->DeclareProperty("crossTopX", crossTopX, "The X position of the top cross");

	crossTopX = 0.;

	DefineMaterial();
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterial(){
	
	G4double a;
	G4double z;

	G4double density;                         // Density of material
	G4int ncomponents,number_of_atoms;        // Number of different elements, atoms

	G4NistManager *nist = G4NistManager::Instance();
	worldMat = nist->FindOrBuildMaterial("G4_AIR");
	boxMat = nist->FindOrBuildMaterial("G4_Cu");
	siliconMat =  nist->FindOrBuildMaterial("G4_Si");
	polystyrene = new G4Material("polystyrene",density= 1.05*g/cm3, ncomponents=2);

	C  = new G4Element("Carbon",     "C",    z=6.,   a=12.01*g/mole);
  	H  = new G4Element("Hydrogen",   "H",    z=1.,   a=1.008*g/mole);
    	polystyrene->AddElement(C, number_of_atoms=8);
    	polystyrene->AddElement(H, number_of_atoms=8);
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
//------------------Creating the world volume-----------------------------------

	solidWorld = new G4Box("solidWorld", 10.0*m, 10.0*m, 10.0*m);

	logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

	physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

//----------------Creating Aluminum Cylinder------------------------------------
	
	G4double cylinderThickness = 3.0*mm;
	G4double cylinderDiameter = 35.2 * cm;
	G4double cylinderHeight = 70*cm;

	G4double cylinderPosX = 0.*cm;
	G4double cylinderPosY = 0.*cm;
	G4double cylinderPosZ = 0.*cm;


	solidOuterCylinder = new G4Tubs(
			"solidOuterCylinder",
			0.*cm,
			cylinderDiameter/2,
			cylinderHeight/2,
			0.0 * deg, 360.0*deg
			);

	solidInnerCylinder = new G4Tubs(
			"solidInnerCylinder",
			0.*cm,
			cylinderDiameter/2 - cylinderThickness,
			cylinderHeight/2- cylinderThickness,
			0.0 * deg, 360.0*deg
			);
	G4SubtractionSolid * solidCylinder = new G4SubtractionSolid(
			"solidCylinder",
			solidOuterCylinder,
			solidInnerCylinder,
			0,
			G4ThreeVector(0.*mm, 0.*mm, 0.*mm)
			);
	logicalCylinder = new G4LogicalVolume(
			solidCylinder,
			boxMat,
			"logicalCylinder");
	G4RotationMatrix* rotationMatrix = new G4RotationMatrix();
	rotationMatrix->rotateX(90. * deg);

	physCylinder = new G4PVPlacement(
			rotationMatrix,
			G4ThreeVector(cylinderPosX, cylinderPosY, cylinderPosZ),
			  logicalCylinder,
			  "physCylinder",
			  logicWorld,
			  false,
			  0,
			  false);
//------------------Creating the aluminium box---------------------------------
	G4double aluminiumThickness = 3.0*mm;
	G4double aluminiumBoxX = 2.5*cm;
	G4double aluminiumBoxY = 2.5*cm;
	G4double aluminiumBoxZ = 5.0*cm;

	G4double aluminiumBoxPosX = 0.*cm;
	G4double aluminiumBoxPosY = - cylinderHeight/2 + cylinderThickness + 20*cm + aluminiumThickness;
	G4double aluminiumBoxPosZ = 0.*cm;


	solidOuterAluminiumBox = new G4Box("solidOuterAluminiumBox", aluminiumBoxX/2., aluminiumBoxY/2., aluminiumBoxZ/2.);
	solidInnerAluminiumBox = new G4Box("solidInnerAluminiumBox", (aluminiumBoxX - 2*aluminiumThickness)/2, (aluminiumBoxY - 2*aluminiumThickness)/2, (aluminiumBoxZ - 2*aluminiumThickness)/2);
	G4SubtractionSolid *solidAluminiumBox = new G4SubtractionSolid("solidAluminiumBox", solidOuterAluminiumBox, solidInnerAluminiumBox, 0, G4ThreeVector(0.*mm, 0.*mm, 0.*mm));



	logicAluminiumBox = new G4LogicalVolume(solidAluminiumBox, boxMat, "logicAluminiumBox");

	physAluminiumBox = new G4PVPlacement(
			0,									// no rotation
			G4ThreeVector(aluminiumBoxPosX, aluminiumBoxPosY, aluminiumBoxPosZ),	// Placed at the center of the world volume
			logicAluminiumBox, 							// it's locical volume
			"AluminiumBox", 							// It's name
			logicWorld,								// logic volume of the mother
			false, 									// no boolean operator
			0, 									// copy number
			false); 								// checking for overlaps

//----------------Creating Silicon thingy------------------------------------

	G4double siliconThickness = 0.5*mm;
	G4double siliconX = 1.*cm;
	G4double siliconY = siliconThickness;
	G4double siliconZ = 1.*cm;

	G4double siliconPosX = 0.*cm;
	G4double siliconPosY = aluminiumBoxPosY - aluminiumBoxY/2 + aluminiumThickness + siliconThickness;
	G4double siliconPosZ = 0.*cm;



	solidSilicon = new G4Box(
			"solidSilicon",
			siliconX/2.,
			siliconY/2.,
			siliconZ/2.);

	substrateLogical = new G4LogicalVolume(solidSilicon, siliconMat, "logicalSilicon");

	physSilicon = new G4PVPlacement(
			0,
			G4ThreeVector(siliconPosX, siliconPosY, siliconPosZ),
			substrateLogical,
			"Silicon",
			logicWorld,
			false,
			0,
			false);

//----------------Creating Scintillator Paddles------------------------------

	G4double paddleX = 20. * cm;
	G4double paddleY = 1. * cm;
	G4double paddleZ = 60. * cm;

	G4double paddleOffset = 1.*cm; 

	G4double paddleBottomX = 0.*cm;
	G4double paddleBottomY = -(cylinderHeight/2 + cylinderPosY + paddleY/2 + paddleOffset);
	G4double paddleBottomZ = 0.*cm;

	G4double paddleTopX = 0.*cm;
	G4double paddleTopY = (cylinderHeight/2 + cylinderPosY + paddleY/2 + paddleOffset);
	G4double paddleTopZ = 0.*cm;

	solidPaddle = new G4Box(
			"solidPaddle",
			paddleX/2.,
			paddleY/2.,
			paddleZ/2.);
	paddleLogical = new G4LogicalVolume(
			solidPaddle,
			polystyrene,
			"paddleLogical");
	physPaddleBottom = new G4PVPlacement(
			0, 
			G4ThreeVector(paddleBottomX, paddleBottomY, paddleBottomZ),
			paddleLogical,
			"physPaddleBottom",
			logicWorld,
			false,
			0,
			false);
	physPaddleTop = new G4PVPlacement(
			0, 
			G4ThreeVector(paddleTopX, paddleTopY, paddleTopZ),
			paddleLogical,
			"physPaddleTop",
			logicWorld,
			false,
			0,
			false);

//----------------Creating Crosses---------------------------­---------------

	G4double crossX = 2.*cm;
	G4double crossY = 1.*cm;
	G4double crossZ = 2.*cm;

	G4double crossOffset = 1.*cm;

	G4cout<<crossTopX<<G4endl;	
	G4double crossTopY = cylinderHeight/2 + paddleOffset + paddleY + crossOffset +crossY/2;
	G4double crossTopZ = 0.*cm;

	G4double crossBottomX = 0.*cm;
	G4double crossBottomY = -(cylinderHeight/2 + paddleOffset + paddleY + crossOffset +crossY/2);
	G4double crossBottomZ = 0.*cm;
	
	solidCross = new G4Box(
			"solidCross",
			crossX/2.,
			crossY/2.,
			crossZ/2.);
	crossLogical = new G4LogicalVolume(
			solidCross,
			polystyrene,
			"crossLogical");
	physCrossTop = new G4PVPlacement(
			0,
			G4ThreeVector(crossTopX*cm, crossTopY, crossTopZ),
			crossLogical,
			"physCrossTop",
			logicWorld,
			false,
			0,
			false);

	physCrossBottom = new G4PVPlacement(
			0,
			G4ThreeVector(crossBottomX, crossBottomY, crossBottomZ),
			crossLogical,
			"physCrossBottom",
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
	paddleLogical->SetVisAttributes(blue);
	crossLogical->SetVisAttributes(white);

//---------------Returning the mother volume---------------------------------
	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	auto detector = new SensitiveDetector("/SiliconSubstrate","SilliconHitsCollection");
	G4SDManager::GetSDMpointer()->AddNewDetector(detector);
	SetSensitiveDetector(substrateLogical,detector);
	SetSensitiveDetector(paddleLogical,detector);
	SetSensitiveDetector(crossLogical,detector);
}
