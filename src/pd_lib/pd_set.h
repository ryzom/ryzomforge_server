/** \file pd_set.h
 * <File description>
 *
 * $Id: pd_set.h,v 1.1 2004/09/27 17:41:01 legros Exp $
 */

#ifndef NL_PD_SET_H
#define NL_PD_SET_H

#include "nel/misc/types_nl.h"
#include <set>
#include <map>

namespace RY_PDS
{


/**
 * <Class description>
 * \author Benjamin Legros
 * \author Nevrax France
 * \date 2003
 */
template<typename Key, typename T>
class CPDSet
{
public:

	/// Constructor
	CPDSet()
	{
	}

public:

	class iterator
	{
	public:
	};

	class const_iterator
	{
	public:
	};

private:

	/// Container Type
	typedef std::map<Key, T>		TMap;

	/// Internal STL Container
	TMap							_Map;

};

}; // RY_PDS

#endif // NL_PD_SET_H

/* End of pd_set.h */
