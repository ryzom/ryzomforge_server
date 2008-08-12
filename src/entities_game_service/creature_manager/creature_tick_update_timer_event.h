/** \file creature_tick_update_timer_event.h
 * 
 * $Id: creature_tick_update_timer_event.h,v 1.4 2005/06/23 18:04:44 boucher Exp $
 */

#ifndef CREATURE_TICK_UPDATE_TIMER_EVENT_H
#define CREATURE_TICK_UPDATE_TIMER_EVENT_H

//
// Includes
//

#include "game_share/timer.h"

class CCreature;

class CCreatureTickUpdateTimerEvent:public CTimerEvent
{
	NL_INSTANCE_COUNTER_DECL(CCreatureTickUpdateTimerEvent);
public:

	CCreatureTickUpdateTimerEvent(CCreature *parent);
	void timerCallback(CTimer *owner);
private:
	CCreature *_Parent;
};

#endif
