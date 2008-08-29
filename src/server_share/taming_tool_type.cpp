/** \file taming_tool_type.cpp
 *
 * $Id: taming_tool_type.cpp,v 1.2 2004/03/01 19:21:54 lecroart Exp $
 */



#include "stdpch.h"
#include "taming_tool_type.h"
// nel
#include "nel/misc/string_conversion.h"

using namespace std;
using namespace NLMISC;

namespace TAMING_TOOL_TYPE
{
	// The conversion table
	const CStringConversion<TTamingToolType>::CPair stringTable [] =
	{
		{ "Unknown" , Unknown },
		{ "Cattleprod", Cattleprod },
		{ "Stick", Stick },
		{ "Whip", Whip },
	};

	CStringConversion<TTamingToolType> conversion(stringTable, sizeof(stringTable) / sizeof(stringTable[0]),  Unknown);

// convert type id to type name string
const std::string& toString( TTamingToolType type )
{
	return conversion.toString(type);
}

// convert type name to type enum value
TTamingToolType toToolType( const std::string& str )
{
	return conversion.fromString(str);
}


} // TAMING_TOOL_TYPE
