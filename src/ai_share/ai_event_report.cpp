/** \file ai_event_report.cpp
 *
 * $Id: ai_event_report.cpp,v 1.3 2004/03/01 19:21:52 lecroart Exp $
 */



#include "stdpch.h"
#include "ai_event_report.h"
// nel
#include "nel/misc/string_conversion.h"

using namespace std;
using namespace NLMISC;

namespace AI_EVENT_REPORT
{
	// The conversion table
	const CStringConversion<TAIReportStat>::CPair stringTable [] =
	{
		{ "HitPoints",	HitPoints },
		{ "Stamina",	Stamina },
		{ "Sap",		Sap },
		{ "Unknown",	Unknown },
	};

	CStringConversion<TAIReportStat> conversion(stringTable, sizeof(stringTable) / sizeof(stringTable[0]),  Unknown);

	

// convert type id to type name string
const std::string& toString( TAIReportStat stat )
{
	return conversion.toString(stat);
}

// convert type name to type enum value
TAIReportStat toStat( const std::string& str )
{
	return conversion.fromString(str);
}

// convert a score to an ai Stat
TAIReportStat scoreToStat( SCORES::TScores score )
{
	return conversion.fromString( SCORES::toString(score) );
}

} // AI_EVENT_REPORT
