/** \file player_inv_hand.h
 * ref inventory and view for the hands of the player
 *
 * $Id: player_inv_hand.h,v 1.12 2007/03/09 09:56:49 boucher Exp $
 */


#ifndef PLAYER_INV_HAND_H
#define PLAYER_INV_HAND_H

#include "game_item_manager/game_item.h"
#include "game_item_manager/player_inventory.h"

/** Handling inventory (reference inventory) */
class CHandlingInventory : public CRefInventory
{
public:
	//@{
	//@name Overloads from inventory base
	/// Return the max slot for equipment
	uint32 getMaxSlot() const;

	float getWearMalus();

	/// Update database of item representation
//	virtual void onItemChanged(uint32 slot);
	/// Update database of inventory representation
//	virtual void onInventoryChanged();
	//@}

};

/** View for the handling inventory */
class CHandlingInvView : public CCharacterInvView
{
public:
	virtual void onItemChanged(uint32 slot, INVENTORIES::TItemChangeFlags changeFlags);
	/// The inventory informations has changed (like total bulk or weight)
	virtual void onInventoryChanged(INVENTORIES::TInventoryChangeFlags changeFlags);

protected:
	/** Update the given slot on the client with item infos.
	 *  If item is NULL, slot is updated as empty on the client.
	 */
	virtual void updateClientSlot(uint32 clientSlot, const CGameItemPtr item);
};

#endif
