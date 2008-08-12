/** \file player_inv_pet.h
 * inventory and view for pet inventories
 *
 * $Id: player_inv_pet.h,v 1.11 2007/03/09 09:56:49 boucher Exp $
 */


#ifndef PLAYER_INV_PET_H
#define PLAYER_INV_PET_H

#include "game_item_manager/game_item.h"
#include "game_item_manager/player_inventory.h"

/** Mektoub Packer inventory */
class CPetInventory : public CInventoryBase
{
public:

	CPetInventory();

	void initPetInventory(uint32 petIndex, uint32 petMaxWeight, uint32 petMaxBulk);

	//@{
	//@name Overloads from inventory base
	/// Return the max bulk according to player capacity
	uint32 getMaxWeight() const;
	uint32 getMaxBulk() const;
	uint32 getMaxSlot() const;
	
	/// Update database of item representation
//	virtual void onItemChanged(uint32 slot);
	/// Update database of inventory representation
//	virtual void onInventoryChanged();
	//@}

private:
	uint32	_PetIndex;
	uint32	_PetMaxWeight;
	uint32	_PetMaxBulk;
};

/** View for the mektoub inventory */
class CPetInvView : public CCharacterInvView
{
public:
	virtual void onItemChanged(uint32 slot, INVENTORIES::TItemChangeFlags changeFlags);
	/// The inventory informations has changed (like total bulk or weight)
	virtual void onInventoryChanged(INVENTORIES::TInventoryChangeFlags changeFlags);
};

#endif
