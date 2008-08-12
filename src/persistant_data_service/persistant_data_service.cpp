/** \file persistant_data_service.cpp
 * <File description>
 *
 * $Id: persistant_data_service.cpp,v 1.5 2006/05/31 12:15:01 boucher Exp $
 */

#include "persistant_data_service.h"

#include "db_manager.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

//-----------------------------------------------
//	callback table for input message 
//
//-----------------------------------------------
TUnifiedCallbackItem CbArray[] =
{
	{ "",	NULL },
};


/*
 * Constructor
 */
CPersistantDataService::CPersistantDataService()
{
}


//-----------------------------------------------
//	NLNET_SERVICE_MAIN
//-----------------------------------------------
NLNET_SERVICE_MAIN( CPersistantDataService, "PDS", "persistant_data_service", 0, CbArray, "", "" );





/*
 * Initialization
 */
void	CPersistantDataService::init()
{
//	RY_PDS::CPDStringManager	sm;

//	sm.addString(CEntityId(12, 0), string(""));
//	sm.stringExists(string(""), 12);

	CDbManager::init();
}


/*
 * Release
 */
void	CPersistantDataService::release()
{
	CDbManager::release();
}




/*
 * Update
 */
bool	CPersistantDataService::update()
{
	if (!CDbManager::update())
		return false;

	return true;
}
