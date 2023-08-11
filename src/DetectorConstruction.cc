#include "DetectorConstruction.hh"
#include "G4Colour.hh"

MyDetectorConstruction :: MyDetectorConstruction(const G4GDMLParser& parser) : G4VUserDetectorConstruction() , GDMLParser(parser)
{
}

MyDetectorConstruction :: ~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{

//------------------Set visual attributes---------------------------------------
	if (GDMLParser.GetVolume("logicTES"))
	{
		logicSiliconSubstrate 	= 	GDMLParser.GetVolume("logicSiliconSubstrate"); 	
		logicSiliconOxide 		= 	GDMLParser.GetVolume("logicSiliconOxide"); 		
		logicSiliconNitride 	=	GDMLParser.GetVolume("logicSiliconNitride");
				
		logicSiliconSubstrate 	-> 	SetVisAttributes(G4Colour(0,1,0));
		logicSiliconOxide		-> 	SetVisAttributes(G4Colour(1,0,0));
		logicSiliconNitride		-> 	SetVisAttributes(G4Colour(0,0,1, 0.1));
	}

	if (GDMLParser.GetVolume("Cryostat_Aluminum"))
	{
		GDMLParser.GetVolume("Cryostat_Aluminum") 	-> SetVisAttributes(G4Colour(0,1,0, 0.1));
	}

	if (GDMLParser.GetVolume("logicCopperBox"))
	{
		GDMLParser.GetVolume("logicCopperBox") 		-> SetVisAttributes(G4Colour(1,0,0, 0.1));
	}

//------------------Returning the mother volume---------------------------------
	return GDMLParser.GetWorldVolume();
}

void MyDetectorConstruction::ConstructSDandField()
{
	auto detector = new SensitiveDetector("/SiliconSubstrate","SilliconHitsCollection");
	G4SDManager::GetSDMpointer()->AddNewDetector(detector);
	SetSensitiveDetector(logicSiliconOxide, detector);
	SetSensitiveDetector(logicSiliconSubstrate, detector);
	SetSensitiveDetector(logicSiliconNitride, detector);
}