/** \file combat_state.h
 *
 * $Id: combat_state.h,v 1.5 2004/03/01 19:21:52 lecroart Exp $
 */



#ifndef NL_COMBAT_STATE_H
#define NL_COMBAT_STATE_H

#include "nel/misc/types_nl.h"

namespace RYZOMCOMBATSTATE
{

	enum TCombatState
	{
		NotEngaged = 0,
		MovingTowardsTarget,
		TargetUnreachable,
		Engaged,
		TargetLost
	};

};	// RYZOMCOMBATSTATE

#endif //NL_COMBAT_STATE_H

/* End of combat_state.h */
