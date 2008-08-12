/** This is the main file of the ryzom admin service.
 *
 *	This service can be started as legacy (ie nelns) AS or as AES replacement
 *	by configuring service name and created modules.
 */


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "nel/net/service.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

// force admin module to link in
extern void admin_modules_forceLink();
void foo()
{
	admin_modules_forceLink();
}

//-----------------------------------------------------------------------------
// class CServiceClass 
//-----------------------------------------------------------------------------

class CServiceClass : public NLNET::IService
{
public :
	void init()
	{
	}

	bool update()
	{
		return true;
	}

	void release()
	{
	}
};




//-----------------------------------------------
//	NLNET_SERVICE_MAIN
//-----------------------------------------------

static const char* getCompleteServiceName(const IService* theService)
{
	static std::string s;
	s= "ryzom_admin_service";

	if (theService->haveLongArg("adminname"))
	{
		s+= "_"+theService->getLongArg("adminname");
	}

	if (theService->haveLongArg("fulladminname"))
	{
		s= theService->getLongArg("fulladminname");
	}

	return s.c_str();
}

static const char* getShortServiceName(const IService* theService)
{
	static std::string s;
	s= "RAS";

	if (theService->haveLongArg("shortadminname"))
	{
		s= theService->getLongArg("shortadminname");
	}
	
	return s.c_str();
}

NLNET_SERVICE_MAIN( CServiceClass, getShortServiceName(scn), getCompleteServiceName(scn), 0, EmptyCallbackArray, "", "" );

