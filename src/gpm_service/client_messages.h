/** \file client_messages.h
 *
 * $Id: client_messages.h,v 1.2 2004/03/01 19:22:05 lecroart Exp $
 */



#ifndef RY_GPMS_CLIENT_MESSAGES_H
#define RY_GPMS_CLIENT_MESSAGES_H

class CClientMessages
{
public:
	// singleton initialisation and release
	static void init();
	static void release();

private:
};


#endif // RY_GPMS_CLIENT_MESSAGES_H

