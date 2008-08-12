/** \file mission_log.h
 * <File description>
 *
 * $Id: mission_log.h,v 1.10 2005/01/10 14:48:26 besson Exp $
 */



#ifndef RY_MISSION_LOG_H
#define RY_MISSION_LOG_H

#include "nel/misc/log.h"
#include "nel/misc/debug.h"
#include "nel/misc/variable.h"


/**
 * separate log system for missions. Logs are in egs_mission.log. use MISLOG to log in this file
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2002
 */
class CMissionLog
{
public:

	/// init the log
	void init(const std::string & logFile);
	///release the log
	void release();
	///\return the name of the log file
	inline const std::string & getLogFile(){return _LogFile;}
	
	void display(const char *format, ...);
	
	/// the NEL log used for in the mission log
	NLMISC::CLog			*Log;
private:
	/// the file displayer used to log the mission informations
	NLMISC::CFileDisplayer	_Fd;
	/// log file name
	std::string				_LogFile;
};

/// the mission log
extern CMissionLog	MissionLog;

/// macro used to log missions script error 
#define MISLOG MissionLog.display
/// macro used to log missions informations in verbose mode (at run time)
#define MISDBG if ( !VerboseMissions ){} else MISLOG

// Syntax error logged to egs_mission.log
#define MISLOGSYNTAXERROR(_PHRASE_)				MISLOG("sline:%u SYNTAX ERROR %s : "_PHRASE_, line, script[0].c_str());
#define MISLOGSYNTAXERROR1(_PHRASE_,_PARAM_)	MISLOG("sline:%u SYNTAX ERROR %s : "_PHRASE_, line, script[0].c_str(), _PARAM_);
#define MISLOGERROR(_PHRASE_)						MISLOG("sline:%u ERROR %s : "_PHRASE_, line, script[0].c_str());
#define MISLOGERROR1(_PHRASE_,_PARAM_)				MISLOG("sline:%u ERROR %s : "_PHRASE_, line, script[0].c_str(), _PARAM_);
#define MISLOGERROR2(_PHRASE_,_PARAM1_,_PARAM2_)	MISLOG("sline:%u ERROR %s : "_PHRASE_, line, script[0].c_str(), _PARAM1_, _PARAM2_);



#endif // RY_MISSION_LOG_H

/* End of mission_log.h */





















