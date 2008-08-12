/** \file player_inv_pet.cpp
 * inventory specialisation for the players inventories
 *
 * $Id: player_inv_pet.cpp,v 1.7 2007/03/09 09:56:49 boucher Exp $
 */

#include "stdpch.h"

#include "player_inv_pet.h"

#include "game_share/slot_equipment.h"
#include "player_manager/character.h"



/////////////////////////////////////////////////////////////
// CMektoubInventory
/////////////////////////////////////////////////////////////

CPetInventory::CPetInventory()
{
	// the bulk and weight are known after ticket loading, so remove limitations at loading
	_PetMaxWeight = 0xFFFFFFFF;
	_PetMaxBulk = 0xFFFFFFFF;

	_PetIndex = ~0;
}


void CPetInventory::initPetInventory(uint32 petIndex, uint32 petMaxWeight, uint32 petMaxBulk)
{
	_PetMaxWeight = petMaxWeight;
	_PetMaxBulk = petMaxBulk;
	_PetIndex = petIndex;
}


uint32 CPetInventory::getMaxWeight() const
{
	return _PetMaxWeight;
}

uint32 CPetInventory::getMaxBulk() const
{
	return _PetMaxBulk;
}

uint32 CPetInventory::getMaxSlot() const
{
	return INVENTORIES::NbPackerSlots;
}

//void CPetInventory::onItemChanged(uint32 slot)
//{
//	// update mek inventory
//	nlassert(false);
//}
//
//void CPetInventory::onInventoryChanged()
//{
//	nlassert(false);
//}


//-----------------------------------------------
//	onItemChanged
//
//-----------------------------------------------
void CPetInvView::onItemChanged(uint32 slot, INVENTORIES::TItemChangeFlags changeFlags)
{
	// Call the parent before the specific code
	CCharacterInvView::onItemChanged(slot, changeFlags);

} // onItemChanged




void CPetInvView::onInventoryChanged(INVENTORIES::TInventoryChangeFlags changeFlags)
{
	
}



