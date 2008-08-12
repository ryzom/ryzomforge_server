/** \file character_tick_update_timer_event.h
 * 
 * $Id: character_tick_update_timer_event.h,v 1.6 2005/06/23 18:14:21 boucher Exp $
 */

#ifndef CHARACTER_TICK_UPDATE_TIMER_EVENT_H
#define CHARACTER_TICK_UPDATE_TIMER_EVENT_H

//
// Includes
//

#include "game_share/timer.h"

class CCharacter;

// ***************************************************************************
// different low frequency update
class CCharacterTickUpdateTimerEvent : public CTimerEvent
{
	NL_INSTANCE_COUNTER_DECL(CCharacterTickUpdateTimerEvent);
public:

	CCharacterTickUpdateTimerEvent(CCharacter *parent);
	void timerCallback(CTimer *owner);
private:
	CCharacter *_Parent;
};

// ***************************************************************************
// frequent update of the database
class CCharacterDbUpdateTimerEvent:public CTimerEvent
{
	NL_INSTANCE_COUNTER_DECL(CCharacterDbUpdateTimerEvent);
public:
	CCharacterDbUpdateTimerEvent(CCharacter *parent);
	void timerCallback(CTimer *owner);
private:
	CCharacter *_Parent;
};

// ***************************************************************************
// frequent update of the player HP/STA/SAP/FOCUS bars
class CCharacterBarUpdateTimerEvent : public CTimerEvent
{
	NL_INSTANCE_COUNTER_DECL(CCharacterBarUpdateTimerEvent);
public:
	CCharacterBarUpdateTimerEvent(CCharacter *parent);
	void timerCallback(CTimer *owner);
private:
	CCharacter *_Parent;
};

#endif
