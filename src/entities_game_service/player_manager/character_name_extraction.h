/** file character_name_extraction.h
 * $id$
 */

#ifndef CHARACTER_NAME_EXTRACTION_H
#define CHARACTER_NAME_EXTRACTION_H

#include "game_share/persistent_data.h"


//-----------------------------------------------------------------------------
// class CEntityBaseNameExtraction
//-----------------------------------------------------------------------------

class CEntityBaseNameExtraction
{
public:
	DECLARE_PERSISTENCE_APPLY_METHOD

	std::string Name;
};


//-----------------------------------------------------------------------------
// class CCharacterNameExtraction
//-----------------------------------------------------------------------------

struct CCharacterNameExtraction: CEntityBaseNameExtraction
{
public:
	DECLARE_PERSISTENCE_APPLY_METHOD
};


//-----------------------------------------------------------------------------
#endif
