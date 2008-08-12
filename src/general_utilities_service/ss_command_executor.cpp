/** \file ss_command_executor.cpp
 *
 * Part of SS (shqrd_script) Module for GUS (general utility service)
 *
 * $id$
 */


//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

// nel
#include "nel/misc/types_nl.h"
#include "nel/misc/common.h"
#include "nel/misc/debug.h"
#include "nel/misc/time_nl.h"
#include "nel/net/unified_network.h"

// game share
#include "game_share/singleton_registry.h"
#include "game_share/utils.h"

// local
#include "ss_command_executor.h"
#include "ss_state_manager.h"
#include "ss_service_comms_manager.h"


//-------------------------------------------------------------------------------------------------
// hooking a tickUpdate() to the service tick update
//-------------------------------------------------------------------------------------------------

class CCommandExecutorServiceSingleton: public IServiceSingleton
{
public:
	void serviceUpdate()
	{
		static NLMISC::TTime lastUpdateTime= NLMISC::CTime::getLocalTime();
		NLMISC::TTime localTime= NLMISC::CTime::getLocalTime();

		uint32 loopCount=0;
		while (localTime-lastUpdateTime>1000)
		{
			lastUpdateTime+= 1000;
			CCommandExecutor::getInstance()->tickUpdate();

			// a bit of a hack to stop us looping indefinitely
			if (++loopCount>=100)
			{
				lastUpdateTime= localTime-1000;
			}
		}
	}
};

static CCommandExecutorServiceSingleton CommandExecutorServiceSingleton;


//-------------------------------------------------------------------------------------------------
// methods CCommandExecutor
//-------------------------------------------------------------------------------------------------

CCommandExecutor::CCommandExecutor() 
{
}

CCommandExecutor* CCommandExecutor::getInstance()
{
	static CCommandExecutor* ptr=NULL;
	if (ptr==NULL)
		ptr= new CCommandExecutor;

	return ptr;
}

void CCommandExecutor::addCommand(NLMISC::CSString command)
{
	NLMISC::CSString time= command.firstWord();
	sint32 i= time.atoi();
	if (i==0 && time!="0")
	{
		// if no time is found then add a '0' to mean run right away
		command= "0 "+command;
	}
	else if (i<0)
	{
		// if a negative time is found then convert to '0' to mean "run right away"
		command= "0 "+command.tailFromFirstWord();
	}
	_Commands.push_back(command);
}

void CCommandExecutor::display() const
{
	// iterate over commands updating remaining time
	for (uint32 i=0;i<_Commands.size();++i)
		nldebug("SS PENDING COMMAND: %s",_Commands[i].c_str());
}

void CCommandExecutor::tickUpdate()
{
	// iterate over commands updating remaining time
	for (uint32 i=0;i<_Commands.size();++i)
	{
		uint32 time= _Commands[i].firstWord().atoi();
		if (time==0)
		{
			// decopose the command from '<time> <service> <command>' format
			NLMISC::CSString command= _Commands[i].tailFromFirstWord();
			NLMISC::CSString service= command.strtok(" \t");

			// mark the command as treated
			_Commands[i].clear();

			// compose and send the command execution message
			CServiceCommsManager::getInstance()->execute(service,command);
		}
		else
		{
			_Commands[i]= NLMISC::toString("%u ",time-1)+_Commands[i].tailFromFirstWord();
		}
	}

	// remove finished commands
	uint32 j=0;
	for (uint32 i=0;i<_Commands.size();++i)
	{
		if (!_Commands[i].empty())
			_Commands[j++]=_Commands[i];
	}
	_Commands.resize(j);

}


//-----------------------------------------------------------------------------
