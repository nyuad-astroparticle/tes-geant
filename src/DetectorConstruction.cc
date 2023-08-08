#include "DetectorConstruction.hh"

MyDetectorConstruction :: MyDetectorConstruction() : G4VUserDetectorConstruction()
{
    GDMLParser = new G4GDMLParser();
}

MyDetectorConstruction :: ~MyDetectorConstruction()
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

//------------------Loading the GDML files--------------------------------------
    
    // Readign the project of interest
        G4String folder = "saber";
        // GDMLParser -> Read("./geometry/" + folder + "/master.gdml");

    // Reading the sensitive detector
        GDMLParser -> Read("./geometry/sensitiveDetector/sensitiveDetector.gdml");

//---------------Returning the mother volume---------------------------------
	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	auto detector = new SensitiveDetector("/SiliconSubstrate","SilliconHitsCollection");
	G4SDManager::GetSDMpointer()->AddNewDetector(detector);
	SetSensitiveDetector(logicSiliconOxide, detector);
	SetSensitiveDetector(logicSiliconSubstrate, detector);
	SetSensitiveDetector(logicSiliconNitride, detector);
}