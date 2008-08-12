/** \file character_game_event.h
 *
 * $Id: character_game_event.h,v 1.12 2005/06/23 18:14:21 boucher Exp $
 */

#ifndef EGS_CHARACTER_GAME_EVENT_H
#define EGS_CHARACTER_GAME_EVENT_H


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

// game share
#include "game_share/persistent_data.h"

//-----------------------------------------------------------------------------

class CCharacter;


/**
 * CCharacterGameEvent
 * contains code and data relative to the game event. The methods reset and 
 * subscribe are called from mission action.
 * \author Matthieu 'Trap' Besson
 * \author Nevrax France
 * \date December 2004
 */
class CCharacterGameEvent
{
	NL_INSTANCE_COUNTER_DECL(CCharacterGameEvent);
public:

	CCharacterGameEvent(CCharacter &c);

	DECLARE_PERSISTENCE_METHODS

	// --------------------------
	// State Modification Methods
	// --------------------------

	// set the game event
	void subscribe();

	// reset the game event (game event is finished)
	void reset();

	// called at each tick
	void tickUpdate();

	// --------------
	// Access Methods
	// --------------

	bool isInGameEvent() { return (_Date != 0); }
	
	NLMISC::TGameCycle getDate() { return _Date; }

	const std::string & getEventFaction() const { return _EventFaction; }
	void setEventFaction(const std::string & eventFaction);
	void clearEventFaction() { setEventFaction(""); }

	// register event faction in IOS
	void registerEventFaction();

	// create a session for character in the event faction channel and event faction info channel(read only)
	// NB : create chan first if they don't exist
	void setEventChannelSessions();

private:
	
	/// add a session in the channel for the char
	void addEventSession( const std::string& channel, bool writeRight, uint32 historicSize );
	
	/// remove char session from the channel
	void removeEventSession( const std::string& channel );
	
private:

	// The parent class
	CCharacter &_Char;

	// Date where the player began the event (default 0 no event participation)
	NLMISC::TGameCycle	_Date;

	// Event faction of player
	std::string			_EventFaction;
	std::string			_PreviousEventFaction;

	// True if event faction must be registered in IOS
	bool				_RegisterEventFaction;

};

#endif // EGS_CHARACTER_GAME_EVENT_H
