/** \file pvp_duel.cpp
 * 
 *
 * $Id: pvp_duel.cpp,v 1.15 2005/11/25 17:52:12 coutelas Exp $
 */


#include "stdpch.h"

#include "pvp_duel.h"
#include "player_manager/character.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"
#include "pvp_manager/pvp.h"
#include "pvp_manager/pvp_manager_2.h"


using namespace std;
using namespace NLMISC;
using namespace NLNET;


//----------------------------------------------------------------------------
PVP_RELATION::TPVPRelation CPVPDuel::getPVPRelation( CCharacter * user, CEntityBase * target, bool curative ) const
{
	if( !user || !target )
	{
		nlwarning("<CPVPDuel::getPVPRelation> user: %p  target: %p",user,target);
		return PVP_RELATION::Unknown;
	}

	if( target->getId().getType() != RYZOMID::player )
	{
		return PVP_RELATION::Unknown;
	}

	// people are enemies if they are in the same duel
	if ( user->getDuelOpponent() == target )
	{
		CPVPManager2::getInstance()->setPVPFactionEnemyReminder( false );
		return PVP_RELATION::Ennemy;
	}

	// if target is in duel then he's neutral pvp
	CCharacter * targetChar = static_cast<CCharacter*>(target);
	if( targetChar->getDuelOpponent() != NULL )
	{
		return PVP_RELATION::NeutralPVP;
	}

	return PVP_RELATION::Neutral;
}

//----------------------------------------------------------------------------
bool CPVPDuel::isTPValid( CCharacter* actor, CGameItemPtr TeleportTicket ) const
{
	if( actor->getPvPRecentActionFlag() )
		return false;
	return true;
}

