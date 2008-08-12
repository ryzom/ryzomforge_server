/** \file pvp_faction.h
 * 
 *
 * $Id: pvp_faction.h,v 1.6 2005/11/25 17:52:12 coutelas Exp $
 */



#ifndef RY_PVP_FACTION_H
#define RY_PVP_FACTION_H

#include "pvp_interface.h"

#include "game_share/pvp_clan.h"
#include "game_share/pvp_relation.h"

/**
 * PvP Faction
 * \author Alain Saffray
 * \author Nevrax France
 * \date 2005
 */
class CPVPFaction : public IPVPInterface
{
public:
	CPVPFaction() { }

	///\name PVP MODE FEATURES DEPENDANTS
	//@{
	/// return pvp relation between the two players
	PVP_RELATION::TPVPRelation getPVPRelation( CCharacter * actor, CEntityBase * target, bool curative = false ) const;
	/*
	/// return true if actor can use a curative action on target
	bool isCurativeActionValid( CCharacter* actor, CEntityBase * target, bool checkMode = false ) const;
	/// return true if actor can use an offensive action on target
	bool isOffensiveActionValid( CCharacter* actor, CEntityBase * target, bool checkMode = false ) const;
	/// returns true if owner area effect can be applied on areaTarget
	bool canApplyAreaEffect(CCharacter* actor, CEntityBase * areaTarget, bool offensive, bool ignoreMainTarget) const;
	*/
	/// return true if actor can use gived teleport point
	bool isTPValid( CCharacter* actor, CGameItemPtr TeleportTicket ) const;
	/// return true is respawn point is valid (use the same continent than character)
	bool isRespawnValid( CCharacter* actor, CCharacterRespawnPoints::TRespawnPoint respawnPoint ) const;
	/// final blower killer in pvp faction
	void finalBlowerKillerInPvPFaction( CCharacter * killer, PVP_CLAN::TPVPClan finalBlowerFaction, CCharacter * victimChar ) const;
	/// killer in PvP faction
	void characterKillerInPvPFaction( CCharacter * character, PVP_CLAN::TPVPClan winnerFaction, sint32 factionPoint ) const;
	/// killed character in PvP faction
	void characterKilledInPvPFaction( CCharacter * character, PVP_CLAN::TPVPClan looserFaction, sint32 factionPoint ) const;
	//@}

private:
};

#endif // RY_PVP_FACTION_H

