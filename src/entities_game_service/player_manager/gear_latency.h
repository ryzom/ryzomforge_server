/** \file gear_latency.h
 * <File description>
 *
 * $Id: gear_latency.h,v 1.6 2005/06/23 18:14:21 boucher Exp $
 */



#ifndef RY_GEAR_LATENCY_H
#define RY_GEAR_LATENCY_H

#include "nel/misc/bit_set.h"
#include "game_share/inventories.h"
#include "egs_sheets/egs_sheets.h"

class CCharacter;
/**
 * Class managing gear latency
 * When a player put an item on him, there is a time during which he can't use actions, use this item, dodge, shield, parry
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CGearLatency
{
	NL_INSTANCE_COUNTER_DECL(CGearLatency);
public:

	/// update latencies
	void update(CCharacter * user);

	/// set a slot as latent
	void setSlot( INVENTORIES::TInventory inventory, uint32 slot, const CStaticItem * form, CCharacter * user );

	/// unset a slot as latent
	void unsetSlot( INVENTORIES::TInventory inventory, uint32 slot, CCharacter * user);

	/// return true if the slot is latent
	inline bool isSlotLatent( INVENTORIES::TInventory inventory, uint32 slot ) const
	{

		bool inHand = false;
		if (inventory == INVENTORIES::handling)
			inHand = true;
		else
			nlassert(inventory == INVENTORIES::equipment);
			
		std::list<CGearSlot>::const_iterator it = _GearLatencies.begin();
		for (; it != _GearLatencies.end(); ++it)
		{
			if ( (*it).InHand == inHand && (*it).Slot == slot )
				return true;
		}
		return false;
	}

	/// return true if there are latent gears
	inline bool isLatent() const
	{
		return !_GearLatencies.empty();
	}

private:
	struct CGearSlot
	{
		/// date of the end of the latency
		NLMISC::TGameCycle	LatencyEndDate;
		/// true if the item is in hand (otherwise, on the body)
		bool				InHand;
		/// slot (position) of the item in the inventory
		uint32				Slot;
	};

	/// list of affected slots, sorted by increasing latency end dates
	std::list<CGearSlot>	_GearLatencies;	
};


#endif // RY_GEAR_LATENCY_H

/* End of gear_latency.h */


