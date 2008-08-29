/** \file pvp_relation.cpp
 * 
 * $Id: pvp_relation.cpp,v 1.1 2005/09/30 15:27:33 coutelas Exp $
 */

#include "stdpch.h"

#include "nel/misc/string_conversion.h"
#include "nel/misc/sstring.h"

#include "pvp_relation.h"

using namespace std;
using namespace NLMISC;

namespace PVP_RELATION
{

	NL_BEGIN_STRING_CONVERSION_TABLE (TPVPRelation)
		NL_STRING_CONVERSION_TABLE_ENTRY(Neutral)
		NL_STRING_CONVERSION_TABLE_ENTRY(NeutralPVP)
		NL_STRING_CONVERSION_TABLE_ENTRY(Ally)
		NL_STRING_CONVERSION_TABLE_ENTRY(Ennemy)
	NL_END_STRING_CONVERSION_TABLE(TPVPRelation, PVPRelationConversion, Unknown)

	TPVPRelation fromString(const std::string & str)
	{
		return PVPRelationConversion.fromString(str);
	}

	const std::string & toString(TPVPRelation relation)
	{
		return PVPRelationConversion.toString(relation);
	}
	
} // namespace PVP_RELATION
