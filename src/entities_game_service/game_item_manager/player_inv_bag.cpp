/** \file player_inv_bag.cpp
 * inventory specialisation for the players inventories
 *
 * $Id: player_inv_bag.cpp,v 1.13 2007/03/09 09:56:48 boucher Exp $
 */

#include "stdpch.h"

#include "player_inv_bag.h"

#include "game_share/slot_equipment.h"
#include "player_manager/character.h"


extern NLMISC::CVariable<uint32>	MaxPlayerBulk;


/////////////////////////////////////////////////////////////
// CBagInventory
/////////////////////////////////////////////////////////////

// ****************************************************************************
uint32 CBagInventory::getMaxBulk() const
{
	return MaxPlayerBulk;
}

// ****************************************************************************
uint32 CBagInventory::getMaxSlot() const
{
	return INVENTORIES::NbBagSlots;
}

// ****************************************************************************
void CBagInvView::onItemChanged(uint32 slot, INVENTORIES::TItemChangeFlags changeFlags)
{
	// Call the parent before the specific code
	CCharacterInvView::onItemChanged(slot, changeFlags);

	// itc_hp
	// Cf. CGameItem::removeHp and CGameItem::addHp
/*	if (_Form && !ITEMFAMILY::destroyedWhenWorned(_Form->Family) )
	{
		const CEntityId itemOwner = getOwnerPlayer();
		if (itemOwner != CEntityId::Unknown)
		{
			SM_STATIC_PARAMS_1(params, STRING_MANAGER::item);
			params[0].SheetId = _SheetId;
			PHRASE_UTILITIES::sendDynamicSystemMessage( TheDataset.getDataSetRow(itemOwner), ITEM_WORN_STATE::getMessageForState(ITEM_WORN_STATE::Worned), params);
		}
	}
*/

}

// ****************************************************************************
void CBagInvView::onInventoryChanged(INVENTORIES::TInventoryChangeFlags changeFlags)
{
}
