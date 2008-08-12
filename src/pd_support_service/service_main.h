/** \file service_main.h
 *
 * $Id: service_main.h,v 1.2 2007/05/09 15:33:12 boucher Exp $
 *
 */

#ifndef SERVICE_MAIN_H
#define SERVICE_MAIN_H


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "nel/net/service.h"


//-----------------------------------------------------------------------------
// class CServiceClass 
//-----------------------------------------------------------------------------

class CServiceClass : public NLNET::IService
{
public :
	void init();
	bool update();
	static void tickUpdate();
	void release();
};


//-----------------------------------------------------------------------------
#endif
