/** \file ai_aiming_type.h
 * definition of the different aiming types used by ai
 *
 * $Id: ai_aiming_type.h,v 1.3 2005/02/22 10:25:13 besson Exp $
 */



#ifndef RY_AI_AIMING_TYPE_H
#define RY_AI_AIMING_TYPE_H

#include "nel/misc/types_nl.h"
#include "game_share/slot_equipment.h"

namespace AI_AIMING_TYPE
{
	enum TAiAimingType
	{
		Random = 0,
		Head,
		Chest,
		Arms,
		Hands,
		Legs,
		Feet,
		
		LeastProtected,
		AveragestProtected,
		MostProtected,
		
		Unknown,
	};

	/// convert a flag to a string
	const std::string &toString(TAiAimingType type);

	/// convert a string to a flag
	TAiAimingType toAimingType( const std::string &str);

	/// convert a slot to a combat flag
	SLOT_EQUIPMENT::TSlotEquipment toSlot(TAiAimingType type);

}; // AI_AIMING_TYPE

#endif // RY_AI_AIMING_TYPE_H
/* End of ai_aiming_type.h */
