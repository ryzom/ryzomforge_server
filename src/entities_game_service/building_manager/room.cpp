/** \file room.cpp
 * <File description>
 *
 * $Id: room.cpp,v 1.7 2005/02/22 10:22:34 besson Exp $
 */



#include "stdpch.h"
#include "nel/misc/string_conversion.h"
#include "nel/net/service.h"

#include "room.h"
#include "mission_manager/ai_alias_translator.h"
#include "creature_manager/creature.h"
#include "creature_manager/creature_manager.h"
#include "player_manager/cdb.h"
#include "cdb_struct_banks.h"

using namespace std;
using namespace NLMISC;

namespace LIFT_DESTS
{
	NL_BEGIN_STRING_CONVERSION_TABLE (TDestType)
	NL_STRING_CONVERSION_TABLE_ENTRY (GuildMain)
	NL_STRING_CONVERSION_TABLE_ENTRY (GuildAnnex)
	NL_STRING_CONVERSION_TABLE_ENTRY (PlayerRoom)
	NL_STRING_CONVERSION_TABLE_ENTRY (CommonRoom)
	NL_STRING_CONVERSION_TABLE_ENTRY (Uninstanciated)
	NL_END_STRING_CONVERSION_TABLE(TDestType, LiftDestsConversion, Unknown)

	TDestType toDestType( const std::string & str )
	{
		return LiftDestsConversion.fromString( str );
	}	
}

namespace LIFT_RESTRICTION
{
	NL_BEGIN_STRING_CONVERSION_TABLE (TRestriction)
		NL_STRING_CONVERSION_TABLE_ENTRY (Rm_Fight)
		NL_STRING_CONVERSION_TABLE_ENTRY (Rm_Magic)
		NL_STRING_CONVERSION_TABLE_ENTRY (Rm_Harvest)
		NL_STRING_CONVERSION_TABLE_ENTRY (Rm_Craft)
	NL_END_STRING_CONVERSION_TABLE(TRestriction, RestConversion, Unknown)
		
	TRestriction toRestriction( const std::string & str )
	{
		return RestConversion.fromString( str );
	}	
}


void CRoom::init(CLiftDestination * destination,uint indexIndestination,CGuild * guild, const CEntityId & player)
{
	_Player = player;
	_IsValid = true;
	_Destination = destination;
	_IndexIndestination = indexIndestination;
	nlassert( _IndexIndestination < _Destination->InstanceCells.size() );
	if ( guild )
		_Guild = guild;

	// let's spawn the bots
	uint size = _Destination->Bots.size();
	_NPCs.reserve( size );
	for ( uint i = 0; i < size; i++ )
	{
		const CEntityId & eid = CAIAliasTranslator::getInstance()->getEntityId( _Destination->Bots[i] );
		if ( eid == CEntityId::Unknown )
		{
			nlwarning("CRoom::init -> Invalid bot alias %s in destination '%s'", CPrimitivesParser::aliasToString(_Destination->Bots[i]).c_str(), _Destination->Name.c_str() );
			continue;
		}
		CCreature * bot = CreatureManager.getCreature( eid );
		if ( bot == NULL )
		{
			nlwarning("CRoom::init -> Invalid bot id '%s'%s in destination '%s'", eid.toString().c_str(), CPrimitivesParser::aliasToString(_Destination->Bots[i]).c_str(), _Destination->Name.c_str() );
			continue;
		}

		//allocate a new creature
		static uint64 id64 = 0;
		NLMISC::CEntityId entityId(RYZOMID::npc, id64++, NLNET::IService::getInstance()->getServiceId(), NLNET::IService::getInstance()->getServiceId());
		CCreature * bot2 = bot->getCopy(  entityId, _Destination->InstanceCells[_IndexIndestination] );
		nlassert( bot2 );
		_NPCs.push_back( entityId );
	}
}// CRoom::init

void CRoom::release()
{
	_IsValid = false;
	_Guild = CGuild::InvalidGuildPtr;
	_Player = CEntityId::Unknown;
	for (uint i = 0; i < _NPCs.size(); i++)
	{
		Mirror.removeEntity( _NPCs[i] );
		CreatureManager.removeCreature(_NPCs[i]);
	}
}// CRoom::release

