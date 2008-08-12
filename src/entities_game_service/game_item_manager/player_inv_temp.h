/** \file player_inv_temp_h
 * temporary inventory for player
 *	inventory and view
 * $Id: player_inv_temp.h,v 1.16 2007/03/09 09:56:49 boucher Exp $
 */


#ifndef PLAYER_INV_TEMP_H
#define PLAYER_INV_TEMP_H

#include "game_share/temp_inventory_mode.h"

#include "game_item_manager/game_item.h"
#include "game_item_manager/player_inventory.h"

#include "nel/misc/sheet_id.h"

/**
 * CTempInventory
 *
 * \author Matthieu 'Trap' Besson
 * \author Nevrax France
 * \date February 2005
 */
class CTempInventory : public CInventoryBase
{
public:

	CTempInventory();

	uint32 getMaxSlot() const;

	virtual void bindView(CInventoryViewPtr inventoryView);

	// Inventory Mode

	TEMP_INV_MODE::TInventoryMode getMode() { return _Mode; }
	bool canEnterMode(TEMP_INV_MODE::TInventoryMode mode);
	bool enterMode(TEMP_INV_MODE::TInventoryMode mode);
	void leaveMode();

	// Display functionnalities : these methods do not affect the inventory structure
	// they just display things to the client throught the database
	// before using verify that the temp inventory is empty (else it may have some problem 
	// between displayed items and owned items)

	void enableTakeDisp(bool b);
	
	void clearDisp(uint32 slot);

	void setDispSheetId(uint32 slot, const NLMISC::CSheetId &sheet);
	NLMISC::CSheetId getDispSheetId(uint32 slot);

	void setDispQuality(uint32 slot, uint16 quality);
	uint16 getDispQuality(uint32 slot);

	void setDispQuantity(uint32 slot, uint16 quantity);
	uint16 getDispQuantity(uint32 slot);

protected:

	TEMP_INV_MODE::TInventoryMode _Mode;

	CCharacter *_Char;

};

/**
 * CTempInvView
 *
 * \author Matthieu 'Trap' Besson
 * \author Nevrax France
 * \date February 2005
 */
class CTempInvView : public CCharacterInvView
{
public:

	void init();

	virtual void onItemChanged(uint32 slot, INVENTORIES::TItemChangeFlags changeFlags);

	virtual void onInventoryChanged(INVENTORIES::TInventoryChangeFlags changeFlags);

	virtual void updateItemPrerequisit(uint32 slot) { /* TODO */ }

protected:

	virtual void updateClientSlot(uint32 clientSlot, const CGameItemPtr item);

	std::vector<uint8> _LastInfoVersion;
};

#endif
