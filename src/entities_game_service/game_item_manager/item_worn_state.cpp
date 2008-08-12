/** \file item_worn_state.cpp
 * 
 * $Id: item_worn_state.cpp,v 1.2 2004/04/14 14:53:46 fleury Exp $
 */


#include "stdpch.h"

#include "nel/misc/debug.h"
#include "item_worn_state.h"
// nel
#include "nel/misc/string_conversion.h"

using namespace std;
using namespace NLMISC;

namespace ITEM_WORN_STATE
{
	NL_BEGIN_STRING_CONVERSION_TABLE (TItemWornState)
		NL_STRING_CONVERSION_TABLE_ENTRY(Unspoiled)
		NL_STRING_CONVERSION_TABLE_ENTRY(WornState1)
		NL_STRING_CONVERSION_TABLE_ENTRY(WornState2)
		NL_STRING_CONVERSION_TABLE_ENTRY(WornState3)
		NL_STRING_CONVERSION_TABLE_ENTRY(WornState4)
		NL_STRING_CONVERSION_TABLE_ENTRY(Worned)
	NL_END_STRING_CONVERSION_TABLE(TItemWornState, Conversion, Unspoiled)
		
	
	//-----------------------------------------------
	// fromString:
	//-----------------------------------------------
	TItemWornState fromString(const std::string &str)
	{
		return Conversion.fromString(str);
	}


	//-----------------------------------------------
	// toString :
	//-----------------------------------------------
	const std::string& toString(TItemWornState state)
	{
		return Conversion.toString(state);
	}


	string stateMsgs[] =
	{
		"ITEM_UNSPOILED",
		"ITEM_WORN_STATE_1",
		"ITEM_WORN_STATE_2",
		"ITEM_WORN_STATE_3",
		"ITEM_WORN_STATE_4",
		"ITEM_WORNED"	
	};

	const std::string& getMessageForState(TItemWornState state)
	{
		return stateMsgs[state];
	}

}; // ITEM_WORN_STATE
