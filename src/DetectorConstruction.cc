#include "DetectorConstruction.hh"
#include "G4Colour.hh"

MyDetectorConstruction :: MyDetectorConstruction() : G4VUserDetectorConstruction()
{}

MyDetectorConstruction :: ~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
//------------------Loading the GDML files--------------------------------------
    
    // Readign the project of interest
        G4String folder = "saber";
		G4GDMLParser *parser = new G4GDMLParser();
        // parser -> Read("./geometry/" + folder + "/master.gdml");
		parser -> Read("./geometry/sensitiveDetector/sensitiveDetector.gdml");
		G4VPhysicalVolume *worldVolume = parser -> GetWorldVolume();
    // Reading the sensitive detector
        // GDMLParser -> Read("./geometry/sensitiveDetector/sensitiveDetector.gdml");

	parser -> GetVolume("logicSiliconSubstrate") -> SetVisAttributes(G4Colour(0,1,0));
	parser -> GetVolume("logicSiliconOxide") -> SetVisAttributes(G4Colour(1,0,0));
	parser -> GetVolume("logicSiliconNitride") -> SetVisAttributes(G4Colour(0,0,1));

//------------------Returning the mother volume---------------------------------
	return worldVolume;
}

void MyDetectorConstruction::ConstructSDandField()
{
	auto detector = new SensitiveDetector("/SiliconSubstrate","SilliconHitsCollection");
	G4SDManager::GetSDMpointer()->AddNewDetector(detector);
	// SetSensitiveDetector(logicSiliconOxide, detector);
	// SetSensitiveDetector(logicSiliconSubstrate, detector);
	// SetSensitiveDetector(logicSiliconNitride, detector);
}