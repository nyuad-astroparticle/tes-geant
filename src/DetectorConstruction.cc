#include "DetectorConstruction.hh"
#include <cmath>
#include "CADMesh.hh"

MyDetectorConstruction::MyDetectorConstruction() : G4VUserDetectorConstruction()
{
	GDMLParser = new G4GDMLParser();
}

MyDetectorConstruction::~MyDetectorConstruction()
{
	delete GDMLParser;
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();
//------------------Creating the world volume-----------------------------------
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic");

	G4Box *solidWorld = new G4Box("solidWorld", 5.0*m, 5.0*m, 5.0*m);

	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

//----------------Creating Aluminum Cylinder------------------------------------
	
	G4double cylinderThickness = 3.0*mm;
	G4double cylinderDiameter = 35.2 * cm;
	G4double cylinderHeight = 106*cm;

	G4double cylinderPosX = 0.*cm;
	G4double cylinderPosY = 0.*cm;
	G4double cylinderPosZ = 0.*cm;

	G4Material *boxMat = nist->FindOrBuildMaterial("G4_Cu");

G4double yShift = 17.0 * cm

#ifdef GDML_ACTIVE
	// Loading the cryostat using GDML
	GDMLParser->Read("./geometry/cryostat.gdml",true);

	G4LogicalVolume* 	logicalCryostat = GDMLParser->GetVolume("Cryostat_Aluminum");
	// logicalCryostat -> SetUserLimits(mySteplimit);
	G4VPhysicalVolume*	physCryostat 	= new G4PVPlacement(
			0,															// No rotation
			G4ThreeVector(cylinderPosX, cylinderPosY + yShift, cylinderPosZ),	// Center Position
			logicalCryostat,
			"physCryostat",
			logicWorld,
			false,
			0,
			false);
#endif

#ifndef GDML_ACTIVE
	// Trying to load the cryostat using CADMesh

	G4ThreeVector cryostatCenter(cylinderPosX, cylinderPosY + yShift, cylinderPosZ);


	G4Material * aluminum = nist -> FindOrBuildMaterial("G4_Al");
	auto mesh = CADMesh::TessellatedMesh::FromPLY("../geometry/cryostat.stl");
	auto meshSolid = mesh -> GetSolid();
	G4LogicalVolume * meshLogical = new G4LogicalVolume(meshSolid, aluminum, "meshLogical");
	// meshLogical -> SetUserLimits(mySteplimit);

	G4VPhysicalVolume * meshPhysical = new G4PVPlacement(0, cryostatCenter, meshLogical, "meshPhysical", logicWorld, false, 0, true);
#endif



//------------------Creating the aluminium box---------------------------------
	G4double aluminiumThickness = 3.0*mm;
	G4double aluminiumBoxX = 2.5*cm;
	G4double aluminiumBoxY = 2.5*cm;
	G4double aluminiumBoxZ = 5.0*cm;

	G4double aluminiumBoxPosX = - 4.5*cm;
	G4double aluminiumBoxPosY = - cylinderHeight/2 + cylinderThickness + yShift - 1.*cm + aluminiumThickness;
	G4double aluminiumBoxPosZ = - 1.*cm;


	G4Box *solidOuterAluminiumBox = new G4Box("solidOuterAluminiumBox", aluminiumBoxX/2., aluminiumBoxY/2., aluminiumBoxZ/2.);
	G4Box *solidInnerAluminiumBox = new G4Box("solidInnerAluminiumBox", (aluminiumBoxX - 2*aluminiumThickness)/2, (aluminiumBoxY - 2*aluminiumThickness)/2, (aluminiumBoxZ - 2*aluminiumThickness)/2);
	G4SubtractionSolid *solidAluminiumBox = new G4SubtractionSolid("solidAluminiumBox", solidOuterAluminiumBox, solidInnerAluminiumBox, 0, G4ThreeVector(0.*mm, 0.*mm, 0.*mm));



	G4LogicalVolume *logicAluminiumBox = new G4LogicalVolume(solidAluminiumBox, boxMat, "logicAluminiumBox");

	G4VPhysicalVolume *physAluminiumBox = new G4PVPlacement(
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
	G4double siliconX = 0.5*cm;
	G4double siliconY = siliconThickness;
	G4double siliconZ = 0.5*cm;

	G4double siliconPosX = 0.*cm;
	G4double siliconPosY = aluminiumBoxPosY - aluminiumBoxY/2 + aluminiumThickness + siliconThickness;
	G4double siliconPosZ = 0.*cm;


//------------Replacing the Silicon Thingy with a stack---------------------- 

	// General stack properties

		G4double stackLengthX = siliconX;
		G4double stackLengthZ = siliconZ;

		G4double stackHeight = stackLengthX;
		G4double stackPosX = aluminiumBoxPosX;
		G4double stackPosY = aluminiumBoxPosY - aluminiumBoxY/2 + aluminiumThickness + stackHeight; // used this line from previous code
		G4double stackPosZ = aluminiumBoxPosZ;


	// Adding Materials

		// Si3N4
		G4double siliconNitrideDensity = 3.17 * g/cm3; // source: Wikipedia, correct if wrong
		G4Material * siliconNitride = new G4Material("siliconNitride", siliconNitrideDensity, 2);
		G4Element  * Si = nist->FindOrBuildElement("Si");
		G4Element  * N = nist->FindOrBuildElement("N");
		siliconNitride -> AddElement(Si, 3);
		siliconNitride -> AddElement(N , 4);


		// SiO2
		G4double siliconOxideDensity = 2.65 * g/cm3; // source : Wikipedia, correct if wrong 
		G4Material * siliconOxide = new G4Material("siliconOxide", siliconOxideDensity, 2);
		G4Element  * O = nist->FindOrBuildElement("O");
		siliconOxide -> AddElement(Si, 1);
		siliconOxide -> AddElement(O , 2);

		// Si
		G4Material * Silicon = nist -> FindOrBuildMaterial("G4_Si");
	
	// Silicon inner layer
		G4double siliconSubstrateHeight = 5. * mm;

		G4ThreeVector siliconSubstrateCenter(stackPosX, stackPosY , stackPosZ);

		G4Box * solidSiliconSubstrate = new G4Box("solidSiliconSubstrate", stackLengthX/2, siliconSubstrateHeight/2 , stackLengthZ/2);

		logicSiliconSubstrate = new G4LogicalVolume(solidSiliconSubstrate, Silicon, "logicSiliconSubstrate");

		G4VPhysicalVolume *physSiliconSubstrate = new G4PVPlacement(0, siliconSubstrateCenter, logicSiliconSubstrate, \
							"physSiliconSubstrate", logicWorld, false, 0, true);
	
	// Silicon Oxide inner two layers

		G4double siliconOxideHeight = 150. * nm;

		G4double silicondOxideRelativeY = siliconSubstrateHeight/2 + siliconOxideHeight/2;

		G4ThreeVector siliconOxideCenter1(stackPosX, stackPosY + silicondOxideRelativeY, stackPosZ);
		G4ThreeVector siliconOxideCenter2(stackPosX, stackPosY - silicondOxideRelativeY, stackPosZ);

		G4Box * solidSiliconOxide = new G4Box("solidSiliconOxide", stackLengthX/2, siliconOxideHeight/2, stackLengthZ/2);
		logicSiliconOxide = new G4LogicalVolume(solidSiliconOxide, siliconOxide, "logicSiliconOxide");

		G4VPhysicalVolume * physSiliconOxide1 = new G4PVPlacement(0, siliconOxideCenter1, logicSiliconOxide, \
							"physSiliconOxide1", logicWorld, false, 0 , true);
		G4VPhysicalVolume * physSiliconOxide2 = new G4PVPlacement(0, siliconOxideCenter2, logicSiliconOxide, \
							"physSiliconOxide2", logicWorld, false, 0 , true);

	// Silicon Nitride outer two layers

		G4double siliconNitrideHeight = 500. * nm;

		G4double siliconNitrideRelativeY = siliconSubstrateHeight/2 + siliconOxideHeight + siliconNitrideHeight/2;
		
		G4ThreeVector siliconNitrideCenter1(stackPosX, stackPosY + siliconNitrideRelativeY, stackPosZ);
		G4ThreeVector siliconNitrideCenter2(stackPosX, stackPosY - siliconNitrideRelativeY, stackPosZ);

		G4Box * solidSiliconNitride = new G4Box("solidSiliconNitride", stackLengthX/2, siliconNitrideHeight/2, stackLengthZ/2);
		logicSiliconNitride = new G4LogicalVolume(solidSiliconNitride, siliconNitride, "logicSiliconNitride");
		
		G4VPhysicalVolume * physSiliconNitride1 = new G4PVPlacement(0, siliconNitrideCenter1, logicSiliconNitride, \
							"physSiliconNitride1", logicWorld, false, 0 , true);
		G4VPhysicalVolume * physSiliconNitride2 = new G4PVPlacement(0, siliconNitrideCenter2, logicSiliconNitride, \
							"physSiliconNitride2", logicWorld, false, 0 , true);

	
	// Setting up the rotation of the stack around X axis

		G4double stackRotationAngle = M_PI/2;
		G4RotationMatrix *stackRotationMatrix = new G4RotationMatrix;
		stackRotationMatrix -> rotateX(stackRotationAngle);


		physSiliconSubstrate 	-> SetRotation(stackRotationMatrix);


		physSiliconOxide1 		-> SetRotation(stackRotationMatrix);
		physSiliconOxide1		-> SetTranslation(G4ThreeVector(stackPosX, stackPosY + silicondOxideRelativeY * std::cos(stackRotationAngle),stackPosZ - silicondOxideRelativeY * std::sin(stackRotationAngle)));
		physSiliconOxide2 		-> SetRotation(stackRotationMatrix);
		physSiliconOxide2		-> SetTranslation(G4ThreeVector(stackPosX, stackPosY - silicondOxideRelativeY * std::cos(stackRotationAngle), stackPosZ + silicondOxideRelativeY * std::sin(stackRotationAngle)));
		physSiliconNitride1 	-> SetRotation(stackRotationMatrix);
		physSiliconNitride1		-> SetTranslation(G4ThreeVector(stackPosX, stackPosY + siliconNitrideRelativeY * std::cos(stackRotationAngle), stackPosZ - siliconNitrideRelativeY * std::sin(stackRotationAngle)));
		physSiliconNitride2 	-> SetRotation(stackRotationMatrix);
		physSiliconNitride2		-> SetTranslation(G4ThreeVector(stackPosX, stackPosY - siliconNitrideRelativeY * std::cos(stackRotationAngle), stackPosZ + siliconNitrideRelativeY * std::sin(stackRotationAngle)));
		
		
#ifndef ADD_PADDLES

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

	G4Box * solidPaddle = new G4Box(
			"solidPaddle",
			paddleX/2.,
			paddleY/2.,
			paddleZ/2.);
	paddleLogical = new G4LogicalVolume(
			solidPaddle,
			polystyrene,
			"paddleLogical");
	G4VPhysicalVolume * physPaddleBottom = new G4PVPlacement(
			0, 
			G4ThreeVector(paddleBottomX, paddleBottomY, paddleBottomZ),
			paddleLogical,
			"physPaddleBottom",
			logicWorld,
			false,
			0,
			false);
	G4VPhysicalVolume * physPaddleTop = new G4PVPlacement(
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

	G4double crossTopX = 0.*cm;
	G4double crossTopY = cylinderHeight/2 + paddleOffset + paddleY + crossOffset +crossY/2;
	G4double crossTopZ = 0.*cm;

	G4double crossBottomX = 0.*cm;
	G4double crossBottomY = -(cylinderHeight/2 + paddleOffset + paddleY + crossOffset +crossY/2);
	G4double crossBottomZ = 0.*cm;
	
	G4Box * solidCross = new G4Box(
			"solidCross",
			crossX/2.,
			crossY/2.,
			crossZ/2.);
	crossLogical = new G4LogicalVolume(
			solidCross,
			polystyrene,
			"crossLogical");
	G4VPhysicalVolume * physCrossTop = new G4PVPlacement(
			0,
			G4ThreeVector(crossTopX, crossTopY, crossTopZ),
			crossLogical,
			"physCrossTop",
			logicWorld,
			false,
			0,
			false);

	G4VPhysicalVolume * physCrossBottom = new G4PVPlacement(
			0,
			G4ThreeVector(crossBottomX, crossBottomY, crossBottomZ),
			crossLogical,
			"physCrossBottom",
			logicWorld,
			false,
			0,
			false);

#endif

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

	logicWorld				-> SetVisAttributes(invisible);
	logicAluminiumBox		-> SetVisAttributes(red);
	// logicalCylinder->SetVisAttributes(green);
	// substrateLogical->SetVisAttributes(yellow);

#ifdef ADD_PADDLES
	paddleLogical			-> SetVisAttributes(blue);
	crossLogical			-> SetVisAttributes(white);
#endif
	logicSiliconNitride 	-> SetVisAttributes(red);
	logicSiliconOxide 		-> SetVisAttributes(blue);
	logicSiliconSubstrate 	-> SetVisAttributes(green);
	logicWorld				-> SetVisAttributes(yellow);

#ifdef GDML_ACTIVE
	logicalCryostat			-> SetVisAttributes(green);
#endif

#ifndef GDML_ACTIVE
	meshLogical 			-> SetVisAttributes(white);
#endif

//---------------Returning the mother volume---------------------------------
	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	auto detector = new SensitiveDetector("/SiliconSubstrate","SilliconHitsCollection");
	G4SDManager::GetSDMpointer()->AddNewDetector(detector);
	// SetSensitiveDetector(substrateLogical,detector);
	
#ifdef ADD_PADDLES
	SetSensitiveDetector(paddleLogical,detector);
	SetSensitiveDetector(crossLogical,detector);
#endif
	SetSensitiveDetector(logicSiliconOxide, detector);
	SetSensitiveDetector(logicSiliconSubstrate, detector);
	SetSensitiveDetector(logicSiliconNitride, detector);
}
