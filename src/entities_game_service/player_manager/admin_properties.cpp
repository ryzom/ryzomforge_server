/** \file admin_properties.cpp
 * <File description>
 *
 * $Id: admin_properties.cpp,v 1.7 2007/01/03 15:53:44 boucher Exp $
 */


#include "stdpch.h"
#include "player_manager/admin_properties.h"
#include "mission_manager/mission_manager.h"
#include "player_manager/character.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"
#include "team_manager/team_manager.h"

using namespace std;
using namespace NLMISC;

NL_INSTANCE_COUNTER_IMPL(CAdminProperties);

void CAdminProperties::updateCSRJournal( CCharacter * user, CMission * mission,uint8 idx )
{
	if ( !mission )
	{
//		user->_PropertyDatabase.setProp( NLMISC::toString( "MISSIONS:%u:TYPE",idx), 0);
		CBankAccessor_PLR::getMISSIONS().getArray(idx).setTYPE(user->_PropertyDatabase, 0 );
//		user->_PropertyDatabase.setProp( NLMISC::toString( "MISSIONS:%u:ICON",idx), 0);
		CBankAccessor_PLR::getMISSIONS().getArray(idx).setICON(user->_PropertyDatabase, CSheetId::Unknown );
//		user->_PropertyDatabase.setProp( NLMISC::toString( "MISSIONS:%u:TITLE",idx), 0);
		CBankAccessor_PLR::getMISSIONS().getArray(idx).setTITLE(user->_PropertyDatabase, 0 );
//		user->_PropertyDatabase.setProp( NLMISC::toString( "MISSIONS:%u:DETAIL_TEXT",idx), 0);
		CBankAccessor_PLR::getMISSIONS().getArray(idx).setDETAIL_TEXT(user->_PropertyDatabase, 0 );
//		user->_PropertyDatabase.setProp( NLMISC::toString( "MISSIONS:%u:END_DATE",idx), 0 );
		CBankAccessor_PLR::getMISSIONS().getArray(idx).setEND_DATE(user->_PropertyDatabase, 0 );
//		user->_PropertyDatabase.setProp( NLMISC::toString( "MISSIONS:%u:BEGIN_DATE",idx), 0 );
		CBankAccessor_PLR::getMISSIONS().getArray(idx).setBEGIN_DATE(user->_PropertyDatabase, 0 );
		for (uint i = 0; i < NB_JOURNAL_COORDS; i++)
		{
//			user->_PropertyDatabase.setProp( NLMISC::toString( "MISSIONS:%u:TARGET%u:TITLE",idx,i), 0);
			CBankAccessor_PLR::getMISSIONS().getArray(idx).getTARGET(i).setTITLE(user->_PropertyDatabase, 0 );
//			user->_PropertyDatabase.setProp( NLMISC::toString( "MISSIONS:%u:TARGET%u:X",idx,i), 0);
			CBankAccessor_PLR::getMISSIONS().getArray(idx).getTARGET(i).setX(user->_PropertyDatabase, 0 );
//			user->_PropertyDatabase.setProp( NLMISC::toString( "MISSIONS:%u:TARGET%u:Y",idx,i), 0);
			CBankAccessor_PLR::getMISSIONS().getArray(idx).getTARGET(i).setY(user->_PropertyDatabase, 0 );
		}
		for (uint i = 0; i < NB_STEP_PER_MISSION; i++)
		{
//			user->_PropertyDatabase.setProp( NLMISC::toString( "MISSIONS:%u:GOALS:%u:TEXT",idx,i), 0);
			CBankAccessor_PLR::getMISSIONS().getArray(idx).getGOALS().getArray(i).setTEXT(user->_PropertyDatabase, 0 );
		}
	}
	else
	{
		// todo mission
		/*
		CMissionTemplate * templ = CMissionManager::getInstance()->getTemplate( mission->getTemplateId() );
		nlassert( templ );
		user->_PropertyDatabase.setProp( NLMISC::toString( "MISSIONS:%u:TYPE",idx), templ->Type);
		user->_PropertyDatabase.setProp( NLMISC::toString( "MISSIONS:%u:ICON",idx),templ->Icon );
		TDataSetRow giverRow = TheDataset.getDataSetRow( CAIAliasTranslator::getInstance()->getEntityId( mission->getGiver() ) );
		user->_PropertyDatabase.setProp( NLMISC::toString( "MISSIONS:%u:TITLE",idx),templ->sendTitleText( user->getEntityRowId(),giverRow ) );
		user->_PropertyDatabase.setProp( NLMISC::toString( "MISSIONS:%u:DETAIL_TEXT",idx),mission->sendDesc( user->getEntityRowId() ) );
		user->_PropertyDatabase.setProp( NLMISC::toString( "MISSIONS:%u:END_DATE",idx),mission->getEndDate() );
		user->_PropertyDatabase.setProp( NLMISC::toString( "MISSIONS:%u:BEGIN_DATE",idx), mission->getBeginDate() );
		mission->fillObjectives( user, idx );
		*/
	}
	///TODO NICO test no list
}

CMission * CAdminProperties::getMission( uint indexInJournal ) const
{
	/// todo mission
	/*
	if ( !_Data ) return NULL;
	CCharacter * user = PlayerManager.getChar( _Data->MissionUser );
	if ( !user )
		return NULL;
	
	CMission * mission = NULL;
	if ( indexInJournal < user->getMissions().size() )
		return (CMission*) user->getMissions()[indexInJournal];

	indexInJournal-= MaxSoloMissionCount;
	CTeam * team = TeamManager.getTeam( user->getTeamId() );
	if (team )
	{
		if ( indexInJournal < team->getMissions().size() )
			return (CMission*) team->getMissions()[indexInJournal];
	}		
	indexInJournal-= ( MaxGroupMissionCount);
	CGuild * guild = user->getGuild();
	if (guild )
	{
		if ( indexInJournal < guild->getMissions().size() )
			return(CMission*) guild->getMissions()[indexInJournal];
	}
	*/
	return NULL;
}
