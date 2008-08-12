/** \file building_template.cpp
 * <File description>
 *
 * $Id: building_template.cpp,v 1.12 2005/02/22 10:22:34 besson Exp $
 */

#include "stdpch.h"
#include "building_template.h"
#include "nel/ligo/primitive.h"
#include "nel/misc/algo.h"
#include "mission_manager/mission_parser.h"



using namespace std;
using namespace NLMISC;
using namespace NLLIGO;

NL_INSTANCE_COUNTER_IMPL(CBuildingTemplate);

//----------------------------------------------------------------------------
bool CBuildingTemplate::build ( const NLLIGO::IPrimitive* prim, CBuildingParseData & parseData )
{
	bool ret = true;
	std::string name,value;
	nlverify( prim->getPropertyByName("name",name) );
	nlverify( prim->getPropertyByName("type",value) );

	Type = BUILDING_TYPES::fromString( value );
	if ( Type == BUILDING_TYPES::Unknown )
	{
		nlwarning("<BUILDING> invalid type '%s' in building template '%s'",value.c_str(),name.c_str() );
		return false;
	}

	// parse the children rooms
	for ( uint i = 0; i < prim->getNumChildren(); i++ )
	{
		const IPrimitive * child;
		if ( prim->getChild(child,i) && child )
		{
			CRoomTemplate room;
			if ( room.build( child,parseData ) )
				Rooms.push_back( room );
			else
				ret = false;
		}
	}
	if ( ret )
		parseData.BuildingTemplates.insert( make_pair(name,this ) );
	return ret;
}

//----------------------------------------------------------------------------
bool CRoomTemplate::build ( const NLLIGO::IPrimitive* prim, CBuildingParseData & parseData )
{
	bool ret = true;
	std::string value;
	nlverify( prim->getPropertyByName("name",Name) );

	// build restriction
	nlverify (prim->getPropertyByName("restriction",value ) );
	
	vector<string> retList;
	NLMISC::splitString( value,":",retList );
	for ( uint i = 0; i < retList.size(); i++ )
	{
		CMissionParser::removeBlanks( retList[i] );
		ROOM_RESTRICTION::TRestriction rest = ROOM_RESTRICTION::fromString( retList[i] );
		if ( rest == ROOM_RESTRICTION::Unknown )
		{
			nlwarning("<BUILDING> : invalid restriction '%s' in room '%s'",retList[i].c_str(), Name.c_str() );
			ret = false;
		}
		else
			Restrictions.push_back( rest );
	}

	// build bots
	vector<string> * botNames;
	nlverify (prim->getPropertyByName("bots",botNames ) && botNames );
	Bots.reserve( botNames->size() );
	for ( uint i = 0; i <botNames->size(); i++ )
	{
		vector<TAIAlias> aliases;
		CAIAliasTranslator::getInstance()->getNPCAliasesFromName( (*botNames)[i] , aliases );
		if ( aliases.empty() )
		{
			nlwarning("<BUILDING> : invalid bot '%s' in room '%s'",(*botNames)[i].c_str(), Name.c_str() );
			ret = false;
		}
		else
			Bots.push_back( aliases[0] );
	}

	// build icon
	nlverify( prim->getPropertyByName("icon",value) );
	Icon = LIFT_ICONS::toLiftIcon( value );
	if ( Icon == LIFT_ICONS::Unknown )
	{
		nlwarning("<BUILDING> : invalid icon '%s' in destination '%s'",value.c_str(), Name.c_str() );
		ret = false;
	}
	nlverify( prim->getPropertyByName("place_name",PhraseId));
	return ret;
}
