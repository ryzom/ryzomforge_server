/** \file player_inv_auto_resize.cpp
 * 
 *
 * $Id: player_inv_auto_resize.cpp,v 1.3 2007/03/09 09:56:48 boucher Exp $
 */

#include "stdpch.h"

#include "player_inv_auto_resize.h"

// ****************************************************************************
CInventoryBase::TInventoryOpResult CAutoResizeInventory::insertItem(CGameItemPtr &item, uint32 slot, bool autoStack)
{
	if (slot == INVENTORIES::INSERT_IN_FIRST_FREE_SLOT)
	{
		if (getFreeSlotCount() == 0)
			setSlotCount(getSlotCount()+1);
	}
	else if (slot >= _Items.size())
	{
		setSlotCount(slot+1);
	}
	
	return CInventoryBase::insertItem(item,slot,autoStack);
}

// ****************************************************************************
void CAutoResizeInventory::forceLoadItem(CGameItemPtr &item, uint32 slot)
{
	if (slot == INVENTORIES::INSERT_IN_FIRST_FREE_SLOT)
	{
		if (getFreeSlotCount() == 0)
			setSlotCount(getSlotCount()+1);
	}
	else if (slot >= _Items.size())
	{
		setSlotCount(slot+1);
	}
	
	CInventoryBase::forceLoadItem(item,slot);
}
