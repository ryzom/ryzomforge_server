
/** \file shard_unifier_client.h
 *	Interface for EGS to trigger message to SU.
 *
 * $Id: shard_unifier_client.h,v 1.6 2006/10/31 16:09:06 blanchard Exp $
 */

#ifndef SHARD_UNIFIER_CLIENT_H
#define SHARD_UNIFIER_CLIENT_H


#include "nel/misc/types_nl.h"
#include "nel/misc/entity_id.h"
#include "game_share/character_sync_itf.h"
#include "game_share/pvp_clan.h"

class CCreateCharMsg;

class IShardUnifierEvent
{
public:

	static IShardUnifierEvent *getInstance();
	
	// interface for character synchronization
	virtual bool isEidTranslatorInitilazed		() =0;
	virtual void onNewChar						(const CHARSYNC::TCharInfo &charInfo) = 0;
	virtual void onDeleteChar					(uint32 charId) =0;
	virtual void onUpdateCharGuild				(const NLMISC::CEntityId &eid, uint32 guildId) = 0;
	virtual void onUpdateCharNewbieFlag			(const NLMISC::CEntityId &eid, bool newbie) = 0;
	virtual void onUpdateCharBestCombatLevel	(const NLMISC::CEntityId &eid, uint32 bestCombatLevel) = 0;
	virtual void onUpdateCharAllegiance			(const NLMISC::CEntityId &eid, PVP_CLAN::TPVPClan cult, PVP_CLAN::TPVPClan civ) = 0;
	virtual void onUpdateCharHomeMainland		(const NLMISC::CEntityId &eid, TSessionId homeMainland) = 0;
	virtual void onUpdateCharRespawnPoints		(const NLMISC::CEntityId &eid, const CONTINENT::TRespawnPointCounters &respawnPoints) = 0;
	virtual void onUpdateCharacters				(uint32 userId, const std::vector<CHARSYNC::TCharInfo> &charInfos) = 0;

	// interface for name unifier (player part)
	virtual void validateCharacterNameBeforeCreate	(uint32 userId, uint8 charIndex, const ucstring &name, uint32 homeSessionId) =0;
	virtual bool validateCharacterCreation			(uint32 userId, uint8 charIndex, const CCreateCharMsg &createCharMsg) =0;
	virtual void renameCharacter					(const NLMISC::CEntityId &eid) =0;

	// interface for name unifier (guild part)
	virtual void validateGuildName				(uint32 guildId, const ucstring &guildName) =0;
	virtual void registerLoadedGuildNames		(const std::vector<CHARSYNC::CGuildInfo> &guildInfos) =0;
	virtual void addGuild						(uint32 guildId, const ucstring &guildName) =0;
	virtual void removeGuild					(uint32 guildId) =0;

	// interface for player and char status
	virtual void playerConnected		(uint32 playerId) =0;
	virtual void playerDisconnected		(uint32 playerId) =0;
	virtual void charConnected			(const NLMISC::CEntityId &charId, uint32 lastDisconnectionDate) =0;
	virtual void charDisconnected		(const NLMISC::CEntityId &charId) =0;
	
	// interface for entity locator
	virtual bool isCharacterOnlineAbroad(const NLMISC::CEntityId &charEid) const =0;
	virtual const std::set<NLMISC::CEntityId> &getSpecialEntityOnlineAbroad(const std::string &privilege) const = 0;


	// utility
	static std::pair<CHARSYNC::TCult, CHARSYNC::TCivilisation> convertAllegiance(std::pair<PVP_CLAN::TPVPClan, PVP_CLAN::TPVPClan> allegiance);

};


#endif //SHARD_UNIFIER_CLIENT_H
