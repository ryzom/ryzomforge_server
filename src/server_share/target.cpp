/** \file brick_families.cpp
 * 
 * $Id: target.cpp,v 1.2 2004/03/01 19:21:54 lecroart Exp $
 */




/////////////
// INCLUDE //
/////////////
#include "stdpch.h"
// Misc
#include "nel/misc/debug.h"
#include "nel/misc/string_conversion.h"
// Game Share
#include "target.h"

using namespace std;
using namespace NLMISC;

namespace TARGET
{
	// TARGET TABLE
	NL_BEGIN_STRING_CONVERSION_TABLE (TTargetRestriction)
		NL_STRING_CONVERSION_TABLE_ENTRY(EveryBody)
		NL_STRING_CONVERSION_TABLE_ENTRY(SelfOnly)
	NL_END_STRING_CONVERSION_TABLE(TTargetRestriction, TargetRestrictionConversion, EveryBody)

	//-------------------------------------------
	// stringToRestriction :
	// Get the Enum Value for a given target's restriction in string.
	// \param str : the input string
	// \return TTargetRestriction : the target's restriction value (for the enum).
	//-------------------------------------------
	TARGET::TTargetRestriction stringToTargetRestriction(const std::string &str)
	{
		return TargetRestrictionConversion.fromString(str);
	}// stringToRestriction //

	//-------------------------------------------
	// targetRestrictionToString :
	// Get the string for a given target's restriction.
	// \param targetRestriction : target's restriction
	// \return string : the target's restriction as a string.
	//-------------------------------------------
	const std::string & targetRestrictionToString(TARGET::TTargetRestriction targetRestriction)
	{
		return TargetRestrictionConversion.toString(targetRestriction);
	}// targetRestrictionToString //

};// TARGET
