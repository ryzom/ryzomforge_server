/** \file building_commands.cpp
 * 
 *
 * $Id: building_commands.cpp,v 1.18 2005/09/20 16:51:06 guignot Exp $
 */



#include "stdpch.h"
#include "guild_manager/fame_manager.h"
#include "egs_mirror.h"
#include "nel/net/unified_network.h"
#include "nel/net/service.h"
#include "player_manager/character.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"
#include "building_manager/building_manager.h"
#include "zone_manager.h"
#include "primitives_parser.h"
#include "creature_manager/creature_manager.h"
#include "creature_manager/creature.h"
#include "pvp_manager/pvp_manager.h"
#include "guild_manager/guild_manager.h"
#include "building_manager/building_physical.h"


using namespace std;
using namespace NLMISC;
using namespace NLNET;


NLMISC_COMMAND(simGpmsTriggerIn,"simulate the buying of a guild building","<userId><lift id>")
{
	if ( args.size() != 2 )
		return false;
	CEntityId id;
	id.fromString( args[0].c_str() );
	TDataSetRow rowId = TheDataset.getDataSetRow( id );
	uint32 liftId = atoi( args[1].c_str() );
	CBuildingManager::getInstance()->addTriggerRequest( rowId, (uint32)liftId );
	return true;
}

NLMISC_COMMAND(simGpmsTriggerOut,"simulate the buying of a guild building","<userId>")
{
	if ( args.size() != 1 )
		return false;
	CEntityId id;
	id.fromString( args[0].c_str() );
	TDataSetRow rowId = TheDataset.getDataSetRow( id );
	CBuildingManager::getInstance()->removeTriggerRequest( rowId );
	return true;
}

/*NLMISC_COMMAND(resetBuildings,"Reload lift/building data. WARNING : debug use only ( wipes lift dynamic data )","")
{
	if ( args.size() != 0 )
		return false;

	
	CPVPManager::release();
	CGuildManager::release();
	CBuildingManager::release();
	CZoneManager::release();
	CPrimitivesParser::release();

	CPVPManager::init();
	CPrimitivesParser::init();
	CZoneManager::init();
	CBuildingManager::init();
	CGuildManager::init();

	log.displayNL("lift data reloaded");
	return true;
}*/

NLMISC_COMMAND(dumpBuilding, "dump building infos", "<building_name = building_instance_galemus_trainer/building_instance_kaemon_trainer/... | building_alias>")
{
	if (args.size() != 1)
		return false;

	IBuildingPhysical * building = NULL;

	const string & buildingId = args[0];
	if (buildingId.size() > 0 && isdigit(buildingId[0]))
	{
		TAIAlias alias = atoi(buildingId.c_str());
		building = CBuildingManager::getInstance()->getBuildingPhysicalsByAlias(alias);
	}
	else
	{
		building = CBuildingManager::getInstance()->getBuildingPhysicalsByName(buildingId);
	}

	if (building)
		building->dumpBuilding( log );

	return true;
}

NLMISC_COMMAND(removeGuildBuilding, "(DEBUG) remove guild building", "<guild id>")
{
	if (args.size() != 1)
		return false;

	CBuildingManager::getInstance()->removeGuildBuilding( atoi(args[0].c_str()) );

	return true;
}

NLMISC_COMMAND(removePlayerBuilding, "(DEBUG) remove player building", "<eid>")
{
	if (args.size() != 1)
		return false;

	CEntityId eid(args[0]);
	if (eid == CEntityId::Unknown)
	{
		log.displayNL("unknown entity id!");
		return true;
	}

	CBuildingManager::getInstance()->removePlayerBuilding(eid);

	return true;
}
