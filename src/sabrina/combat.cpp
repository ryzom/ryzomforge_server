/** \file combat.cpp
 * <File description>
 *
 * $Id: combat.cpp,v 1.2 2004/03/01 19:22:18 lecroart Exp $
 */



#include "stdpch.h"
#include "combat.h"
//
#include "nel/misc/debug.h"
#include "nel/misc/string_conversion.h"

using namespace std;
using namespace NLMISC;

uint8 CCombat::_MaxHistoryDepth	= 2;

namespace COMBAT_HISTORY
{

	// The conversion table
	NL_BEGIN_STRING_CONVERSION_TABLE (TCombatHistory)
		NL_STRING_CONVERSION_TABLE_ENTRY (Miss)
		NL_STRING_CONVERSION_TABLE_ENTRY (Fumble)
		NL_STRING_CONVERSION_TABLE_ENTRY (Parry)
		NL_STRING_CONVERSION_TABLE_ENTRY (Dodge)
		NL_STRING_CONVERSION_TABLE_ENTRY (HitHead)
		NL_STRING_CONVERSION_TABLE_ENTRY (HitChest)
		NL_STRING_CONVERSION_TABLE_ENTRY (HitArms)
		NL_STRING_CONVERSION_TABLE_ENTRY (HitHands)
		NL_STRING_CONVERSION_TABLE_ENTRY (HitLegs)
		NL_STRING_CONVERSION_TABLE_ENTRY (HitFeet)
		NL_STRING_CONVERSION_TABLE_ENTRY (CriticalHitHead)
		NL_STRING_CONVERSION_TABLE_ENTRY (CriticalHitChest)
		NL_STRING_CONVERSION_TABLE_ENTRY (CriticalHitArms)
		NL_STRING_CONVERSION_TABLE_ENTRY (CriticalHitHands)
		NL_STRING_CONVERSION_TABLE_ENTRY (CriticalHitLegs)
		NL_STRING_CONVERSION_TABLE_ENTRY (CriticalHitFeet)
		NL_STRING_CONVERSION_TABLE_ENTRY (Unknown)
	NL_END_STRING_CONVERSION_TABLE(TCombatHistory, CombatHistoryConversion, Unknown)


	//--------------------------------------------------------------
	//					CCombat::toString()
	//--------------------------------------------------------------
	const string &toString(TCombatHistory event)
	{
		return CombatHistoryConversion.toString(event);
	}
}; // COMBAT_HISTORY //


