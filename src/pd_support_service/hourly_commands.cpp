/** \file hourly_commands.cpp
 *
 * $Id: hourly_commands.cpp,v 1.2 2007/05/09 15:33:12 boucher Exp $
 */


#include <time.h>
#include "nel/misc/types_nl.h"
#include "nel/misc/file.h"
#include "nel/misc/path.h"
#include "nel/misc/sstring.h"
#include "nel/net/service.h"
#include "game_share/utils.h"
#include "game_share/singleton_registry.h"
#include "stat_job_manager.h"

NLMISC::CVariable<std::string> HourlyActivityLogFileName("scheduler", "HourlyActivityLogFileName", "log file name for hourly activity logs", "pdss_hourly_activity.log", 0, true);
NLMISC::CVariable<uint32> HourlyTimeInterval("scheduler", "HourlyTimeInterval", "number of seconds in an hour", 60*60, 0, true);
NLMISC::CVariable<uint32> HourlyStartTime("scheduler", "HourlyStartTime", "number of seconds into the hour when hourly tasks should be launched", 15*60, 0, true);

class CHourlyTaskScheduler: public IServiceSingleton
{
public:
	void serviceUpdate()
	{
		static uint32 jobsRemaining=0;

		// if there are jobs still running then just chart progress
		if (jobsRemaining!=0)
		{
			if (CJobManager::getInstance()->getNumJobs() < jobsRemaining)
			{
				nlinfo("JobManager state: %s",CJobManager::getInstance()->getStatus().c_str());
				jobsRemaining= CJobManager::getInstance()->getNumJobs();
			}
			return;
		}
		
		// get the start time
		time_t startTime;
		time( &startTime );

		// if we're too early in the hour then return
		if ( uint32(startTime%HourlyTimeInterval.get()) <= HourlyStartTime )
			return;

		// setup the lastTime corresponding to the last time we ran
		static uint32 lastTime=0;
		if (lastTime==0 && NLMISC::CFile::fileExists(HourlyActivityLogFileName))
		{
			lastTime= NLMISC::CFile::getFileModificationDate(HourlyActivityLogFileName);
		}

		// if we already ran within the last hour then return
		if (startTime/(HourlyTimeInterval) == lastTime/(HourlyTimeInterval))
			return;

		// setup the new lastTime and oldJobsRemaining values
		uint32 oldJobsRemaining= CJobManager::getInstance()->getNumJobs();
		lastTime= startTime;

		// execute hourly tasks
		NLMISC::CConfigFile::CVar *commandsVar = NLNET::IService::getInstance()->ConfigFile.getVarPtr("HourlyCommands");
		WARN_IF(commandsVar  == NULL,"'HourlyCommands' not found in cfg file");
			
		// if we have hourly commands...
		if (commandsVar!=NULL)
		{
			nlinfo("Executing Hourly Commands");
			// iterate over the entries in the commandsVar, executing them 1 by 1
			for (uint i=0; commandsVar!=NULL && i<commandsVar->size(); ++i)
			{
				NLMISC::CSString commandStr= commandsVar->asString(i);
				nlinfo("Executing hourly command: %s",commandStr.strip().c_str());
				NLMISC::ICommand::execute(commandStr.strip(),*NLMISC::InfoLog);
			}
		}

		// if we've started jobs running then update the remaining jobs info
		uint32 newJobsRemaining= CJobManager::getInstance()->getNumJobs();
		if (oldJobsRemaining!=newJobsRemaining)
			jobsRemaining= newJobsRemaining;

		// get the end time
		time_t endTime;
		time( &endTime );

		// determine date info from time info
		tm * ptm;
		ptm = gmtime(&endTime);

		// write to the log file
		FILE* fileHandle= fopen(HourlyActivityLogFileName,"ab");
		nlassert(fileHandle!=NULL);
		fprintf(fileHandle,"%02u/%02u/%u CHourlyTaskScheduler: Started: %02u:%02u, Finished: %02u:%02u, Executed %u commands Started %u Jobs\n",
			ptm->tm_mday, ptm->tm_mon+1, ptm->tm_year+1900, startTime/3600%24, startTime/60%60, endTime/3600%24, endTime/60%60, commandsVar==NULL?0:commandsVar->size(), jobsRemaining );
		nlinfo("JobManager state: %s",CJobManager::getInstance()->getStatus().c_str());
		fclose(fileHandle);
	}
};

static CHourlyTaskScheduler HourlyTaskScheduler;
