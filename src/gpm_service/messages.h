/** \file messages.h
 *
 * $Id: messages.h,v 1.4 2007/05/25 09:47:42 verquerre Exp $
 */



#ifndef RY_GPMS_MESSAGES_H
#define RY_GPMS_MESSAGES_H

#include "game_share/msg_gpm_service.h"

class CGPMPlayerPrivilegeInst : public CGPMPlayerPrivilege
{
public:

	virtual void callback (const std::string &name, NLNET::TServiceId id);
};

class CMessages
{
public:
	// singleton initialisation and release
	static void init();
	static void release();

private:
};


#endif // RY_GPMS_MESSAGES_H

