/** \file merchant.h
 * establish and keep an accurate list of item selled by an merchant NPC
 *
 * $Id: merchant.h,v 1.13 2006/11/02 16:06:21 saffray Exp $
 */

#ifndef RYZOM_MERCHANT_H
#define RYZOM_MERCHANT_H

#include "game_share/item_type.h"
#include "game_share/rm_family.h"

#include "egs_sheets/egs_static_game_sheet.h"
//#include "shop_type/character_shopping_list.h"
#include "shop_unit.h"
#include "creature_manager/creature.h"

#include <vector>
#include <string>

//class CCharacterShoppingList;
class CCreature;

/**
 * CMerchant
 * Mount list of items selling by NPC merchant
 * \author Alain Saffray
 * \author Nevrax France
 * \date 2003
 */
class CMerchant : public NLMISC::CRefCount
{
	NL_INSTANCE_COUNTER_DECL(CMerchant);
public:

	// constructor
	CMerchant( CCreature& creature ) { _Creature = &creature; _PriceFactor = 1.0f; }

	// destructor
	virtual ~CMerchant();

	// add explicite trade list
	void addExpliciteSellingItem( NLMISC::CSmartPtr< IItemTrade>& item );

	// clear explicit trade list
	void clearExplicitTradeList() { _ExpliciteShopContent.releaseShopUnit();}

	// add shop unit in merchant trade list
	void addShopUnit( const IShopUnit * );

	// clear trade list
	void clearMerchantTradeList();

	// get merchant trade list
	const std::vector< const IShopUnit * >& getMerchantTradeList();

	// add a CCharacterShoopingList consulting trade list
//	void addCharacterShowingTradeList( CCharacterShoppingList& characterShoppingList ) { _CharacterShowingTradeList.push_back( &characterShoppingList ); }

	// return true if merchant sell player item
	bool sellPlayerItem();

	// return price factor of merchant
	float getPriceFactor() const { return _PriceFactor; }

	// set price factor
	void setPriceFactor( float f ) { _PriceFactor = f; }

	// clear creature ptr
	void clearCreaturePtr() { _Creature = NULL; }

	/// wrapper to CCreature
	inline const CStaticCreatures* getForm() const { return _Creature ? _Creature->getForm() : NULL; };
	inline PVP_CLAN::TPVPClan getAltarClanRestriction() { return _Creature ? _Creature->getAltarClanRestriction() : PVP_CLAN::None ; }
	inline bool getAltarForNeutral() { return _Creature ? _Creature->getAltarForNeutral() : false; }
	sint32 getAltarFameRestriction() { return _Creature ? _Creature->getAltarFameRestriction() : CStaticFames::INVALID_FACTION_INDEX; }
	inline sint32 getAltarFameValueRestriction() { return _Creature ? _Creature->getAltarFameValueRestriction() : 0; }

private:
	CCreature *													_Creature;
	std::vector< const IShopUnit * >							_MerchantTradeList;
	CShopUnitStatic												_ExpliciteShopContent;
	float														_PriceFactor;
//	std::vector< NLMISC::CRefPtr< CCharacterShoppingList > >	_CharacterShowingTradeList;
};

#endif // RYZOM_MERCHANT_H

/* merchant.h */

