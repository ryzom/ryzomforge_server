/* \file character_version_adapter.h
 * character version adapater
 *
 * $Id: character_version_adapter.h,v 1.25 2006/05/31 12:12:36 boucher Exp $
 */


#ifndef CHARACTER_VERSION_ADAPTER_H
#define CHARACTER_VERSION_ADAPTER_H

// Misc
#include "game_share/inventories.h"
#include "game_item_manager/game_item.h"

class CCharacter;


/**
 * Singleton class used to adapt different version of CCharacter
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CCharacterVersionAdapter
{	
	NL_INSTANCE_COUNTER_DECL(CCharacterVersionAdapter);
public:

	/// getInstance
	static inline CCharacterVersionAdapter *getInstance()
	{
		NL_ALLOC_CONTEXT(CVAGI);
		if (_Instance == NULL)
			_Instance = new CCharacterVersionAdapter();
		
		return _Instance;
	}
	
	/// Destructor
	virtual ~CCharacterVersionAdapter() {}

	/// get current version number
	uint32 currentVersionNumber() const;

	/// adapt character from given version
	void adaptCharacterFromVersion( CCharacter &character, uint32 version ) const;

	/// adapt a specific inventory to version6
	void updateInventoryToVersion6 ( CInventoryBase *inventory, INVENTORIES::TInventory inventoryType, CCharacter * character )const;

	void setToolsToMaxHP(CInventoryBase * pInv) const;
	
private:
	/// adapter methods
	void adaptToVersion1(CCharacter &character) const;
	void adaptToVersion2(CCharacter &character) const;
	void adaptToVersion3(CCharacter &character) const;
	void adaptToVersion4(CCharacter &character) const;
	void adaptToVersion5(CCharacter &character) const;
	void adaptToVersion6(CCharacter &character) const;
	void adaptToVersion7(CCharacter &character) const;
	void adaptToVersion8(CCharacter &character) const;
	void adaptToVersion9(CCharacter &character) const;
	void adaptToVersion10(CCharacter &character) const;
	void adaptToVersion11(CCharacter &character) const;
	void adaptToVersion12(CCharacter &character) const;
	void adaptToVersion13(CCharacter &character) const;
	void adaptToVersion14(CCharacter &character) const;
	void adaptToVersion15(CCharacter &character) const;
	void adaptToVersion16(CCharacter &character) const;
	void adaptToVersion17(CCharacter &character) const;
	void adaptToVersion18(CCharacter &character) const;
	void adaptToVersion19(CCharacter &character) const;
	void adaptToVersion20(CCharacter &character) const;
	void adaptToVersion21(CCharacter &character) const;
	void adaptToVersion22(CCharacter &character) const;
private:
	/// unique instance
	static CCharacterVersionAdapter*			_Instance;
	
};

#endif // CHARACTER_VERSION_ADAPTER_H
