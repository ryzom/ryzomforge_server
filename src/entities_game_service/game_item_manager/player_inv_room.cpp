/** \file player_inv_room.cpp
 * player room inventory
 *
 * $Id: player_inv_room.cpp,v 1.4 2007/03/09 09:56:49 boucher Exp $
 */

#include "stdpch.h"

#include "player_inv_room.h"

#include "player_manager/character.h"
#include "building_manager/building_manager.h"
#include "building_manager/room_instance.h"


/////////////////////////////////////////////////////////////
// CPlayerRoomInventory
/////////////////////////////////////////////////////////////

// ****************************************************************************
CPlayerRoomInventory::CPlayerRoomInventory(CCharacter * owner)
: _Owner(owner)
{
	nlassert(owner != NULL);
}

// ****************************************************************************
uint32 CPlayerRoomInventory::getMaxBulk() const
{
	return BasePlayerRoomBulk;
}

// ****************************************************************************
uint32 CPlayerRoomInventory::getMaxSlot() const
{
	return INVENTORIES::NbRoomSlots;
}

// ****************************************************************************
CInventoryBase::TInventoryOpResult CPlayerRoomInventory::insertItem(CGameItemPtr &item, uint32 slot, bool autoStack)
{
	/*if (!canUseInventory(_Owner))
		return ior_access_denied;*/

	return CInventoryBase::insertItem(item, slot, autoStack);
}

// ****************************************************************************
CGameItemPtr CPlayerRoomInventory::removeItem(uint32 slot, uint32 quantity, TInventoryOpResult * res)
{
	/*if (!canUseInventory(_Owner))
	{
		if (res != NULL)
			*res = ior_access_denied;
		return NULL;
	}*/

	return CInventoryBase::removeItem(slot, quantity, res);
}

// ****************************************************************************
/*bool CPlayerRoomInventory::canUseInventory(CCharacter * c) const
{
	nlassert(c != NULL);

	// for the moment only owner can use his room inventory
	if (c != _Owner)
		return false;

	// player must be in the room to access the inventory
	CMirrorPropValueRO<TYPE_CELL> mirrorCell(TheDataset, c->getEntityRowId(), DSPropertyCELL);
	const sint32 cell = mirrorCell;
	if ( !CBuildingManager::getInstance()->isRoomCell(cell) )
		return false;

	const CRoomInstancePlayer * room = dynamic_cast<CRoomInstancePlayer*>( CBuildingManager::getInstance()->getRoomInstanceFromCell(cell) );
	if (room == NULL)
		return false;

	if (room->getPlayer() != c->getId())
		return false;

	return true;
}*/

/////////////////////////////////////////////////////////////
// CPlayerRoomInvView
/////////////////////////////////////////////////////////////

// ****************************************************************************
void CPlayerRoomInvView::onInventoryChanged(INVENTORIES::TInventoryChangeFlags changeFlags)
{
}

