/** \file messages.h
 *
 * $Id: messages.h,v 1.2 2004/03/01 19:19:03 lecroart Exp $
 */



#ifndef RYAI_MESSAGES_H
#define RYAI_MESSAGES_H

#include "ai_share/aids_messages.h"
#include "ai_share/ais_messages.h"

class CMessages
{
public:
	// singleton initialisation and release
	static void init();
	static void release();
};


#endif
