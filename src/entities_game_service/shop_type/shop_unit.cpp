/** \file shop_unit.cpp
 * Interface for shop unit and specialized class: 
 *
 * $Id: shop_unit.cpp,v 1.5 2004/12/24 13:02:44 boucher Exp $
 */

#include "stdpch.h"

#include "shop_unit.h"

NL_INSTANCE_COUNTER_IMPL(IShopUnit);

//-----------------------------------------------------------------------------
void CShopUnitStatic::releaseShopUnit()
{
	_ShopContent.clear();
}

//-----------------------------------------------------------------------------
void CShopUnitStatic::addContent( const TItemTradePtr& item )
{
	if( dynamic_cast<CTradeBase *>( (IItemTrade*)item ) != 0 )
	{
		_ShopContent.push_back( item );
	}
}

//-----------------------------------------------------------------------------
void CShopUnitDynamic::releaseShopUnit()
{
	_ShopContent.clear();
}

//-----------------------------------------------------------------------------
void CShopUnitDynamic::addContent( const TItemTradePtr& item )
{
	if( dynamic_cast<CItemForSale *>( (IItemTrade*)item ) != 0 )
	{
		//todo: check if item are already in shop
		_ShopContent[ item->getContinent() ].push_back( item ); 
		_CycleContentChange = CTickEventHandler::getGameCycle();
		item->setAvailable( true );
	}
}

//-----------------------------------------------------------------------------
bool CShopUnitDynamic::removeContent( const TItemTradePtr& item, bool updateQuantity )
{
	if( dynamic_cast<CItemForSale *>( (IItemTrade*)item ) != 0 )
	{
		for( uint32 i = 0; i < _ShopContent[ item->getContinent() ].size(); ++i )
		{
			if( (IItemTrade*)item == (IItemTrade*)_ShopContent[ item->getContinent() ] [ i ] )
			{
				// RM are in mutlitple shop unit (one per item part, and we must update quantity one time par Rm (and not one time per item part)
				if( updateQuantity )
					item->setAvailable( false );
				if( item->isAvailable( 1 ) == false )
				{
					_ShopContent[ item->getContinent() ] [ i ] = _ShopContent[ item->getContinent() ].back();
					_ShopContent[ item->getContinent() ].pop_back();
					return true;
				}
				return false;
			}
		}
	}
	return true;
}
