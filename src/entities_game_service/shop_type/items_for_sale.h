/** \file items_for_sale.h
 * Manage items selled by player character with shop store system
 *
 * $Id: items_for_sale.h,v 1.15 2005/06/23 18:14:21 boucher Exp $
 */

#ifndef RY_ITEMS_FOR_SALE_H
#define RY_ITEMS_FOR_SALE_H

#include <vector>

#include "game_share/persistent_data.h"
#include "game_share/continent.h"

#include "item_for_sale.h"

class CCharacter;

class CItemsForSale
{
	NL_INSTANCE_COUNTER_DECL(CItemsForSale);
public:

	// Start by declaring methods for persistent load/ save operations
	// The following macro is defined in persistent_data.h
	// At time of writing it evaluated to:
	//	void store(CPersistentDataRecord &pdr) const;
	//	void apply(CPersistentDataRecord &pdr);
	
	DECLARE_PERSISTENCE_METHODS
		
	// constructor
	CItemsForSale() { _Character = 0; _NextIdentifier = 0; }

	// set owner character
	void setOwnerCharacter( CCharacter * c ) { nlassert(c != 0); _Character = c ; }

	// add an item in dynamic item list for sell it in shop store
	bool addItemForSale( uint32 price, uint32 retirePrice, CGameItemPtr item, uint32 quantity );

	// remove an item (removed by character or selled to another or selling delai reached)
	NLMISC::CSmartPtr< IItemTrade > removeItem( uint32 identifier, uint32 quantity, bool sellOffline );

	// get const reference on content
	const std::vector< TItemTradePtr >& getContent() const { return _ItemsForSale; }

	// serial
	void serial(NLMISC::IStream &f) throw(NLMISC::EStream );

	// check coherency between CDynamicItems and CItemsForSale of character, assume CItemsForSale is a reference
	void checkSellStore( NLMISC::CEntityId charId );

	// return nb item in shop store
	uint32 getNbItemInShopStore() const { return _ItemsForSale.size(); }

	// returns the number of items for sale on the given continent
	uint32 getNbItemsForSaleOnContinent(CONTINENT::TContinent continent) const;

	// remove items for sale on the given continent and get them
	std::vector<TItemTradePtr> removeItemsOnContinent(CONTINENT::TContinent continent);

private:
	CCharacter *					_Character;
	std::vector< TItemTradePtr >	_ItemsForSale;
	uint32							_NextIdentifier;
};

#endif
