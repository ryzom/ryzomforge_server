// Ryzom - MMORPG Framework <http://dev.ryzom.com/projects/ryzom/>
// Copyright (C) 2010  Winch Gate Property Limited
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "stdpch.h"

#include "pvp_faction.h"
#include "player_manager/character.h"
#include "pvp_manager/pvp_manager_2.h"
#include "zone_manager.h"
#include "phrase_manager/phrase_utilities_functions.h"
#include "stat_db.h"
#include "pvp_manager/pvp_faction_reward_manager/pvp_faction_reward_manager.h"
#include "pvp_manager/pvp_faction_hof.h"
#include "nel/misc/variable.h"

using namespace std;
using namespace	PHRASE_UTILITIES;

CVariable<bool> ResPawnPVPInSameRegionForbiden("egs","ResPawnPVPInSameRegionForbiden", "When character dead in PvP Faction, it can't respawn in same same region of it's death", true, 0, true );

//----------------------------------------------------------------------------
PVP_RELATION::TPVPRelation CPVPFaction::getPVPRelation( CCharacter * actor, CEntityBase * target, bool curative ) const
{
	// Init relation reminders
	CPVPManager2::getInstance()->setPVPFactionAllyReminder( false );
	CPVPManager2::getInstance()->setPVPFactionEnemyReminder( false );

	bool targetSafe = false;
	bool actorSafe = false;
	
	// Check actor and target validity
	if (actor == 0 || target == 0)
	{
		nlwarning("<CPVPFaction::getPVPRelation> actor: %p  target: %p", actor, target);
		return PVP_RELATION::Unknown;
	}

	CCharacter * pTarget = dynamic_cast<CCharacter*>(target);
	if (pTarget == 0)
		return PVP_RELATION::Unknown;
	
	if (CPVPManager2::getInstance()->inSafeZone(pTarget->getPosition()))
	{
		if (pTarget->getSafeInPvPSafeZone())
			targetSafe = true;
	}

	if( CPVPManager2::getInstance()->inSafeZone(actor->getPosition()))
	{
		if( actor->getSafeInPvPSafeZone())
			actorSafe = true;
	}
	if (actorSafe)
		nlinfo("Actor is safe");
	else
		nlinfo("Actor is UNsafe");
		
	if (targetSafe)
		nlinfo("Target is safe");
	else
		nlinfo("Target is UNsafe");
		
	// if target is not tagged then he's neutral
	if (!pTarget->getPVPFlag() && !pTarget->getPvPRecentActionFlag())
		return PVP_RELATION::Neutral;

	// if Actor is not tagged then he's neutral 
	if (!actor->getPVPFlag() && !actor->getPvPRecentActionFlag())
		return PVP_RELATION::Neutral;

	if ((targetSafe && !actorSafe) || (actorSafe && !targetSafe)) {
		nlinfo("NeutralPVP");
		return PVP_RELATION::NeutralPVP;
	}

	// Both are in Teams
	if ((pTarget->getTeamId() != CTEAM::InvalidTeamId) && (actor->getTeamId() != CTEAM::InvalidTeamId))
	{
		
		// In same Team
		if (actor->getTeamId() == pTarget->getTeamId())
		{
			nlinfo("Team Ally");
			CPVPManager2::getInstance()->setPVPFactionAllyReminder( true );
			return PVP_RELATION::Ally;
		}
		
		// In same League
		if ((pTarget->getLeagueId() != DYN_CHAT_INVALID_CHAN) && (actor->getLeagueId() != DYN_CHAT_INVALID_CHAN) && (actor->getLeagueId() == pTarget->getLeagueId()))
		{
			nlinfo("League Ally");
			CPVPManager2::getInstance()->setPVPFactionAllyReminder( true );
			return PVP_RELATION::Ally;
		}
		
		if (targetSafe || actorSafe) {
			nlinfo("NeutralPVP in safe zone");
			return PVP_RELATION::NeutralPVP;
		}
		
		nlinfo("InTeam ennemy");
		// Default is ennemies
		return PVP_RELATION::Ennemy;
		
	}

	// In same Guild and not in teams
	if ((pTarget->getGuildId() != 0) && (actor->getGuildId() != 0) && (actor->getGuildId() == pTarget->getGuildId()))
	{
		nlinfo("Guild Ally");
		CPVPManager2::getInstance()->setPVPFactionAllyReminder( true );
		return PVP_RELATION::Ally;
	}

	nlinfo("ok");
	
	// If both safe can heal
	if (targetSafe && actorSafe)
	{
		nlinfo("Neutral Safe");
//		CPVPManager2::getInstance()->setPVPFactionAllyReminder(true);
		return PVP_RELATION::Neutral;
	}
	
	// If not both safe, no heal, no attack
	if (targetSafe || actorSafe) {
		nlinfo("NeutralPVP Safe/Unsafe");
		return PVP_RELATION::NeutralPVP;
	}
	
	CPVPManager2::getInstance()->setPVPFactionEnemyReminder(true);
	CPVPManager2::getInstance()->setPVPFactionAllyReminder(true);
	nlinfo("Active PVP");
	return PVP_RELATION::Active;
}


//----------------------------------------------------------------------------
bool CPVPFaction::isTPValid( CCharacter* actor, CGameItemPtr TeleportTicket ) const
{
	bool result = ! actor->getPvPRecentActionFlag();
	if( TeleportTicket != 0 && TeleportTicket->getStaticForm() != 0 && result )
	{
		// if character have is not PvP faction flagged (Tag PvP off), only recent PvP action can forbid TP usage
		if( actor->getPVPFlag() == false )
			return true;

		// check if war occurs between player character allegiances and region destination clan owner  
		uint16 idx = CZoneManager::getInstance().getTpSpawnZoneIdByName( TeleportTicket->getStaticForm()->Destination );
		const CTpSpawnZone * zone = CZoneManager::getInstance().getTpSpawnZone( idx );
		if( zone != 0 )
		{
			PVP_CLAN::TPVPClan regionFactionOwner = CPVPFactionRewardManager::getInstance().getRegionOwner( zone->getRegion() );
			pair<PVP_CLAN::TPVPClan, PVP_CLAN::TPVPClan> actorAllegiance = actor->getAllegiance();

			if( regionFactionOwner == PVP_CLAN::Neutral )
				return true;
			else
			{
				if( CPVPManager2::getInstance()->factionWarOccurs(actorAllegiance.first, regionFactionOwner) == false 
				&& CPVPManager2::getInstance()->factionWarOccurs(actorAllegiance.second, regionFactionOwner) == false )
					return true;
			}
		}
	}
	return false;
}

//----------------------------------------------------------------------------
bool CPVPFaction::isRespawnValid( CCharacter* actor, CCharacterRespawnPoints::TRespawnPoint respawnPoint ) const
{
	if( actor->getPVPFlag() == false )
		return true;

	const CTpSpawnZone * zone = CZoneManager::getInstance().getTpSpawnZone(respawnPoint);
	if (zone == NULL)
		return false;

	// validate default respawn point
	if( zone->getPlaceType() == PLACE_TYPE::Capital || zone->getName() == "place_aegus" || zone->getName() == "place_stalli" || zone->getName() == "place_qai_lo" || zone->getName() == "place_aubermouth" )
		return true;

	// check if the respawn point is in the region where player character is killed in PvP
	if( ResPawnPVPInSameRegionForbiden )
		if ( (zone->getRegion() == actor->getKilledPvPRegion() ) && actor->getPvPRecentActionFlag() )
			return false;

	// check if respawn point is in enemy region
	PVP_CLAN::TPVPClan regionClan = CPVPFactionRewardManager::getInstance().getRegionOwner(zone->getRegion());
	pair< PVP_CLAN::TPVPClan, PVP_CLAN::TPVPClan > allegiance = actor->getAllegiance();

	if( regionClan != PVP_CLAN::Neutral )
	{
		if( CPVPManager2::getInstance()->factionWarOccurs( regionClan, allegiance.first ) || 
			CPVPManager2::getInstance()->factionWarOccurs( regionClan, allegiance.second ) )
			return false;
	}
	return true;
}

//----------------------------------------------------------------------------
void CPVPFaction::finalBlowerKillerInPvPFaction( CCharacter * killer, PVP_CLAN::TPVPClan finalBlowerFaction, CCharacter * victimChar ) const
{
	CPVPFactionHOF::getInstance()->writeStatInHOFDatabase( killer, finalBlowerFaction, CPVPFactionHOF::final_blow, 1 );

	BOMB_IF(victimChar == 0, "<CPVPFaction::finalBlowerKillerInPvPFaction> victimChar pointer is null !", return );

	SM_STATIC_PARAMS_1(fbMsgParam, STRING_MANAGER::player);
	fbMsgParam[0].setEId( victimChar->getId() );
	CCharacter::sendDynamicSystemMessage( killer->getId(), "CHARACTER_MADE_THE_FINAL_BLOW", fbMsgParam );
}

//----------------------------------------------------------------------------
void CPVPFaction::characterKillerInPvPFaction( CCharacter * character, PVP_CLAN::TPVPClan winnerFaction, sint32 factionPoint ) const
{
	CPVPFactionHOF::getInstance()->writeStatInHOFDatabase( character, winnerFaction, CPVPFactionHOF::faction_point, factionPoint );
	CPVPFactionHOF::getInstance()->writeStatInHOFDatabase( character, winnerFaction, CPVPFactionHOF::kill, 1 );
}

//----------------------------------------------------------------------------
void CPVPFaction::characterKilledInPvPFaction( CCharacter * character, PVP_CLAN::TPVPClan looserFaction, sint32 factionPoint ) const
{
	CPVPFactionHOF::getInstance()->writeStatInHOFDatabase( character, looserFaction, CPVPFactionHOF::faction_point, factionPoint );
	CPVPFactionHOF::getInstance()->writeStatInHOFDatabase( character, looserFaction, CPVPFactionHOF::lost, 1 );

	character->killedInPVP();
}

