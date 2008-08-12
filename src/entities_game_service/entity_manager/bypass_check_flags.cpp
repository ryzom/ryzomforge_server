/** \file bypass_check_flags.cpp
 * 
 *
 * $Id: bypass_check_flags.cpp,v 1.2 2005/02/22 10:22:33 besson Exp $
 */



#include "stdpch.h"


/////////////
// INCLUDE //
/////////////
#include "entity_manager/bypass_check_flags.h"
#include "nel/misc/string_conversion.h"

CBypassCheckFlags CBypassCheckFlags::NoFlags;


namespace CHECK_FLAG_TYPE
{
	NL_BEGIN_STRING_CONVERSION_TABLE (TCheckFlagType)
		NL_STRING_CONVERSION_TABLE_ENTRY (WhileSitting)
		NL_STRING_CONVERSION_TABLE_ENTRY (InWater)
		NL_STRING_CONVERSION_TABLE_ENTRY (OnMount)
		NL_STRING_CONVERSION_TABLE_ENTRY (Fear)
		NL_STRING_CONVERSION_TABLE_ENTRY (Sleep)
		NL_STRING_CONVERSION_TABLE_ENTRY (Invulnerability)
		NL_STRING_CONVERSION_TABLE_ENTRY (Stun)
	NL_END_STRING_CONVERSION_TABLE(TCheckFlagType, Conversion, Unknown)

	const std::string& toString(TCheckFlagType type)
	{
		return Conversion.toString(type);
	}

	TCheckFlagType fromString(const std::string &str)
	{
		return Conversion.fromString(str);
	}
}



void CBypassCheckFlags::setFlag(CHECK_FLAG_TYPE::TCheckFlagType type, bool on)
{
	const uint16 val = (on?1:0);

	switch(type)
	{
	case CHECK_FLAG_TYPE::WhileSitting:
		Flags.WhileSitting = val;
		break;
	case CHECK_FLAG_TYPE::InWater:
		Flags.InWater = val;
		break;
	case CHECK_FLAG_TYPE::OnMount:
		Flags.OnMount = val;
		break;
	case CHECK_FLAG_TYPE::Fear:
		Flags.Fear = val;
		break;
	case CHECK_FLAG_TYPE::Sleep:
		Flags.Sleep = val;
		break;
	case CHECK_FLAG_TYPE::Invulnerability:
		Flags.Invulnerability = val;
		break;
	case CHECK_FLAG_TYPE::Stun:
		Flags.Stun = val;
		break;
	default:;
	};
}
