/** \file ss_service_comms_manager.h
 *
 * Part of SS (shqrd_script) Module for GUS (general utility service)
 *
 * $id$
 */


#ifndef SS_SERVICE_COMMS_MANAGER_H
#define SS_SERVICE_COMMS_MANAGER_H

//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

// nel
#include "nel/misc/types_nl.h"
#include "nel/net/message.h"

// game_share
#include "game_share/singleton_registry.h"


//-------------------------------------------------------------------------------------------------
// class CServiceCommsManager
//-------------------------------------------------------------------------------------------------

class CServiceCommsManager
{
public:
	// singleton accessor
	static CServiceCommsManager* getInstance();

public:
	// execute a command line or variable modification request
	// note that during treatment of serviceUp the '#' token is a valid
	// service id - it represents the service that has just appeared
	virtual void execute(const std::string& serviceNameWildcard,const std::string& cmdLine)=0;

	// display the state of the singleton (list the connected services etc)
	virtual void display(NLMISC::CLog* log=NLMISC::InfoLog)=0;
};


//-------------------------------------------------------------------------------------------------
#endif
