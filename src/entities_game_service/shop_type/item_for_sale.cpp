/** \file item_for_sale.cpp
 * class contains data and accessors for an item selled by player character with shop store system
 *
 * $Id: item_for_sale.cpp,v 1.20 2007/07/11 15:27:55 boucher Exp $
 */

#include "stdpch.h"

#include "item_for_sale.h"
#include "player_manager/character.h"

using namespace std;
using namespace NLMISC;


#define PERSISTENT_TOKEN_FAMILY RyzomTokenFamily


CVariable<double>	GlobalFactionPointPriceFactor("egs", "GlobalFactionPointPriceFactor", "this factor is applied to all faction point prices", 1.0, 0, true);


NL_INSTANCE_COUNTER_IMPL(IItemTrade);
NL_INSTANCE_COUNTER_IMPL(CTradeBase);

//-----------------------------------------------------------------------------
CItemForSale::CItemForSale()
{ 
	_Available = false;
	_ItemPtr = 0;
}

//-----------------------------------------------------------------------------
CItemForSale::~CItemForSale()
{

	if( _ItemPtr != 0 )
	{
		_ItemPtr.deleteItem();
		_ItemPtr = 0;
	}
}

//-----------------------------------------------------------------------------
void CItemForSale::itemForSale( uint32 price, uint32 retirePrice, CGameItemPtr item, uint32 quantity, const NLMISC::CEntityId& id, CONTINENT::TContinent continent, uint32 identifier )
{
#ifdef NL_DEBUG
	nlassert( item != NULL );
//	nlassert( item->parent() == NULL );
	nlassert( item->getInventory() == NULL );
#endif
	if( item != NULL )
	{
		// TODO : check if this 'detach' is needed
//		item->detachFromParent(); 
		RYMSG::TPriceInfo pi;
		_PriceInfo.setCurrency(RYMSG::TTradeCurrency::tc_dappers);
		_PriceInfo.setAmount(price);
		_RetirePrice = retirePrice;
		_ItemPtr = item;
		_Quantity = quantity;

		_StartSaleCycle = CTickEventHandler::getGameCycle();
		_Owner = id;
		_Continent = continent;
		_Identifier = identifier;
	}	
}

//-----------------------------------------------------------------------------
void CItemForSale::setAvailable( bool a )
{
	if( a == true )
	{
		_Available = true;
	}
	else
	{
		if( _Quantity > 0 )
			--_Quantity;
		if( _Quantity == 0 )
			_Available = false;
	}
}

//-----------------------------------------------------------------------------
//void CItemForSale::serial(NLMISC::IStream &f) throw(NLMISC::EStream )
//{
//	f.serial( _PriceInfo );
//	f.serial( _RetirePrice );
//	f.serial( _StartSaleCycle );
//	f.serial( _Owner );
//	f.serialEnum( _Continent );
//	f.serial( _Quantity );
//	f.serial( _Identifier );
//	
//	if( f.isReading() )
//	{
//		_ItemPtr.newItem();
//		nlassertex( _ItemPtr != 0, ("Item for sale is NULL after newItem()") );
////		_ItemPtr->load( f, _Owner, CCharacter::getCurrentVersion() );
//		_ItemPtr->legacyLoad( f, CCharacter::getCurrentVersion(), NULL );
//	}
//	else
//	{
//		nlassert(false);
//		nlassertex( _ItemPtr != 0, ("Item for sale is NULL and want save it") );
////		_ItemPtr->save( f );
//	}
//}

//-----------------------------------------------------------------------------
void CItemForSale::copy( IItemTrade * itt )
{
	_PriceInfo = itt->getPriceInfo();
	_RetirePrice = itt->getRetirePrice();
	_StartSaleCycle = itt->getStartSaleCycle();
	if( itt->getItemPtr() != 0 )
	{
		_ItemPtr = itt->getItemPtr()->getItemCopy();
	}
	else _ItemPtr = 0;
	_Owner = itt->getOwner();
	_Continent = itt->getContinent();
	_Available = 0;
	_Quantity = itt->getQuantity();
	_Identifier = itt->getIdentifier();
}

//-----------------------------------------------------------------------------
CTradeBase::~CTradeBase()
{
}

//-----------------------------------------------------------------------------
void CTradeBase::copy( IItemTrade * itt )
{
	_PriceInfo = itt->getPriceInfo();
	_Sheet = itt->getSheetId();
	_Quality = itt->getQuality();
	_Level = itt->getLevel();
	if( itt->getItemPtr() != 0 )
	{
		_ItemPtr = itt->getItemPtr()->getItemCopy();
	}
	else _ItemPtr = 0;
}

//-----------------------------------------------------------------------------
//uint32 CTradeBase::getFactionPointPrice() const
//{
//	return uint32(_FactionPointPrice * GlobalFactionPointPriceFactor.get() + 0.5);
//}

//-----------------------------------------------------------------------------
// Persistent data for CItemForSale
//-----------------------------------------------------------------------------

#define PERSISTENT_CLASS CItemForSale

#define PERSISTENT_DATA\
	PROP2(_Price, uint32, _PriceInfo.getAmount(), _PriceInfo.setCurrency(RYMSG::TTradeCurrency::tc_dappers); _PriceInfo.setAmount(val))\
	PROP(uint32,_RetirePrice)\
	PROP_GAME_CYCLE_COMP(_StartSaleCycle)\
	PROP(CEntityId,_Owner)\
	PROP2(_Continent,string,CONTINENT::toString(_Continent),_Continent=CONTINENT::toContinent(val))\
	PROP(uint32,_Quantity)\
	PROP(uint32,_Identifier)\
	STRUCT2(_ItemPtr,_ItemPtr->store(pdr),\
		_ItemPtr.newItem();\
		CGameItem::CPersistentApplyArg applyArgs;\
		_ItemPtr->apply(pdr, applyArgs))\

#pragma message( PERSISTENT_GENERATION_MESSAGE )
#include "game_share/persistent_data_template.h"


