/** \file player_inv_room.h
 * player room inventory
 *
 * $Id: player_inv_room.h,v 1.2 2007/03/09 09:56:49 boucher Exp $
 */


#ifndef PLAYER_INV_ROOM_H
#define PLAYER_INV_ROOM_H

#include "game_item_manager/game_item.h"
#include "game_item_manager/player_inventory.h"

/** Player room inventory */
class CPlayerRoomInventory : public CInventoryBase
{
public:
	/// ctor
	CPlayerRoomInventory(CCharacter * owner);

	//@{
	//@name Overloads from inventory base
	virtual uint32 getMaxBulk() const;
	virtual uint32 getMaxSlot() const;

	virtual TInventoryOpResult insertItem(CGameItemPtr &item, uint32 slot = INVENTORIES::INSERT_IN_FIRST_FREE_SLOT, bool autoStack = false);
	virtual CGameItemPtr removeItem(uint32 slot, uint32 quantity = INVENTORIES::REMOVE_MAX_STACK_QUANTITY, TInventoryOpResult * res = NULL);
	//@}

	/// return true if the given character can use inventory
	//bool canUseInventory(CCharacter * c) const;

private:
	/// owner of the room
	CCharacter * const _Owner;
};

/** View for the player room inventory */
class CPlayerRoomInvView : public CCharacterInvView
{
public:
	/// The inventory informations has changed (like total bulk or weight)
	virtual void onInventoryChanged(INVENTORIES::TInventoryChangeFlags changeFlags);
};

#endif
