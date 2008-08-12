/** \file dynamic_items.h
 * Keep each item selled by player
 *
 * $Id: dynamic_items.h,v 1.13 2007/02/01 16:25:26 boucher Exp $
 */

#ifndef RYZOM_DYNAMIC_ITEM_H
#define RYZOM_DYNAMIC_ITEM_H

// Misc

#include "game_share/item_type.h"
#include "game_share/backup_service_interface.h"

#include "item_for_sale.h"

#include <vector>

/**
 * CDynamicItems singleton
 * list of items selling by players characters
 * \author Alain Saffray
 * \author Nevrax France
 * \date 2003
 */
class CDynamicItems
{
	NL_INSTANCE_COUNTER_DECL(CDynamicItems);
public:

	// Start by declaring methods for persistent load/ save operations
	// The following macro is defined in persistent_data.h
	// At time of writing it evaluated to:
	//	void store(CPersistentDataRecord &pdr) const;
	//	void apply(CPersistentDataRecord &pdr);
	
	DECLARE_PERSISTENCE_METHODS_WITH_ARG(uint index)

	// return an instance on singleton
	static CDynamicItems * getInstance();

	// add dynamic item for sell
	bool addDynamicItemForSell( TItemTradePtr& item );

	// remove dynamic item for sell
	void removeDynamicItemForSell( TItemTradePtr& item );

	// init CDynamicItems, load save file
	void init();

	// save all sub vector
	void saveAll();

	// tickupdate
	void tickUpdate();
	
	// return item in _DynamicItems for character
	void getItemsOfCharacter( const NLMISC::CEntityId& charId, std::vector< TItemTradePtr >& itemsForSaleOfCharacter );

	// return true if dynamic items store initialized (= loaded)
	inline bool isInit() { return _InitOk; }

	// backup service callback
	void fileAvailable(const CFileDescription& fileDescription, NLMISC::IStream& dataStream);

private:

	CDynamicItems();

	// typedef for base sub vectors
	typedef std::vector<TItemTradePtr>		TItemTradeVector;

	// get the save directory path (does not include SaveFilesDirectory, only relative path)
	void getSavePath(std::string &path);

	// Build the file name for the sub vector (does not include SaveFilesDirectory, only relative path)
	void makeFileName(uint subIndex, std::string &fileName);

	// return the sub index according to owner
	uint32 getSubVectorIndex(const NLMISC::CEntityId& characterId);

	// return the sub index according to item owner
	uint32 getSubVectorIndex(const TItemTradePtr& item);

	TItemTradeVector &getSubVector(const TItemTradePtr& item);

	// save dynamic items content sub vector
	void save(uint subIndex );



	enum // for speudo contantes
	{	
		SALE_STORE_VERSION = 1,
		// 1024 vectors 
		NUM_SUB_VECTORS = 1<<10,
		// mask for sub vector index
		SUB_VECTOR_MASK = NUM_SUB_VECTORS-1,
	};

	static CDynamicItems *	_Instance;

	TItemTradeVector		_DynamicItems[NUM_SUB_VECTORS];
//	std::vector< TItemTradePtr >	_DynamicItems;
	NLMISC::TGameCycle		_LastSaveTick;
	uint32					_NextVectorToSave;
	uint32					_NextVectorToCheck;
	uint32					_NextItemToCheck;
	uint32					_TotalNbItemsForSale;

	bool					_InitOk;

	uint32					_CurrentLoadIndex;
};

#endif // RYZOM_STATIC_ITEM_H

/* dynamic_items.h */

