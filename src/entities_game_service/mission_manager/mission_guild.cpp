/** \file mission_guild.cpp
 * <File description>
 *
 * $Id: mission_guild.cpp,v 1.12 2005/08/31 12:56:25 besson Exp $
 */

#include "stdpch.h"
#include "mission_manager/mission_guild.h"
#include "mission_manager/mission_manager.h"
#include "guild_manager/guild_manager.h"
#include "guild_manager/guild.h"
#include "primitives_parser.h"
#include "egs_mirror.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"
#include "player_manager/character.h"

NL_INSTANCE_COUNTER_IMPL(CMissionGuild);

//----------------------------------------------------------------------------
void CMissionGuild::updateUsersJournalEntry()
{
	/// todo guild mission
}

//----------------------------------------------------------------------------
void CMissionGuild::clearUsersJournalEntry()
{
	/// todo guild mission
}


//----------------------------------------------------------------------------
void CMissionGuild::setupEscort(const std::vector<TAIAlias> & aliases)
{
	nlwarning( "<MISSIONS> DONT KNOW HOW TO SETUP ESCORTS FOR GUILDS" );
}

//----------------------------------------------------------------------------
void CMissionGuild::getEntities(std::vector<TDataSetRow>& entities)
{
	CGuild * guild = CGuildManager::getInstance()->getGuildFromId( _GuildId );
	if ( guild )
	{
		for ( std::map<EGSPD::TCharacterId, EGSPD::CGuildMemberPD*>::const_iterator it = guild->getMembersBegin(); it != guild->getMembersEnd(); ++it )
		{
			TDataSetRow row = TheDataset.getDataSetRow( (*it).first );
			if ( TheDataset.isAccessible( row ) )
				entities.push_back( TheDataset.getDataSetRow( (*it).first ) );
		}
	}
	else
		nlwarning("<MISSIONS> Invalid guild %u", _GuildId);
}

//----------------------------------------------------------------------------
void CMissionGuild::stopChildren()
{
	CMissionTemplate * templ = CMissionManager::getInstance()->getTemplate( _Mission->getTemplateId() );
	nlassert(templ);
	for ( uint i = 0; i < templ->ChildrenMissions.size(); i++ )
	{
		const CMissionTemplate * child = CMissionManager::getInstance()->getTemplate( templ->ChildrenMissions[i] );
		if ( child )
		{
			for ( uint j = 0; j < child->Instances.size(); j++ )
			{
				CMissionGuild * mission = dynamic_cast<CMissionGuild*>( child->Instances[j] );
				if ( mission && mission->_GuildId == _GuildId )
					mission->onFailure( true,false );
			}
		}
		else
			nlwarning("<MISSIONS> : invalid child template %u",templ->ChildrenMissions[i] );
	}
}

//----------------------------------------------------------------------------
void CMissionGuild::onFailure(bool ignoreJumps, bool sendMessage)
{
	CMissionTemplate * templ = CMissionManager::getInstance()->getTemplate( _Mission->getTemplateId() );
	nlassert(templ);
	CMission::onFailure(ignoreJumps);
	sendMessage = ( sendMessage && !templ->Tags.NoList );
	if ( getProcessingState() == CMissionBaseBehaviour::Normal  )
	{
		CGuild * guild = CGuildManager::getInstance()->getGuildFromId( _GuildId );
		if ( guild )
		{
			if (sendMessage && !templ->Tags.NoList && !templ->Tags.AutoRemove)
				guild->sendMessageToGuildMembers("MISSION_FAILED");

			if ( templ->Tags.NoList || isChained() || templ->Tags.AutoRemove )
				guild->removeMission(this, mr_fail);
			else
				setFailureFlag();
		}
		return;
	}
	if ( _ProcessingState == CMissionBaseBehaviour::InJump )
	{
		_ProcessingState = Normal;
		return;
	}
	else if ( _ProcessingState == CMissionBaseBehaviour::Complete )
	{
		forceSuccess();
		return;
	}
}

//----------------------------------------------------------------------------
void CMissionGuild::forceSuccess()
{
	CMissionTemplate * templ = CMissionManager::getInstance()->getTemplate( _Mission->getTemplateId() );
	nlassert(templ);
	CGuild * guild = CGuildManager::getInstance()->getGuildFromId( _GuildId );
	if ( guild )
	{
		_ProcessingState = Normal;
		CMissionEventMissionDone  event(templ->Alias);

		guild->addSuccessfulMission(templ);
		if ( !templ->Tags.NoList && !templ->Tags.AutoRemove )
			guild->sendMessageToGuildMembers(isChained()?"EGS_MISSION_STEP_SUCCESS":"EGS_MISSION_SUCCESS");

		CMissionManager::getInstance()->missionDoneOnce(templ);
		stopChildren();
		guild->processMissionEvent( event );
		
		// only remove no list missions, other must be manually removed by user
		if ( templ->Tags.NoList || isChained() || templ->Tags.AutoRemove )
		{
			updateEncyclopedia();
			guild->removeMission(this, mr_success);
		}
		else
		{
			setSuccessFlag();
		}
	}
	else
		nlwarning("<MISSIONS> alias %s : invalid team", CPrimitivesParser::aliasToString(templ->Alias).c_str());
}

//----------------------------------------------------------------------------
CCharacter* CMissionGuild::getMainEntity()
{
	CGuild * guild = CGuildManager::getInstance()->getGuildFromId( _GuildId );
	if ( guild )
		return PlayerManager.getChar( guild->getHighestGradeOnlineUser() );
	nlwarning( "<MISSIONS> invalid guild id '%u' ",_GuildId );
	return NULL;
}
