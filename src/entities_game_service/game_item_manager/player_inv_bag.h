/** \file player_inv_bag.h
 * bag inventory
 * inventory and view
 * $Id: player_inv_bag.h,v 1.10 2007/03/09 09:56:48 boucher Exp $
 */


#ifndef PLAYER_INV_BAG_H
#define PLAYER_INV_BAG_H

#include "game_item_manager/game_item.h"
#include "game_item_manager/player_inventory.h"

/** Bag inventory */
class CBagInventory : public CInventoryBase
{
public:
	
	//@{
	//@name Overloads from inventory base
	/// Return the max bulk according to player capacity
	uint32 getMaxBulk() const;

	uint32 getMaxSlot() const;
};

/** View for the bag inventory */
class CBagInvView : public CCharacterInvView
{
public:
	virtual void onItemChanged(uint32 slot, INVENTORIES::TItemChangeFlags changeFlags);
	/// The inventory informations has changed (like total bulk or weight)
	virtual void onInventoryChanged(INVENTORIES::TInventoryChangeFlags changeFlags);
};

#endif
