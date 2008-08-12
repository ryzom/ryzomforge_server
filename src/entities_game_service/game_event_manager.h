/** \file game_event_manager.h
 * 
 *
 * $Id: game_event_manager.h,v 1.11 2006/07/12 14:37:31 boucher Exp $
 */



#ifndef EGS_GAME_EVENT_MANAGER_H
#define EGS_GAME_EVENT_MANAGER_H

// misc
#include "nel/misc/types_nl.h"
#include "nel/misc/singleton.h"
#include "nel/misc/common.h"
#include "nel/misc/time_nl.h"
#include "nel/misc/eid_translator.h"

#include "game_share/persistent_data.h"

#include "mission_manager/ai_alias_translator.h"

#include "dyn_chat_egs.h"

class CCharacter;

/**
 * CGameEventManager
 *
 * \author Matthieu 'Trap' Besson
 * \author Nevrax France
 * \date December 2004
 */
class CGameEventManager : public NLMISC::CSingleton<CGameEventManager>
{
public:
	CGameEventManager();

	// --------------------------
	// State Modification Methods
	// --------------------------
	
	// Read game event file
	void init();

	// No more than one GameEvent at a time
	void resetGameEvent(const std::string &sEventName, const std::string &sEventFaction1, const std::string &sEventFaction2, const std::string &sEventFaction1ChannelName, const std::string &sEventFaction2ChannelName, bool factionChanelInZoneOnly );

	// called when a new character is loaded
	void characterLoadedCallback(CCharacter *c);

	// add a new loged character to event channel s
	void addCharacterToChannelEvent( CCharacter *c );

	// add character to it's faction event channels
	void addCharacterToChannelFactionEvent( CCharacter *c, uint8 clan );
		
	// remove character to it's faction event channels
	void removeCharacterToChannelFactionEvent( CCharacter *c, uint8 clan );

	// --------------
	// Access Methods
	// --------------
	
	// Does an event is running ?
	bool isGameEventRunning() { return (_Date != 0); }

	// Get the date where the event started
	uint32 getStartingDate() { return _Date; }

	const std::string &getGameEventName() { return _Name; }

	bool isGameEventMission(TAIAlias missionAlias);

	TChanID getChannelEventId() const { return _ChannelEventId; }

	std::string	getFaction1() { return _EventFaction1Name; }
	std::string	getFaction2() { return _EventFaction2Name; }

	bool isFactionChanelInZoneOnly() { return _FactionChanelInZoneOnly;	}

	inline bool isInit() { return _InitOk; }

	DECLARE_PERSISTENCE_METHODS
		
private:
	void saveGameEventFile();

	void createEventChannel();
		
private:
	
	// The Singleton instance
	NLMISC::TGameCycle	_Date;

	std::string			_Name;
	std::string			_EventFaction1Name;
	std::string			_EventFaction2Name;
	std::string			_EventFaction1ChannelName;
	std::string			_EventFaction2ChannelName;
	
	TChanID				_ChannelEventId;
	TChanID				_ChannelEventFaction1Id;
	TChanID				_ChannelEventFaction2Id;
	TChanID				_ChannelGMEventFaction1Id;
	TChanID				_ChannelGMEventFaction2Id;

	bool				_FactionChanelInZoneOnly;

	bool				_InitOk;
};

#endif // EGS_GAME_EVENT_MANAGER_H

