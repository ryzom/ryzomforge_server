/** \file variables.cpp
 * <File description>
 *
 * $Id: variables.cpp,v 1.2 2004/03/01 19:22:05 lecroart Exp $
 */



#include "variables.h"

#include "nel/misc/variable.h"
#include "nel/misc/entity_id.h"

#include "world_position_manager.h"

using namespace std;
using namespace NLMISC;

uint32			NumEntities			= 0;
uint32			NumPlayers			= 0;
bool			Verbose				= false;
bool			CheckPlayerSpeed	= true;


//
NLMISC_VARIABLE(uint32, NumEntities, "Number of entities currently on service");

//
NLMISC_VARIABLE(uint32, NumPlayers, "Number of players currently on service");

//
NLMISC_VARIABLE(bool, Verbose, "Allow display of verbose info");

//
NLMISC_VARIABLE(bool, CheckPlayerSpeed, "Allow checking player speed -- debug only!");


//
NLMISC_DYNVARIABLE(string, Watch0, "Display of entity 0")
{
	static NLMISC::CEntityId	id;
	if (get)
	{
		if (id != NLMISC::CEntityId::Unknown)
			*pointer = CWorldPositionManager::debugString(CWorldPositionManager::getEntityIndex(id));
	}
	else
	{
		id.fromString((*pointer).c_str());
	}
}

//
NLMISC_DYNVARIABLE(string, Watch1, "Display of entity 1")
{
	static NLMISC::CEntityId	id;
	if (get)
	{
		if (id != NLMISC::CEntityId::Unknown)
			*pointer = CWorldPositionManager::debugString(CWorldPositionManager::getEntityIndex(id));
	}
	else
	{
		id.fromString((*pointer).c_str());
	}
}
