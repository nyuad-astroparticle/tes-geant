#include "DetectorConstruction.hh"
#include "G4Colour.hh"

MyDetectorConstruction :: MyDetectorConstruction() : G4VUserDetectorConstruction()
{}

MyDetectorConstruction :: ~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();
//------------------Creating the world volume-----------------------------------

	G4Material 			*worldMat 		= nist->FindOrBuildMaterial("G4_Galactic");
	G4Box 				*solidWorld 	= new G4Box("solidWorld", 5.0*m, 5.0*m, 5.0*m);
	G4LogicalVolume 	*logicWorld 	= new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	G4VPhysicalVolume 	*physWorld 		= new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
	G4VisAttributes* invisible  = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
    invisible->SetVisibility(false);
	logicWorld -> SetVisAttributes(invisible);

//------------------Loading the GDML files--------------------------------------
    
    // Readign the project of interest
        G4String folder = "saber";
		G4GDMLParser parser;

		parser.Read("./geometry/tes/tesposition.gdml");
		G4VPhysicalVolume *tes = parser.GetWorldVolume();
		// G4double stackRotationAngle = 90*deg;
		// G4RotationMatrix *stackRotationMatrix = new G4RotationMatrix;
		// stackRotationMatrix -> rotateZ(stackRotationAngle);
		// tes 	-> SetRotation(stackRotationMatrix);

		parser.GetVolume("logicSiliconSubstrate") -> SetVisAttributes(G4Colour(0,1,0));
		parser.GetVolume("logicSiliconOxide") -> SetVisAttributes(G4Colour(1,0,0));
		parser.GetVolume("logicSiliconNitride") -> SetVisAttributes(G4Colour(0,0,1));
		logicWorld -> AddDaughter(tes);
		parser.Clear();

		parser.Read("./geometry/cryostat/cryostat.gdml");
		G4VPhysicalVolume *cryostat = parser.GetWorldVolume();
		// cryostat -> GetLogicalVolume() -> SetVisAttributes(G4Colour(0,1,0,0.1));
		parser.GetVolume("Cryostat_Aluminum") -> SetVisAttributes(G4Colour(0,1,0, 0.1));
		logicWorld -> AddDaughter(cryostat);
		parser.Clear();

		parser.Read("./geometry/copperBox/copperBox.gdml");
		parser.GetVolume("logicCopperBox") -> SetVisAttributes(G4Colour(1,0,0,0.5));
		logicWorld -> AddDaughter()


    // Reading the sensitive detector
        // GDMLParser -> Read("./geometry/sensitiveDetector/sensitiveDetector.gdml");


//------------------Returning the mother volume---------------------------------
	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	auto detector = new SensitiveDetector("/SiliconSubstrate","SilliconHitsCollection");
	G4SDManager::GetSDMpointer()->AddNewDetector(detector);
	// SetSensitiveDetector(logicSiliconOxide, detector);
	// SetSensitiveDetector(logicSiliconSubstrate, detector);
	// SetSensitiveDetector(logicSiliconNitride, detector);
}