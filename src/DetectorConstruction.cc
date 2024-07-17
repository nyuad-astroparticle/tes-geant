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

	// Example how to retrieve Auxiliary Information for sensitive detector taken directly from G04 example 

	const G4GDMLAuxMapType* auxmap = GDMLParser.GetAuxMap();
	G4cout << "Found " << auxmap->size()
			<< " volume(s) with auxiliary information."
			<< G4endl << G4endl;

	for (G4GDMLAuxMapType::const_iterator iter = auxmap->begin(); iter != auxmap->end(); iter++) 
	{
		G4cout << "Volume " << ((*iter).first)->GetName()
			<< " has the following list of auxiliary information: "
			<< G4endl << G4endl;

		G4double r = 1.0, g = 1.0, b = 1.0; // Default color values
		G4double transparency = 1.0; // Default transparency value

		for (G4GDMLAuxListType::const_iterator vit = (*iter).second.begin(); vit != (*iter).second.end(); vit++)
		{
			G4cout << "--> Type: " << (*vit).type << " Value: " << (*vit).value << G4endl;
			
			// Check if the auxiliary information is for color
			if ((*vit).type == "Color") 
			{
				// Parse the color string into three separate float values
				std::istringstream iss((*vit).value);
				if (!(iss >> r >> g >> b)) 
				{
					G4cerr << "Error parsing color string: " << (*vit).value << G4endl;
				}
			}
			// Check if the auxiliary information is for transparency
			else if ((*vit).type == "Transparency") 
			{
				// Parse the transparency string into a single float value
				std::istringstream iss((*vit).value);
				if (!(iss >> transparency)) 
				{
					G4cerr << "Error parsing transparency string: " << (*vit).value << G4endl;
				}
			}
		}

		// Create a G4Colour object with the parsed values
		G4Colour colour(r, g, b, transparency);

		// Create and set the visualization attributes
		G4VisAttributes* visAttributes = new G4VisAttributes(colour);
		visAttributes->SetVisibility(true);

		// Assign the visualization attributes to the volume
		((*iter).first)->SetVisAttributes(visAttributes);
	}

	G4cout << G4endl;

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
	// 	logicSaber				->	SetVisAttributes(G4Colour(1,1,1, 0.4));
	}

	// if (GDMLParser.IsValid("logicCopperPlate"))
	// {
		// logicCopperPlate				= 	GDMLParser.GetVolume("logicCopperPlate");
	// 	logicCopperPlate				->	SetVisAttributes(G4Colour(265,165,0));
	// }

	// if (GDMLParser.IsValid("Cryostat_Aluminum"))
	// {
	// 	GDMLParser.GetVolume("Cryostat_Aluminum") 			-> SetVisAttributes(G4Colour(0,1,0, 0.1));
	// 	GDMLParser.GetVolume("logicMagneticShield")			-> SetVisAttributes(G4Color(1,1,0.5,0.1));
	// }
	// if (GDMLParser.IsValid("logicCopperBox"))
	// {
	// 	GDMLParser.GetVolume("logicCopperBox") 				-> SetVisAttributes(invisible);
	// 	GDMLParser.GetVolume("logicBox") 					-> SetVisAttributes(G4Colour(1,0,0,0.1));
	// }
	// if (GDMLParser.IsValid("logicThorium"))
	// {
		// logicThorium = GDMLParser.GetVolume("logicThorium");				
	// 	logicThorium -> SetVisAttributes(G4Colour(0,0,1));
	// 	// GDMLParser.GetVolume("logicAluminumFoil")			-> SetVisAttributes(G4Color(1,1,1,0.2));
	// 	GDMLParser.GetVolume("logicThoriumMotherVolume")	-> SetVisAttributes(invisible);
	// }

	if (GDMLParser.IsValid("logicBottomScintillators"))
	{
		GDMLParser.GetVolume("logicBottomScintillators")	-> SetVisAttributes(invisible);
		GDMLParser.GetVolume("logicTapeLong")				-> SetVisAttributes(G4Color(0,0,0,0.4));
		GDMLParser.GetVolume("logicTapeShort")				-> SetVisAttributes(G4Color(0,0,0,0.4));
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

	// SetSensitiveDetector(logicThorium, detector);
}
