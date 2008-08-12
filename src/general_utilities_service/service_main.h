/** \file service_main.h
 *
 * $id$
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
