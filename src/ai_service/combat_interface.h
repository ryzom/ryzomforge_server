/** \file combat_interface.h
 *
 * $Id: combat_interface.h,v 1.19 2004/04/28 20:01:40 boucher Exp $
 */


#ifndef RYAI_COMBAT_INTERFACE_H
#define RYAI_COMBAT_INTERFACE_H

// Nel Misc
#include "nel/misc/types_nl.h"

// Game share
#include "game_share/ryzom_entity_id.h"
#include "game_share/action_nature.h"
#include "nel/misc/sheet_id.h"

class	CAIEntityPhysical;
class	CModEntityPhysical;

// the class
class CCombatInterface
{
public:
	static void init();
	static void release();

	class CEvent
	{
	public:
		TDataSetRow					_originatorRow;
		TDataSetRow					_targetRow;
		float						_weight;
		ACTNATURE::TActionNature	_nature;
	};
	static std::list <CEvent> _events;
};

#endif
