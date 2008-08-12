/** \file player_inv_equip.h
 * ref inventory and view for player equipement
 *
 * $Id: player_inv_equip.h,v 1.12 2007/03/09 09:56:49 boucher Exp $
 */


#ifndef PLAYER_INV_EQUIP_H
#define PLAYER_INV_EQUIP_H

#include "game_item_manager/game_item.h"
#include "game_item_manager/player_inventory.h"

/** Equipment inventory (reference inventory) */
class CEquipInventory : public CRefInventory
{
public:
	//@{
	//@name Overloads from inventory base
	/// Return the max slot for equipment
	uint32 getMaxSlot() const;

	/// get total wear malus for equip inv
	float getWearMalus();
};

/** View for the equipement inventory */
class CEquipInvView : public CCharacterInvView
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
