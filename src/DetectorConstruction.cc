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
		G4LogicalVolume	*logicTESE	= 	GDMLParser.GetVolume("logicTESE");
		logicTESE 					->	SetVisAttributes(invisible);
		
		logicSiliconSubstrateE 	= 	GDMLParser.GetVolume("logicSiliconSubstrateE"); 	
		logicSiliconOxideE 		= 	GDMLParser.GetVolume("logicSiliconOxideE"); 		
		logicSiliconNitrideE 	=	GDMLParser.GetVolume("logicSiliconNitrideE");
				
		logicSiliconSubstrateE 	-> 	SetVisAttributes(G4Colour(0,1,0));
		logicSiliconOxideE		-> 	SetVisAttributes(G4Colour(1,0,0));
		logicSiliconNitrideE		-> 	SetVisAttributes(G4Colour(0,0,1, 0.1));

		G4LogicalVolume	*logicTESB	= 	GDMLParser.GetVolume("logicTESB");
		logicTESB 					->	SetVisAttributes(invisible);
		
		logicSiliconSubstrateB 	= 	GDMLParser.GetVolume("logicSiliconSubstrateB"); 	
		logicSiliconOxideB 		= 	GDMLParser.GetVolume("logicSiliconOxideB"); 		
		logicSiliconNitrideB 	=	GDMLParser.GetVolume("logicSiliconNitrideB");
				
		logicSiliconSubstrateB 	-> 	SetVisAttributes(G4Colour(0,1,0));
		logicSiliconOxideB		-> 	SetVisAttributes(G4Colour(1,0,0));
		logicSiliconNitrideB	-> 	SetVisAttributes(G4Colour(0,0,1, 0.1));
	}
	
	if (GDMLParser.IsValid("logicDetectorSaber"))
	{
		logicSaber				= 	GDMLParser.GetVolume("logicDetectorSaber");
		logicSaber				->	SetVisAttributes(G4Colour(1,1,1, 0.4));
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
		GDMLParser.GetVolume("logicCopperBox") 				-> SetVisAttributes(invisible);
		GDMLParser.GetVolume("logicBox") 					-> SetVisAttributes(G4Colour(1,0,0,0.1));
	}
	if (GDMLParser.IsValid("logicThorium"))
	{
		GDMLParser.GetVolume("logicThorium")				-> SetVisAttributes(G4Colour(0,0,1));
		GDMLParser.GetVolume("logicAluminumFoil")			-> SetVisAttributes(G4Color(1,1,1,0.2));
		GDMLParser.GetVolume("logicThoriumMotherVolume")	-> SetVisAttributes(invisible);
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
	auto detector = new SensitiveDetector("/SiliconSubstrate","SilliconHitsCollection", eventAction);
	G4SDManager::GetSDMpointer()->AddNewDetector(detector);
	if (logicSiliconSubstrateE)
	{
		SetSensitiveDetector(logicSiliconOxideE, detector);
		SetSensitiveDetector(logicSiliconSubstrateE, detector);
		SetSensitiveDetector(logicSiliconNitrideE, detector);
		SetSensitiveDetector(logicSiliconOxideB, detector);
		SetSensitiveDetector(logicSiliconSubstrateB, detector);
		SetSensitiveDetector(logicSiliconNitrideB, detector);
	}
	if (logicLong)
	{
		SetSensitiveDetector(logicLong, detector);
		SetSensitiveDetector(logicShort, detector);
	}
	else if (logicSaber)
	{
		SetSensitiveDetector(logicSaber, detector);
	}
}
