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
	G4VisAttributes* invisible  = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
    invisible->SetVisibility(false);

	if (GDMLParser.IsValid("logicTES"))
	{
		logicSiliconSubstrate 	= 	GDMLParser.GetVolume("logicSiliconSubstrate"); 	
		logicSiliconOxide 		= 	GDMLParser.GetVolume("logicSiliconOxide"); 		
		logicSiliconNitride 	=	GDMLParser.GetVolume("logicSiliconNitride");
				
		logicSiliconSubstrate 	-> 	SetVisAttributes(G4Colour(0,1,0));
		logicSiliconOxide		-> 	SetVisAttributes(G4Colour(1,0,0));
		logicSiliconNitride		-> 	SetVisAttributes(G4Colour(0,0,1, 0.1));
	}

	// GDMLParser.GetWorldVolume()->GetLogicalVolume()->

	if (GDMLParser.IsValid("logicSaber"))
	{
		logicSaber				= 	GDMLParser.GetVolume("logicSaber");
		logicSaber				->	SetVisAttributes(G4Colour(1,1,1));
	}

	if (GDMLParser.IsValid("logicCopperPlate"))
	{
		logicCopperPlate				= 	GDMLParser.GetVolume("logicCopperPlate");
		logicCopperPlate				->	SetVisAttributes(G4Colour(265,165,0));
	}

	if (GDMLParser.IsValid("Cryostat_Aluminum"))
	{
		GDMLParser.GetVolume("Cryostat_Aluminum") 			-> SetVisAttributes(G4Colour(0,1,0, 0.1));
	}
	if (GDMLParser.IsValid("logicCopperBox"))
	{
		GDMLParser.GetVolume("logicCopperBox") 				-> SetVisAttributes(G4Colour(1,0,0, 0.1));
	}
	if (GDMLParser.IsValid("logicThorium"))
	{
		GDMLParser.GetVolume("logicThorium")				-> SetVisAttributes(G4Colour(0,0,1));
	}

	if (GDMLParser.IsValid("logicBottomScintillators"))
	{
		GDMLParser.GetVolume("logicBottomScintillators")	-> SetVisAttributes(invisible);
		logicLong				= GDMLParser.GetVolume("logicLong");					
		logicShort 				= GDMLParser.GetVolume("logicShort");					
		
		logicLong											-> SetVisAttributes(G4Colour(1,1,1));
		logicShort 											-> SetVisAttributes(G4Colour(1,1,1));
	}


//------------------Returning the mother volume---------------------------------
	return GDMLParser.GetWorldVolume();
}

void MyDetectorConstruction::ConstructSDandField()
{
	auto detector = new SensitiveDetector("/SiliconSubstrate","SilliconHitsCollection");
	G4SDManager::GetSDMpointer()->AddNewDetector(detector);
	if (logicSiliconSubstrate)
	{
		SetSensitiveDetector(logicSiliconOxide, detector);
		SetSensitiveDetector(logicSiliconSubstrate, detector);
		SetSensitiveDetector(logicSiliconNitride, detector);
		SetSensitiveDetector(logicLong, detector);
		SetSensitiveDetector(logicShort, detector);
	}
	else if (logicSaber)
	{
		SetSensitiveDetector(logicSaber, detector);
	}
}
