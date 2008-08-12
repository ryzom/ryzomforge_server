/** \file player_inv_auto_resize.h
 * an auto resize inventory
 *
 * $Id: player_inv_auto_resize.h,v 1.3 2007/03/09 09:56:48 boucher Exp $
 */


#ifndef PLAYER_INV_AUTO_RESIZE_H
#define PLAYER_INV_AUTO_RESIZE_H

#include "game_item_manager/game_item.h"
#include "game_item_manager/player_inventory.h"

/** auto resize inventory */
class CAutoResizeInventory : public CInventoryBase
{
public:
	//@{
	//@name Overloads from inventory base
	/// Insert an item in the inventory, auto resize inventory if needed
	virtual TInventoryOpResult insertItem(CGameItemPtr &item, uint32 slot = INVENTORIES::INSERT_IN_FIRST_FREE_SLOT, bool autoStack = false);
	/// NEVER use this method. ONLY used when loading inventory from save files.
	/// It does ignore bulk and weight limitations.
	virtual void forceLoadItem(CGameItemPtr &item, uint32 slot);
	//@}
};

#endif // PLAYER_INV_AUTO_RESIZE_H
