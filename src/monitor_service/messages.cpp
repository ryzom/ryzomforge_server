/** \file messages.cpp
 *
 * $Id: messages.cpp,v 1.3 2007/03/09 09:56:55 boucher Exp $
 */



// include files
#include "stdpch.h"

#include "messages.h"

using namespace NLMISC;
using namespace NLNET;

// ***************************************************************************
// the callback table
// ***************************************************************************

static void cbAddEntities( NLNET::CMessage& msgin, const std::string &serviceName, TServiceId serviceId );

TUnifiedCallbackItem CbArray[] = 
{
	{	"ADDED_ENTITIES",		cbAddEntities,			},
};

// ***************************************************************************
// Messages from the world editor
// ***************************************************************************

//
static void cbAddEntities( NLNET::CMessage& msgin, const std::string &serviceName, TServiceId serviceId )
{
//	This is where we should deal with player record creation
}


