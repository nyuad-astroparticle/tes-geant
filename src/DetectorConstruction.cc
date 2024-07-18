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


//------------------Returning the mother volume---------------------------------
	return GDMLParser.GetWorldVolume();
}

void MyDetectorConstruction::ConstructSDandField()
{
	// the same thing but for senstivie detector. just the type "SendDet" is enough
	auto detector = new SensitiveDetector("/SiliconSubstrate","SilliconHitsCollection", eventAction);
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	SDman -> AddNewDetector(detector);

	
	const G4GDMLAuxMapType* auxmap = GDMLParser.GetAuxMap();
	for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();
      iter!=auxmap->end(); iter++) 
	{
		for (G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();
			vit!=(*iter).second.end();vit++)
		{
			if ((*vit).type=="SensDet")
			{
				G4cout << "Attaching sensitive detector " << (*vit).value
					<< " to volume " << ((*iter).first)->GetName()
					<<  G4endl << G4endl;

				SetSensitiveDetector((*iter).first, detector);
			}
		}
	}
}
