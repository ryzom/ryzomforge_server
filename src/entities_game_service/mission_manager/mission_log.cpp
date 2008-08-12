/** \file mission_log.cpp
 * <File description>
 *
 * $Id: mission_log.cpp,v 1.10 2005/02/08 18:59:00 boucher Exp $
 */



#include "stdpch.h"
#include "mission_log.h"
#include "nel/misc/displayer.h"

using namespace std;
using namespace NLMISC;

CMissionLog MissionLog;
//bool VerboseMissions = false;

//-----------------------------------------------
// CMissionLog init
//-----------------------------------------------
void CMissionLog::init(const std::string & logFile)
{
	NL_ALLOC_CONTEXT(ML_INIT);
	_LogFile = logFile;
	if ( logFile.empty() )
		Log = NLMISC::WarningLog;
	else
	{
		Log = new NLMISC::CLog;
		_Fd.setParam ( logFile, true);
		Log->addDisplayer (&_Fd);
	}
}// CMissionLog init

//-----------------------------------------------
// CMissionLog release
//-----------------------------------------------
void CMissionLog::release()
{
	if ( Log != NLMISC::WarningLog )
		delete Log;
}// CMissionLog release

//-----------------------------------------------
//-----------------------------------------------
void CMissionLog::display(const char *format, ...)
{
	if (Log == NULL) return;

	char *str;
	NLMISC_CONVERT_VARGS (str, format, 256/*NLMISC::MaxCStringSize*/);
	
	string toDisp = str;
	toDisp = string(IDisplayer::dateToHumanString()) + string(" ") + toDisp;

	Log->displayRawNL(toDisp.c_str());
}
