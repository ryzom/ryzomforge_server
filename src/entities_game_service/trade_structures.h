/** \file trade.h
 * Trade liste informations (name, price and spécifique information depending what is trading
 *
 * $Id: trade_structures.h,v 1.11 2005/06/23 18:02:35 boucher Exp $
 */



#ifndef TRADE_H
#define TRADE_H

// Misc
#include "nel/misc/vectord.h"

#include "game_item_manager/game_item.h"
#include "game_share/constants.h"

namespace RYZOM_TRADE
{


//type of a trade
enum TTradeType
{
	unknown = 0,
	item,
	teleport,
	brick,
	phrase,
	pact,
	plan,
};


// Specialized part of trading struct for item
struct SItemTrade
{
	NL_INSTANCE_COUNTER_DECL(SItemTrade);
public:

	// constructor
	SItemTrade() { ItemPtr = 0; Quality = 0; Level = 0; }

	uint16			Quality;
	uint16			Level;
	CGameItemPtr	ItemPtr;
	
	void copy( SItemTrade * i )
	{
		if (!i)
			return;

		Quality = i->Quality;
		Level = i->Level;
		ItemPtr = i->ItemPtr;
	}
};


///////////////////////////////////////////////////////
// User interface : Common interface for trading struct
///////////////////////////////////////////////////////
class CTradeBase
{
public:
	uint32				Price;
	uint8				Type;
	NLMISC::CSheetId	Sheet;
	void*				Specialized;

	CTradeBase() { Type = unknown; Specialized = 0; Price = 0; }

	CTradeBase( TTradeType type )
	{	
		NL_ALLOC_CONTEXT(TRDBSE);
		Type = type; 
		if ( Type == item || Type == plan )
		{
			Specialized = new SItemTrade();
		}
		else
			Specialized = 0;
	}

	// destructor
	virtual ~CTradeBase()
	{
		if( (Specialized && Type == item || Type == plan ) && Specialized != 0 )
		{
			delete ( (SItemTrade *) Specialized);
		}
	}
	
	// Copy constructor
	CTradeBase( const CTradeBase& t )
	{
		NL_ALLOC_CONTEXT(TRDBSE2);
		Price = t.Price;
		Type = t.Type;
		Sheet = t.Sheet;
		if ( (Type == item || Type == plan ) && t.Specialized != 0)
		{
			Specialized = new SItemTrade();
			( (SItemTrade *) Specialized)->copy( (SItemTrade *) t.Specialized );
		}
		else
			Specialized = 0;
	}
	
	// = operator
	const CTradeBase &operator = (const CTradeBase &a)
	{
		NL_ALLOC_CONTEXT(TRDBSE3);
		Price = a.Price;
		Type = a.Type;
		Sheet = a.Sheet;
		if ( ( Type == item || Type == plan ) && a.Specialized != 0 )
		{
			if (Specialized)
				delete  (SItemTrade *) Specialized ;

			Specialized = new SItemTrade();
			( (SItemTrade *) Specialized)->copy( (SItemTrade *) a.Specialized );
		}
		return *this;
	}
private:
	// Common part of CTrade for serial management
	struct CTradeUnserial
	{
		uint32	Price;
		uint8	Type;
		NLMISC::CSheetId Sheet;
	};

	void init( CTradeUnserial& s )
	{
		NL_ALLOC_CONTEXT(TRDBSE4);
		Price = s.Price;
		Type = s.Type;
		Sheet = s.Sheet;
		if ( Type == item || Type == plan )
		{
			Specialized = new SItemTrade();
		}
	}
};

typedef std::vector< RYZOM_TRADE::CTradeBase * > TTradeList;

}

#endif
