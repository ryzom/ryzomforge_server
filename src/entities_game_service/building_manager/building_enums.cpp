/** \file building_enums.cpp
 * <File description>
 *
 * $Id: building_enums.cpp,v 1.1 2004/05/28 16:08:10 brigand Exp $
 */


#include "stdpch.h"
#include "building_enums.h"
#include "nel/misc/string_conversion.h"

namespace ROOM_RESTRICTION
{
	NL_BEGIN_STRING_CONVERSION_TABLE (TRestriction)
		NL_STRING_CONVERSION_TABLE_ENTRY (Rm_Fight)
		NL_STRING_CONVERSION_TABLE_ENTRY (Rm_Magic)
		NL_STRING_CONVERSION_TABLE_ENTRY (Rm_Harvest)
		NL_STRING_CONVERSION_TABLE_ENTRY (Rm_Craft)
	NL_END_STRING_CONVERSION_TABLE(TRestriction, Conversion, Unknown)
			
	//----------------------------------------------------------------------------
	TRestriction fromString( const std::string & str )
	{
		return Conversion.fromString( str );
	}	
}

namespace BUILDING_TYPES
{
	NL_BEGIN_STRING_CONVERSION_TABLE (TBuildingType)
		NL_STRING_CONVERSION_TABLE_ENTRY (Common)
		NL_STRING_CONVERSION_TABLE_ENTRY (Player)
		NL_STRING_CONVERSION_TABLE_ENTRY (Guild)
	NL_END_STRING_CONVERSION_TABLE(TBuildingType, Conversion, Unknown)
		
		//----------------------------------------------------------------------------
	TBuildingType fromString( const std::string & str )
	{
		return Conversion.fromString( str );
	}	
}


