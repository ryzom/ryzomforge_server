/** \file character_tick_update_timer_event.cpp
 *
 * $Id: character_tick_update_timer_event.cpp,v 1.5 2005/02/22 10:22:31 besson Exp $
 */


#include "stdpch.h"

//
// Includes
//

#include "character_tick_update_timer_event.h"
#include "player_manager/character.h"

NL_INSTANCE_COUNTER_IMPL(CCharacterTickUpdateTimerEvent);
NL_INSTANCE_COUNTER_IMPL(CCharacterDbUpdateTimerEvent);
NL_INSTANCE_COUNTER_IMPL(CCharacterBarUpdateTimerEvent);

// ***************************************************************************
CCharacterTickUpdateTimerEvent:: CCharacterTickUpdateTimerEvent(CCharacter *parent)
{
	_Parent = parent;
}

void CCharacterTickUpdateTimerEvent::timerCallback(CTimer* owner)
{
	H_AUTO(CCharacterTickUpdateTimerEvent);

	uint32 timeToNextTick= _Parent->tickUpdate();
	owner->setRemaining(timeToNextTick,this);
}

// ***************************************************************************
CCharacterDbUpdateTimerEvent:: CCharacterDbUpdateTimerEvent(CCharacter *parent)
{
	_Parent = parent;
}

void CCharacterDbUpdateTimerEvent::timerCallback(CTimer* owner)
{
	H_AUTO(CharacterDbUpdateTimerEvent);
	
	_Parent->databaseUpdate();
	owner->setRemaining(2,this);
}


// ***************************************************************************
CCharacterBarUpdateTimerEvent::CCharacterBarUpdateTimerEvent(CCharacter *parent)
{
	_Parent= parent;
}

void CCharacterBarUpdateTimerEvent::timerCallback(CTimer *owner)
{
	H_AUTO(CCharacterBarUpdateTimerEvent);

	_Parent->barUpdate();
	owner->setRemaining(2,this);
}

