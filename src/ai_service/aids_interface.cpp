/** \file aids_interface.cpp
 *
 * $Id: aids_interface.cpp,v 1.6 2007/03/09 09:56:41 boucher Exp $
 */



#include "stdpch.h"
#include "aids_interface.h"
#include "ai_share/aids_messages.h"

using namespace NLMISC;
using namespace NLNET;
using namespace std;

//---------------------------------------------------------------------------------
// service up and service down callbacks

static void cbServiceUp( const std::string& serviceName, NLNET::TServiceId serviceId, void * )
{
	if (serviceName=="AIDS")
	{
		// send a message to the service to say 'I exist'
		CMsgAIServiceUp().send(serviceId);
		// send messages to say which managers are up and running
	}
}

static void cbServiceDown( const std::string& serviceName, NLNET::TServiceId serviceId, void * )
{
}


//---------------------------------------------------------------------------------
// classic init() and release()
void CAIDSInterface::init()
{
	// register the service up and service down callbacks
	CUnifiedNetwork::getInstance()->setServiceUpCallback("AIDS", cbServiceUp, 0);
	CUnifiedNetwork::getInstance()->setServiceDownCallback( "AIDS", cbServiceDown, 0);
}

void CAIDSInterface::release()
{
}

//---------------------------------------------------------------------------------
// send text messages back to the AIDS
void CAIDSInterface::info(const std::string &s)
{
	string str = string("AIS: %3d: INF: ")+s;
	CMsgAIFeedback(str).send("AIDS");
}

void CAIDSInterface::debug(const std::string &s)
{
	string str = string("AIS: %3d: DBG: ")+s;
	CMsgAIFeedback(str).send("AIDS");
}

void CAIDSInterface::warning(const std::string &s)
{
	string str = string("AIS: %3d: WRN: ")+s;
	CMsgAIFeedback(str).send("AIDS");
}

