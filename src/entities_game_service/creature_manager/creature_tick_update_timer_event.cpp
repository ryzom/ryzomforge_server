/** \file creature_tick_update_timer_event.cpp
 *
 * $Id: creature_tick_update_timer_event.cpp,v 1.5 2006/09/14 17:04:21 cado Exp $
 */


#include "stdpch.h"

//
// Includes
//

#include "creature_tick_update_timer_event.h"
#include "creature_manager/creature.h"

NL_INSTANCE_COUNTER_IMPL(CCreatureTickUpdateTimerEvent);

CCreatureTickUpdateTimerEvent:: CCreatureTickUpdateTimerEvent(CCreature *parent)
{
	_Parent = parent;
}

void CCreatureTickUpdateTimerEvent::timerCallback(CTimer* owner)
{
	H_AUTO(CCreatureTickUpdateTimerEvent);

	uint32 timeToNextTick= _Parent->tickUpdate();
	owner->setRemaining(timeToNextTick,this,1);
}
