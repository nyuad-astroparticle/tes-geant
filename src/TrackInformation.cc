/************************
•     ┓             •    
┓┏┳┓┏┓┃┏┓┏┳┓┏┓┏┓╋┏┓╋┓┏┓┏┓
┗┛┗┗┣┛┗┗ ┛┗┗┗ ┛┗┗┗┻┗┗┗┛┛┗
    ┛                    
    Track Information

Stores the ID of the
first generation migrant
that created the track
************************/

// The relevant headerfile
#include "TrackInformation.hh"

// Constructor
TrackInformation::TrackInformation(G4int id) : migrantID(id)
{}

//----------------------- 8< -------------[ cut here ]------------------------

// Destructor
TrackInformation::~TrackInformation()
{}

//----------------------- 8< -------------[ cut here ]------------------------

// Mutators
void        TrackInformation::SetMigrantID(G4int migrantID) { this->migrantID = migrantID; }
const G4int TrackInformation::GetMigrantID()                { return migrantID; }