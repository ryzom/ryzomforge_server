/** \file solded_items.h
 * Singleton received solded items and keep it until character are online, when his online remove it 
 * from character selled item and give to him corresponding money
 *
 * $Id: solded_items.h,v 1.6 2005/06/23 18:14:21 boucher Exp $
 */

#ifndef RYZOM_SOLDED_ITEMS_H
#define RYZOM_SOLDED_ITEMS_H

// Misc
#include "nel/misc/entity_id.h"
//
#include "item_for_sale.h"

class CCharacter;

/**
 * CSoldedItems
 * Keep list of solded item when owner are offline
 * \author Alain Saffray
 * \author Nevrax France
 * \date 2003
 */
class CSoldedItems
{
	NL_INSTANCE_COUNTER_DECL(CSoldedItems);
public:

	// Start by declaring methods for persistent load/ save operations
	// The following macro is defined in persistent_data.h
	// At time of writing it evaluated to:
	//	void store(CPersistentDataRecord &pdr) const;
	//	void apply(CPersistentDataRecord &pdr);
	
//	DECLARE_PERSISTENCE_METHODS
		
	struct TSoldedItem
	{
		DECLARE_PERSISTENCE_METHODS
			
		TItemTradePtr Item;
		uint32 Quantity;
	};

	typedef std::vector< TSoldedItem > TMapElem;
	typedef std::map< NLMISC::CEntityId, TMapElem > TItemSolded;

	// get instance
	static CSoldedItems * getInstance();
	
	// an item are solded
	void soldedItem( TItemTradePtr item, uint32 quantity, CCharacter * character );

	// character log
	void characterLogon( CCharacter * character );

	// save
	void save() {}

private:
	// constructor
	CSoldedItems() {}
	
	static CSoldedItems *	_Instance;
	TItemSolded				_SoldedItem;
};

#endif // RYZOM_SOLDED_ITEMS_H

/* solded_items.h */
