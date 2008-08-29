/** \file place_type.cpp
 * 
 * $Id: place_type.cpp,v 1.2 2006/05/31 12:15:01 boucher Exp $
 */

#include "stdpch.h"

#include "nel/misc/debug.h"
#include "place_type.h"
// nel
#include "nel/misc/string_conversion.h"

using namespace std;
using namespace NLMISC;

namespace PLACE_TYPE
{
	const CStringConversion<TPlaceType>::CPair stringTable [] =
	{
		{ "Capital", Capital },
		{ "Village", Village },
		{ "Outpost", Outpost },
		{ "Locality", Place },
		{ "Street", Street },
		{ "Undefined", Undefined },
	};		
	CStringConversion<TPlaceType> conversion(stringTable, sizeof(stringTable) / sizeof(stringTable[0]), Undefined);


	//-----------------------------------------------
	// fromString :
	//-----------------------------------------------
	TPlaceType fromString(const std::string &str)
	{
		return conversion.fromString(str);
	}


	//-----------------------------------------------
	// toString :
	//-----------------------------------------------
	const std::string& toString(TPlaceType place_type)
	{
		return conversion.toString(place_type);
	}
};
