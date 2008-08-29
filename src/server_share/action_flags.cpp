/** \file action_flags.cpp
 * 
 * $Id: action_flags.cpp,v 1.3 2004/03/01 19:21:52 lecroart Exp $
 */



#include "stdpch.h"

// nel
#include "nel/misc/i18n.h"
#include "nel/misc/string_conversion.h"

#include "action_flags.h"

using namespace std;
using namespace NLMISC;

namespace RYZOMACTIONFLAGS
{
	// The conversion table
	const CStringConversion<TActionFlag>::CPair stringTable [] =
	{
		{ "Attacks", Attacks },
		{ "Undefined", Undefined },
	};		

	CStringConversion<TActionFlag> conversion(stringTable, sizeof(stringTable) / sizeof(stringTable[0]),  Undefined);
	

	// convert item family id to item family name string
	const std::string& toString( TActionFlag flag )
	{
		return conversion.toString(flag);
	}

	
	// convert item type name to item type enum value
	TActionFlag toActionFlag( const std::string& str )
	{
		return conversion.fromString(str);
	}
}; // RYZOMACTIONFLAGS
