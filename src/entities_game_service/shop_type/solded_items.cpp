/** \file solded_items.cpp
 * Singleton received solded items and keep it until character are online, when his online remove it 
 * from character selled item and give to him corresponding money
 *
 * $Id: solded_items.cpp,v 1.8 2005/09/15 12:52:51 berenguier Exp $
 */

#include "stdpch.h"

#include "solded_items.h"
#include "player_manager/character.h"
#include "player_manager/player_manager.h"

CSoldedItems * CSoldedItems::_Instance = 0;

using namespace std;
using namespace NLMISC;


#define PERSISTENT_TOKEN_FAMILY RyzomTokenFamily


NL_INSTANCE_COUNTER_IMPL(CSoldedItems);

//-----------------------------------------------------------------------------
CSoldedItems * CSoldedItems::getInstance()
{
	NL_ALLOC_CONTEXT(SI_GI);
	if( _Instance == 0 )
	{
		_Instance = new CSoldedItems();
		nlassert( _Instance != 0 );
	}
	return _Instance;
}

//-----------------------------------------------------------------------------
void CSoldedItems::soldedItem( TItemTradePtr item, uint32 quantity, CCharacter * character )
{
	if( dynamic_cast<CItemForSale*>((IItemTrade*)item) != 0 )
	{
		CCharacter * character = PlayerManager.getChar( item->getOwner() );
		if( character != 0 )
		{
			character->itemSolded( item, quantity, character );
		}
		else
		{
			TItemSolded::iterator it = _SoldedItem.find( item->getOwner() );
			if( it == _SoldedItem.end() )
			{
				vector< TSoldedItem > emptyVector;
				pair<TItemSolded::iterator, bool> result = _SoldedItem.insert( make_pair( item->getOwner(), emptyVector ) );
				it = result.first;
			}

			TSoldedItem itemSolded;
			itemSolded.Item = item;
			itemSolded.Quantity = quantity;

			(*it).second.push_back( itemSolded );
			item->setAvailable( false );

			save();
		}
	}
}

//------------------------------------------------------------------------------
void CSoldedItems::characterLogon( CCharacter * character )
{
	nlassert( character != 0 );
	TItemSolded::iterator it = _SoldedItem.find( character->getId() );
	if( it != _SoldedItem.end() )
	{
		for( uint32 i = 0; i < (*it).second.size(); ++i )
		{
			character->itemSolded( (*it).second[i].Item, (*it).second[i].Quantity, 0 );
		}
		(*it).second.clear();
		_SoldedItem.erase( it );

		save();
	}
}
/*
//-----------------------------------------------------------------------------
// Global defines for persistent data system
//-----------------------------------------------------------------------------

#define PERSISTENT_MACROS_AUTO_UNDEF


//-----------------------------------------------------------------------------
// Proxy for saving TItemSolded map elements
//-----------------------------------------------------------------------------

class TItemSoldedMapElemProxy
{
public:
	DECLARE_PERSISTENCE_METHODS_WITH_TARGET(CSoldedItems::TMapElem &target)
};

#define PERSISTENT_CLASS TItemSoldedMapElemProxy

#define PERSISTENT_DATA\
	LSTRUCT_VECT(MapElem, VECT_LOGIC(target), target[i].store(pdr), VECT_APPEND(target).apply(pdr))\

#pragma message( PERSISTENT_GENERATION_MESSAGE )
#include "game_share/persistent_data_template.h"


//-----------------------------------------------------------------------------
// Persistent data for CSoldedItems
//-----------------------------------------------------------------------------

#define PERSISTENT_CLASS CSoldedItems

#define PERSISTENT_DATA\
	LSTRUCT_MAP(_SoldedItem,NLMISC::CEntityId,MAP_LOGIC(_SoldedItem),\
	(*it).first, TItemSoldedMapElemProxy().store(pdr,(*it).second),\
	TItemSoldedMapElemProxy().apply(pdr,_SoldedItem[key]))\
	
#pragma message( PERSISTENT_GENERATION_MESSAGE )
#include "game_share/persistent_data_template.h"


//-----------------------------------------------------------------------------
// Persistent data for CSoldedItems::TSoldedItem
//-----------------------------------------------------------------------------
#define PERSISTENT_CLASS CSoldedItems::TSoldedItem
#define PERSISTENT_TOKEN_CLASS TSoldedItem

#define PERSISTENT_DATA\
	PROP(uint32,Quantity)\
	STRUCT2(Item, Item->store(pdr), Item=new IItemTrade; Item->apply(pdr))\

#pragma message( PERSISTENT_GENERATION_MESSAGE )
#include "game_share/persistent_data_template.h"
*/
