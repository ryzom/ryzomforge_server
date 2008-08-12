/** \file messages.h
 *
 * $Id: messages.h,v 1.3 2004/03/01 19:18:37 lecroart Exp $
 */



#ifndef RY_AGST_MESSAGES_H
#define RY_AGST_MESSAGES_H

#include "game_share/msg_brick_service.h"

class CMessages
{
public:
	// singleton initialisation and release
	static void init();
	static void release();

private:
};


#endif // RY_AGST_MESSAGES_H

