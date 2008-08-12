/** \file pvp_duel.h
 * 
 *
 * $Id: pvp_duel.h,v 1.10 2005/11/25 17:52:12 coutelas Exp $
 */



#ifndef RY_PVP_DUEL_H
#define RY_PVP_DUEL_H


#include "pvp_interface.h"

#include "game_share/pvp_clan.h"
#include "game_share/pvp_relation.h"

/**
 * A Duel between 2 players
 * \author Stephane coutelas
 * \author Nevrax France
 * \date 2005
 */
class CPVPDuel : public IPVPInterface
{
public:
	/// return pvp relation between the two players
	PVP_RELATION::TPVPRelation getPVPRelation( CCharacter * actor, CEntityBase * target, bool curative = false ) const;
	
	///\name PVP MODE FEATURES DEPENDANTS
	//@{
	/// return true if actor can use gived teleport point
	bool isTPValid( CCharacter* actor, CGameItemPtr TeleportTicket ) const;
	/// return true is respawn point is valid (use the same continent than character)
	bool isRespawnValid( CCharacter* actor, CCharacterRespawnPoints::TRespawnPoint respawnPoint ) const { return true; }
	/// final blower killer in pvp faction
	void finalBlowerKillerInPvPFaction( CCharacter * killer, PVP_CLAN::TPVPClan finalBlowerFaction, CCharacter * victimChar ) const {}
	/// killer in PvP faction
	void characterKillerInPvPFaction( CCharacter * character, PVP_CLAN::TPVPClan winnerFaction, sint32 factionPoint ) const {}
	/// killed character in PvP faction
	void characterKilledInPvPFaction( CCharacter * character, PVP_CLAN::TPVPClan looserFaction, sint32 factionPoint ) const {}
	//@}

};

#endif // RY_PVP_DUEL_H

