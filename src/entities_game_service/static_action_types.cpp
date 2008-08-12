/** \file static_action_types.cpp
 * <File description>
 *
 * $Id: static_action_types.cpp,v 1.7 2005/02/04 10:34:34 coutelas Exp $
 */



#include "stdpch.h"
#include "static_action_types.h"
#include "nel/misc/string_conversion.h"

using namespace std;
using namespace NLMISC;

namespace STATIC_ACT_TYPES
{

NL_BEGIN_STRING_CONVERSION_TABLE (TStaticActTypes)
NL_STRING_CONVERSION_TABLE_ENTRY(Neutral)
NL_STRING_CONVERSION_TABLE_ENTRY(Casting)
NL_STRING_CONVERSION_TABLE_ENTRY(Forage)
NL_STRING_CONVERSION_TABLE_ENTRY(BotChat)
NL_STRING_CONVERSION_TABLE_ENTRY(Teleport)
NL_STRING_CONVERSION_TABLE_ENTRY(Mount)
NL_STRING_CONVERSION_TABLE_ENTRY(Unknown)
NL_END_STRING_CONVERSION_TABLE(TStaticActTypes, StaticActTypesConversion, Unknown)


//-----------------------------------------------
// toSBrickFamily :
//-----------------------------------------------
TStaticActTypes StaticActTypes(const std::string &str)
{
	return StaticActTypesConversion.fromString(str);
} // toBrickFamily //


//-----------------------------------------------
// toString :
//-----------------------------------------------
const std::string &toString(TStaticActTypes type)
{
	return StaticActTypesConversion.toString(type);
} // toString //

}
