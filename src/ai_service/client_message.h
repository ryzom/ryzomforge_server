/** \file client_messages.h
 *
 * $Id: client_message.h,v 1.3 2004/03/01 19:19:20 lecroart Exp $
 */




#ifndef CLIENT_MESSAGE_H
#define CLIENT_MESSAGE_H

#include "nel/misc/types_nl.h"

/**
 * class used to handle message from client with the new IOS message forwaeding system
 * \author Boris Boucher
 * \author Nevrax France
 * \date 2002
 */
class CAIClientMessages
{
public:
	static void init();
	static void release();
};


#endif
