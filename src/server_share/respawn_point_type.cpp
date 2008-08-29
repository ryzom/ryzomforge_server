/** \file respawn_point_type.cpp
 * 
 * $Id: respawn_point_type.cpp,v 1.6 2004/09/28 16:24:07 brigand Exp $
 */



#include "stdpch.h"

#include "respawn_point_type.h"
// nel
#include "nel/misc/string_conversion.h"

using namespace std;
using namespace NLMISC;

namespace RESPAWN_POINT
{
	NL_BEGIN_STRING_CONVERSION_TABLE (TRespawnPointType)
		NL_STRING_CONVERSION_TABLE_ENTRY(KAMI)
		NL_STRING_CONVERSION_TABLE_ENTRY(KARAVAN)
		NL_STRING_CONVERSION_TABLE_ENTRY(OUTPOST)
		NL_STRING_CONVERSION_TABLE_ENTRY(NEWBIELAND)
		NL_STRING_CONVERSION_TABLE_ENTRY(RESPAWNABLE)
		NL_STRING_CONVERSION_TABLE_ENTRY(NORMAL)
	NL_END_STRING_CONVERSION_TABLE(TRespawnPointType, RespawnPointTypeConversion, UNKNOWN)
		
	
	
	//-----------------------------------------------
	// toRespawnPointType :
	//-----------------------------------------------
	TRespawnPointType toRespawnPointType(const std::string &str)
	{
		return RespawnPointTypeConversion.fromString(str);
	}


	//-----------------------------------------------
	// toString :
	//-----------------------------------------------
	const std::string& toString(TRespawnPointType respawn_point_type)
	{
		return RespawnPointTypeConversion.toString(respawn_point_type);
	}
}; // RESPAWN_POINT
