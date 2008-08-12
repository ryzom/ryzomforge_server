/** \file special_trade_list.h
 * Bot special trade list.
 *
 * $Id: special_trade_list.h,v 1.10 2006/05/31 12:17:10 boucher Exp $
 */

#ifndef RY_SPECIAL_TRADE_LIST_H
#define RY_SPECIAL_TRADE_LIST_H


/**
 * Bot special trade list.
 * A bot can sell / buy items for better / worse price.
 * This class is build around a pointer, so that each bot doesn't store an instance of a special trade list but only 32bits for the pointer
 * WARNING : sell means that the bot sell the item, buy means that the bot buys it to a player
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CSpecialTradeList
{
public:

	/// ctor
	CSpecialTradeList()
		:_Content(NULL){}

	/// dtor
	~CSpecialTradeList()
	{
		removeAllContent();
	}

	///\return true if the list is empty ( i.e. : not allocated )
	bool empty()
	{
		return _Content == NULL;
	}
	/// add a sold item in the list
	void addSoldItem( const NLMISC::CSheetId & sheet, uint16 level, float factor )
	{
		allocate();
		CSoldItem item;
		item.Factor = factor;
		item.Level = level;
		item.Sheet = sheet;
		_Content->SoldItems.push_back( item );
	}
	/// add a bought item in the list
	void addBoughtItem( const NLMISC::CSheetId & sheet, float factor )
	{
		allocate();
		CBoughtItem item;
		item.Factor = factor;
		item.Sheet = sheet;
		_Content->BoughtItems.push_back( item );
	}
	/// get the buy price of an item ( return true if found )
	bool getBuyPriceFactor( const NLMISC::CSheetId & sheet, float & factor )const
	{
		if ( ! _Content )
			return false;
		for ( uint i = 0; i < _Content->BoughtItems.size(); i++ )
		{
			if ( _Content->BoughtItems[i].Sheet == sheet )
			{
				factor = _Content->BoughtItems[i].Factor;
				return true;
			}
		}
		return false;
	}
	/// get the sell price of an item ( return true if found )
	bool getSellPriceFactor( const NLMISC::CSheetId & sheet, uint16 level, float & factor )const
	{
		if ( ! _Content )
			return false;
		for ( uint i = 0; i < _Content->SoldItems.size(); i++ )
		{
			if ( _Content->SoldItems[i].Sheet == sheet && _Content->SoldItems[i].Level == level )
			{
				factor = _Content->SoldItems[i].Factor;
				return true;
			}
		}
		return false;
	}

	/// return the number of sold items in the list
	uint getSoldItemCount()
	{
		if(!_Content)
			return 0;
		return _Content->SoldItems.size();
	}

	void getSoldItem(uint idx,NLMISC::CSheetId & sheet, uint16 & level, float & factor)
	{
		nlassert(_Content);
		if ( idx < _Content->SoldItems.size() )
		{
			level = _Content->SoldItems[idx].Level;
			sheet = _Content->SoldItems[idx].Sheet;
			factor = _Content->SoldItems[idx].Factor;
		}
	}
	
	void removeAllContent()
	{
		if ( _Content )
		{
			delete _Content;
			_Content = NULL;
		}
	}

private:
	/// allocate the list
	void allocate()
	{
		NL_ALLOC_CONTEXT(SPEC_TL);
		if ( !_Content )
			_Content = new CContent;
	}
	struct CSoldItem
	{
		NLMISC::CSheetId	Sheet;
		float				Factor;
		uint16				Level;
	};
	struct CBoughtItem
	{
		NLMISC::CSheetId	Sheet;
		float				Factor;
	};

	/// the real content of the class
	struct CContent
	{
		NL_INSTANCE_COUNTER_DECL(CContent);
	public:

		std::vector< CSoldItem >	SoldItems;
		std::vector< CBoughtItem >	BoughtItems;
	};
	CContent * _Content;
};


#endif // RY_SPECIAL_TRADE_LIST_H

/* End of special_trade_list.h */
