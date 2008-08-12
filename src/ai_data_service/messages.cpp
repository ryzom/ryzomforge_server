/** \file messages.cpp
 *
 * $Id: messages.cpp,v 1.5 2007/06/14 16:20:06 cado Exp $
 */



// include files
#include "nel/misc/types_nl.h"

#include "messages.h"
//#include "actor_manager.h"

using namespace NLMISC;
using namespace NLNET;


//-------------------------------------------------------------------------
// singleton initialisation and release

void CMessages::init()
{
	// incoming messages
	TRANSPORT_CLASS_REGISTER( CMsgAIServiceUp );
	TRANSPORT_CLASS_REGISTER( CMsgAIManagerUp );
	TRANSPORT_CLASS_REGISTER( CMsgAIFeedback );

	TRANSPORT_CLASS_REGISTER( CMsgAICloseMgrs );
	TRANSPORT_CLASS_REGISTER( CMsgAIBackupMgrs );
}

void CMessages::release()
{
}


//-------------------------------------------------------------------------
// incoming message callbacks

void CMsgAIServiceUp::callback (const std::string &serviceName, NLNET::TServiceId sid)
{
	nlinfo("AI Service Up: %02d (CPU rating: %f  RAMrating %f)", sid.get(), ProcessorAllocation,RamAllocation);
	for (uint i=0;i<ManagersRunning.size();i++)
		nlinfo("-- Running Manager: %04d",ManagersRunning[i]);
}

void CMsgAIManagerUp::callback (const std::string &serviceName, NLNET::TServiceId sid)
{
	nlinfo("Service %d: Manager Up: %04d",sid.get(), MgrId);
}

void CMsgAIFeedback::callback (const std::string &serviceName, NLNET::TServiceId sid)
{
	nlinfo("AI Manager %d: %s",Message.c_str());
}

//-------------------------------------------------------------------------
// stub outgoing message callbacks

void CMsgAICloseMgrs::callback(const std::string &serviceName, NLNET::TServiceId sid) {}
void CMsgAIBackupMgrs::callback(const std::string &serviceName, NLNET::TServiceId sid) {}

