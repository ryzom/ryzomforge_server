/** \file merchant.cpp
  * establish and keep an accurate list of item selled by an merchant NPC
 *
 * $Id: merchant.cpp,v 1.12 2007/05/09 15:33:39 boucher Exp $
 */

#include "stdpch.h"
#include <vector>

#include "shop_type/merchant.h"

#include "creature_manager/creature.h"

using namespace std;
using namespace NLMISC;

NL_INSTANCE_COUNTER_IMPL(CMerchant);

//-----------------------------------------------------------------------------
CMerchant::~CMerchant()
{
	clearMerchantTradeList();
	_ExpliciteShopContent.releaseShopUnit();
}

//-----------------------------------------------------------------------------
void CMerchant::addShopUnit( const IShopUnit * shop )
{
	for( uint i = 0; i < _MerchantTradeList.size(); ++i )
	{
		if( _MerchantTradeList[ i ] == shop )
			return;
	}
	_MerchantTradeList.push_back( shop );
}

//-----------------------------------------------------------------------------
void CMerchant::clearMerchantTradeList()
{
	_MerchantTradeList.clear();
	_MerchantTradeList.push_back( &_ExpliciteShopContent );
}

//-----------------------------------------------------------------------------
void CMerchant::addExpliciteSellingItem( CSmartPtr< IItemTrade>& item )
{
	_ExpliciteShopContent.addContent( item );
}

//-----------------------------------------------------------------------------
const vector< const IShopUnit * >& CMerchant::getMerchantTradeList()
{
	if(_Creature)
		_Creature->updateMerchantTradeList();
	return _MerchantTradeList; 
}

//-----------------------------------------------------------------------------
bool CMerchant::sellPlayerItem() 
{ 
	return _Creature ? _Creature->sellPlayerItem() : false;
}
