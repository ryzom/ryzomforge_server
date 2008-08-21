/** \file named_items.h
 * <File description>
 *
 * $Id: named_items.h,v 1.5 2005/07/11 13:27:53 besson Exp $
 */

/* Copyright, 2000-2004 Nevrax Ltd.
 *
 * This file is part of NEVRAX RYZOM.
 * NEVRAX RYZOM is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX RYZOM is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX RYZOM; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#ifndef RY_NAMED_ITEMS_H
#define RY_NAMED_ITEMS_H

#include "nel/misc/types_nl.h"
#include "game_item_manager/game_item.h"

class CPersistentDataRecord;

/**
 * Class used to managed named items, scripted by level designers
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CNamedItems
{
public:
	/// get singleton instance
	static CNamedItems &getInstance()
	{
		if(!_Instance)
		{
			_Instance = new CNamedItems;
			nlassert(_Instance);
		}
		return *_Instance;
	}

	/// load named items from file
	void loadNamedItemsFromFile(const std::string & fileName);

	/// create a named item
	CGameItemPtr createNamedItem(const std::string & name, uint32 quantity);

	/// get a reference on a specific named item (to get all its properties)
	CGameItemPtr getNamedItemRef(const std::string &name);

private:
	/// private ctor
	CNamedItems();

	/// load an named items inventory from a persistent data record
	CInventoryPtr loadFromPdr(CPersistentDataRecord & pdr);
	/// save an inventory item into a persistent data record
	void saveIntoPdr(CPersistentDataRecord & pdr, CInventoryPtr namedItemsInv);

private:
	/// singleton instance
	static CNamedItems * _Instance;

	/// named items, sorted by names
	CHashMap<std::string, CGameItemPtr> _NamedItems;
};


#endif // RY_NAMED_ITEMS_H

/* End of named_items.h */
