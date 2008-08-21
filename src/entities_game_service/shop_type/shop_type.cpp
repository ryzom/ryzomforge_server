/** \file shop_type.cpp
 * shop type contains one type item in shops bases
 *
 * $Id: shop_type.cpp,v 1.3 2005/02/08 18:59:04 boucher Exp $
 */


#include "stdpch.h"

#include "shop_type.h"

NL_INSTANCE_COUNTER_IMPL(IShopType);

//-----------------------------------------------------------------------------
CItemShopType::CItemShopType() 
{ 
	_ShopType = IShopType::item; 

	for( uint i = 0; i < ITEM_ORIGIN::NUM_ITEM_ORIGIN; ++i )
	{
		for( uint j = 0; j < NumQuality; ++j )
		{
			for( uint k = 0; k < NumLevel; ++k )
			{
				for( uint l = 0; l < IShopUnit::NumShopUnitType; ++l )
				{
					_ShopItemBaseContent [ i ] [ j ] [ k ] [ l ] = 0;
				}
			}
		}
	}
}	

//-----------------------------------------------------------------------------
void CItemShopType::releaseShopType()
{
	for( uint i = 0; i < ITEM_ORIGIN::NUM_ITEM_ORIGIN; ++i )
	{
		for( uint j = 0; j < NumQuality; ++j )
		{
			for( uint k = 0; k < NumLevel; ++k )
			{
				for( uint l = 0; l < IShopUnit::NumShopUnitType; ++l )
				{
					if( _ShopItemBaseContent [ i ] [ j ] [ k ] [ l ] != 0 )
					{
						delete _ShopItemBaseContent [ i ] [ j ] [ k ] [ l ];
						_ShopItemBaseContent [ i ] [ j ] [ k ] [ l ] = 0;
					}
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
IShopUnit * CItemShopType::getShopUnit( uint32 selector1, uint32 selector2, uint32 selector3, IShopUnit::TShopUnitType shopUnitType )
{
	nlassert( selector1 < ITEM_ORIGIN::NUM_ITEM_ORIGIN );
	nlassert( selector2 < NumQuality );
	nlassert( selector3 < NumLevel );
	nlassert( shopUnitType == IShopUnit::StaticShop || shopUnitType == IShopUnit::DynamicShop );
	return _ShopItemBaseContent [ selector1] [ selector2 ] [ selector3 ] [ shopUnitType ];
}
	
//-----------------------------------------------------------------------------
IShopUnit * CItemShopType::createShopUnit( uint32 selector1, uint32 selector2, uint32 selector3, IShopUnit::TShopUnitType shopUnitType )
{
	IShopUnit * shopUnit = getShopUnit( selector1, selector2, selector3, shopUnitType );
	if( shopUnit == 0 )
	{
		if( shopUnitType == IShopUnit::DynamicShop )
		{
			shopUnit = _ShopItemBaseContent [ selector1 ] [ selector2 ] [ selector3 ] [ shopUnitType ] = new CShopUnitDynamic();
		}
		else
		{
			shopUnit = _ShopItemBaseContent [ selector1 ] [ selector2 ] [ selector3 ] [ shopUnitType ] = new CShopUnitStatic();
		}
	}
	else
	{
		nlassert( shopUnitType == shopUnit->getShopUnitType() );
	}
	return shopUnit;
}
	
//-----------------------------------------------------------------------------
CRMShopType::CRMShopType() 
{ 
	_ShopType = IShopType::rm;

	for( uint i = 0; i < ECOSYSTEM::NUM_ECOSYSTEM; ++i )
	{
		for( uint j = 0; j < NumQuality; ++j )
		{
			for( uint k = 0; k < NumLevel; ++k )
			{
				for( uint l = 0; l < IShopUnit::NumShopUnitType; ++l )
				{
					_ShopRMBaseContent [ i ] [ j ] [ k ] [ l ] = 0;
				}
			}
		}
	}
}	

//-----------------------------------------------------------------------------
void CRMShopType::releaseShopType()
{
	for( uint i = 0; i < ECOSYSTEM::NUM_ECOSYSTEM; ++i )
	{
		for( uint j = 0; j < NumQuality; ++j )
		{
			for( uint k = 0; k < NumLevel; ++k )
			{
				for( uint l = 0; l < IShopUnit::NumShopUnitType; ++l )
				{
					if( _ShopRMBaseContent [ i ] [ j ] [ k ] [ l ] != 0 )
					{
						delete _ShopRMBaseContent [ i ] [ j ] [ k ] [ l ];
						_ShopRMBaseContent [ i ] [ j ] [ k ] [ l ] = 0;
					}
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
IShopUnit * CRMShopType::getShopUnit( uint32 selector1, uint32 selector2, uint32 selector3, IShopUnit::TShopUnitType shopUnitType )
{
	nlassert( selector1 < ECOSYSTEM::NUM_ECOSYSTEM );
	nlassert( selector2 < NumQuality );
	nlassert( selector3 < NumLevel );
	nlassert( shopUnitType == IShopUnit::StaticShop || shopUnitType == IShopUnit::DynamicShop );
	return _ShopRMBaseContent [ selector1] [ selector2 ] [ selector3 ] [ shopUnitType ];
}

//-----------------------------------------------------------------------------
IShopUnit * CRMShopType::createShopUnit( uint32 selector1, uint32 selector2, uint32 selector3, IShopUnit::TShopUnitType shopUnitType )
{
	IShopUnit * shopUnit = getShopUnit( selector1, selector2, selector3, shopUnitType );
	if( shopUnit == 0 )
	{
		if( shopUnitType == IShopUnit::DynamicShop )
		{
			shopUnit = _ShopRMBaseContent [ selector1 ] [ selector2 ] [ selector3 ] [ shopUnitType ] = new CShopUnitDynamic();
		}
		else
		{
			shopUnit = _ShopRMBaseContent [ selector1 ] [ selector2 ] [ selector3 ] [ shopUnitType ] = new CShopUnitStatic();
		}
	}
	else
	{
		nlassert( shopUnitType == shopUnit->getShopUnitType() );
	}
	return shopUnit;
}

//-----------------------------------------------------------------------------
CTPShopType::CTPShopType()
{ 
	_ShopType = IShopType::tp; 

	for( uint i = 0; i < ECOSYSTEM::NUM_ECOSYSTEM; ++i )
	{
		for( uint j = 0; j < NumTpType; ++j )
		{
			_ShopTPBaseContent [ i ] [ j ] = 0;
		}
	}
}	

//-----------------------------------------------------------------------------
void CTPShopType::releaseShopType()
{
	for( uint i = 0; i < ECOSYSTEM::NUM_ECOSYSTEM; ++i )
	{
		for( uint j = 0; j < NumTpType; ++j )
		{
			if( _ShopTPBaseContent [ i ] [ j ] != 0 )
			{
				delete _ShopTPBaseContent [ i ] [ j ];
				_ShopTPBaseContent [ i ] [ j ] = 0;
			}
		}
	}
}

//-----------------------------------------------------------------------------
IShopUnit * CTPShopType::getShopUnit( uint32 selector1, uint32 selector2, uint32 selector3, IShopUnit::TShopUnitType shopUnitType )
{
	nlassert( selector1 < ECOSYSTEM::NUM_ECOSYSTEM );
	nlassert( selector2 < NumTpType );
	return _ShopTPBaseContent [ selector1] [ selector2 ];
}

//-----------------------------------------------------------------------------
IShopUnit * CTPShopType::createShopUnit( uint32 selector1, uint32 selector2, uint32 selector3, IShopUnit::TShopUnitType shopUnitType )
{
	IShopUnit * shopUnit = getShopUnit( selector1, selector2, selector3, shopUnitType );
	if( shopUnit == 0 )
	{
		if( shopUnitType == IShopUnit::DynamicShop )
		{
			shopUnit = _ShopTPBaseContent [ selector1 ] [ selector2 ] = new CShopUnitDynamic();
		}
		else
		{
			shopUnit = _ShopTPBaseContent [ selector1 ] [ selector2 ] = new CShopUnitStatic();
		}
	}
	else
	{
		nlassert( shopUnitType == shopUnit->getShopUnitType() );
	}
	return shopUnit;
}
