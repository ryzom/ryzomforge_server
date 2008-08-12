/** \file protection_type.cpp
 * 
 * $Id: protection_type_back_compat.cpp,v 1.2 2005/10/03 15:52:19 guignot Exp $
 */



#include "stdpch.h"

#include "nel/misc/debug.h"
#include "protection_type_back_compat.h"
// nel
#include "nel/misc/string_conversion.h"

using namespace std;
using namespace NLMISC;


namespace BACK_COMPAT
{
namespace OLD_PROTECTION_TYPE
{

NL_BEGIN_STRING_CONVERSION_TABLE (TOldProtectionType)
	NL_STRING_CONVERSION_TABLE_ENTRY(Cold)
	NL_STRING_CONVERSION_TABLE_ENTRY(Acid)
	NL_STRING_CONVERSION_TABLE_ENTRY(Rot)
	NL_STRING_CONVERSION_TABLE_ENTRY(Fire)
	NL_STRING_CONVERSION_TABLE_ENTRY(Shockwave)
	NL_STRING_CONVERSION_TABLE_ENTRY(Poison)
	NL_STRING_CONVERSION_TABLE_ENTRY(Electricity)
	NL_STRING_CONVERSION_TABLE_ENTRY(Madness)
	NL_STRING_CONVERSION_TABLE_ENTRY(Slow)
	NL_STRING_CONVERSION_TABLE_ENTRY(Snare)
	NL_STRING_CONVERSION_TABLE_ENTRY(Sleep)
	NL_STRING_CONVERSION_TABLE_ENTRY(Stun)
	NL_STRING_CONVERSION_TABLE_ENTRY(Root)
	NL_STRING_CONVERSION_TABLE_ENTRY(Blind)
	NL_STRING_CONVERSION_TABLE_ENTRY(Fear)
	NL_STRING_CONVERSION_TABLE_ENTRY(None)
NL_END_STRING_CONVERSION_TABLE(TOldProtectionType, OldProtectionTypeConversion, None)

TOldProtectionType fromString(const std::string & str)
{
	return OldProtectionTypeConversion.fromString(str);
}

const std::string & toString(TOldProtectionType oldType)
{
	return OldProtectionTypeConversion.toString(oldType);
}

} // namespace OLD_PROTECTION_TYPE
} // namespace BACK_COMPAT

