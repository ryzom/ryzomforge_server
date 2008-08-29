/** \file ai_aiming_type.cpp
 * 
 * $Id: ai_aiming_type.cpp,v 1.3 2005/02/22 10:25:13 besson Exp $
 */



#include "stdpch.h"
//
#include "nel/misc/debug.h"
#include "nel/misc/string_conversion.h"
//
#include "ai_aiming_type.h"

using namespace std;
using namespace NLMISC;

namespace AI_AIMING_TYPE
{
	// The conversion table
	NL_BEGIN_STRING_CONVERSION_TABLE (TAiAimingType)
		NL_STRING_CONVERSION_TABLE_ENTRY (Random)

		NL_STRING_CONVERSION_TABLE_ENTRY (Head)
		NL_STRING_CONVERSION_TABLE_ENTRY (Chest)
		NL_STRING_CONVERSION_TABLE_ENTRY (Arms)
		NL_STRING_CONVERSION_TABLE_ENTRY (Hands)
		NL_STRING_CONVERSION_TABLE_ENTRY (Legs)
		NL_STRING_CONVERSION_TABLE_ENTRY (Feet)

		NL_STRING_CONVERSION_TABLE_ENTRY (LeastProtected)
		NL_STRING_CONVERSION_TABLE_ENTRY (AveragestProtected)
		NL_STRING_CONVERSION_TABLE_ENTRY (MostProtected)
		
		NL_STRING_CONVERSION_TABLE_ENTRY (Unknown)
	NL_END_STRING_CONVERSION_TABLE(TAiAimingType, Conversion, Unknown)


	const string &toString(TAiAimingType type)
	{
		return Conversion.toString(type);
	}

	TAiAimingType toAimingType( const string &str)
	{
		return Conversion.fromString(str);
	}

	SLOT_EQUIPMENT::TSlotEquipment toSlot(TAiAimingType type)
	{
		switch(type)
		{
		case Head:
			return SLOT_EQUIPMENT::HEAD;
		case Chest:
			return SLOT_EQUIPMENT::CHEST;
		case Arms:
			return SLOT_EQUIPMENT::ARMS;
		case Hands:
			return SLOT_EQUIPMENT::HANDS;
		case Legs:
			return SLOT_EQUIPMENT::LEGS;
		case Feet:
			return SLOT_EQUIPMENT::FEET;
		default:
			return SLOT_EQUIPMENT::UNDEFINED;
		};
	}

}; // AI_AIMING_TYPE
