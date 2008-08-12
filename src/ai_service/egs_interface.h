/** \file egs_interface.h
 *
 * $Id: egs_interface.h,v 1.12 2007/03/09 09:56:41 boucher Exp $
 */




#ifndef RYAI_EGS_INTERFACE_H
#define RYAI_EGS_INTERFACE_H

// Include
#include "nel/net/unified_network.h"
#include "nel/misc/types_nl.h"
#include "nel/misc/entity_id.h"
#include "nel/misc/sheet_id.h"

//#include "ai_entity_id.h"


// the class
class CEGSInterface
{
public:
	// classic init(), update() and release()
	static void init();
	static void update();
	static void release();
};


class CAddHandledAIGroupImp : public CAddHandledAIGroupMsg
{
	virtual void callback (const std::string &name, NLNET::TServiceId id);
};

class CDelHandledAIGroupImp : public CDelHandledAIGroupMsg
{
	virtual void callback (const std::string &name, NLNET::TServiceId id);
};

class CCreatureDespawnImp : public CCreatureDespawnMsg
{
	virtual void callback (const std::string &name, NLNET::TServiceId id);
};

class CUserEventMsgImp : public CUserEventMsg
{	
	void callback (const std::string &name, NLNET::TServiceId id);
};

class CSetEscortTeamIdImp : public CSetEscortTeamId
{
	void callback (const std::string &name, NLNET::TServiceId id);
};



#endif
