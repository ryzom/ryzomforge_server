/** \file utils.cpp
 *
 * $Id: utils.cpp,v 1.2 2007/05/09 15:33:12 boucher Exp $
 */


//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

#include <time.h>
#include "nel/net/service.h"
#include "game_share/utils.h"
#include "utils.h"


//-------------------------------------------------------------------------------------------------
// Handy utilities
//-------------------------------------------------------------------------------------------------

NLMISC::CSString buildDateString(uint32 timeValue)
{
	const char* monthNames[]= {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	if (timeValue==0)
		return "";
	time_t rawtime= timeValue;
	struct tm * timeinfo= gmtime(&rawtime);
	return NLMISC::toString("%u %s %u",timeinfo->tm_mday,monthNames[timeinfo->tm_mon],timeinfo->tm_year+1900);
}

NLMISC::CSString buildDowTimeString(uint32 timeValue)
{
	const char* dowNames[]= {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
	if (timeValue==0)
		return "";
	time_t rawtime= timeValue;
	struct tm * timeinfo= gmtime(&rawtime);
	BOMB_IF(timeinfo->tm_wday<1 || timeinfo->tm_wday>7,"Invalid week day reported by gmtime()!",return "");
	return NLMISC::toString("%s %u:%u",dowNames[timeinfo->tm_wday-1],timeinfo->tm_hour,timeinfo->tm_min);
}

NLMISC::CSString buildDurationString(uint32 timeValue)
{
	NLMISC::CSString result;

	if (timeValue>= 24*60*60)
	{
		result= (timeValue>= 2*24*60*60)?
			NLMISC::toString("%u_days_",timeValue/(24*60*60)):
			"1_day_";
		timeValue%= (24*60*60);
	}
	result+= NLMISC::toString("%u:%02u:%02u",timeValue/3600,(timeValue/60)%60,timeValue%60);
	return result;
}

NLMISC::CSString lookupSessionName(uint32 sessionId)
{
	// setup a static map of session ids to shard names
	typedef std::map<uint32,NLMISC::CSString> TSessionNames;
	static TSessionNames SessionNames;
	static bool init= false;
	if (!init)
	{
		breakable
		{
			init= true;

			NLMISC::CConfigFile::CVar *sessionNamesVar = NLNET::IService::getInstance()->ConfigFile.getVarPtr("HomeMainlandNames");
			DROP_IF(sessionNamesVar == NULL,"'HomeMainlandNames' not found in cfg file",break);

			for (uint i=0; i<sessionNamesVar->size()/3; ++i)
			{
				NLMISC::CSString sessionIdString= sessionNamesVar->asString(i*3);
				uint32 id = sessionIdString.atoui();
				NLMISC::CSString name = sessionNamesVar->asString(i*3+1);
				DROP_IF(id==0,"Invalid session id "+sessionIdString,continue);
				nldebug("Adding shard name mappiing: %u => %s",id,name.c_str());
				SessionNames[id]= name;
			}
		}
	}

	// lookup the session in the SessionNames map
	TSessionNames::iterator it= SessionNames.find(sessionId);

	// if the session is known then put in the session name, otherwise put in a session number
	return	(it!=SessionNames.end())? it->second.c_str(): NLMISC::toString("%s%u",SessionNames.empty()?"":"Ring:",sessionId);
}

uint32 lookupSessionId(const NLMISC::CSString& sessionName)
{
	// setup a static map of session ids to shard names
	typedef std::map<NLMISC::CSString,uint32> TSessionIds;
	static TSessionIds SessionIds;
	static bool init= false;
	if (!init)
	{
		breakable
		{
			init= true;

			NLMISC::CConfigFile::CVar *sessionNamesVar = NLNET::IService::getInstance()->ConfigFile.getVarPtr("HomeMainlandNames");
			DROP_IF(sessionNamesVar == NULL,"'HomeMainlandNames' not found in cfg file",break);

			for (uint i=0; i<sessionNamesVar->size()/3; ++i)
			{
				NLMISC::CSString sessionIdString= sessionNamesVar->asString(i*3);
				uint32 id = sessionIdString.atoui();
				NLMISC::CSString name = sessionNamesVar->asString(i*3+1);
				DROP_IF(id==0,"Invalid session id "+sessionIdString,continue);
				nldebug("Adding session id mappiing: %s => %i",name.c_str(),id);
				SessionIds[name]= id;
			}
		}
	}

	// lookup the session in the SessionNames map
	TSessionIds::iterator it= SessionIds.find(sessionName);

	// if the session is known then put in the session name, otherwise put in a session number
	return	(it!=SessionIds.end())? it->second: 0;
}
