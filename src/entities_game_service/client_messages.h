/** \file client_messages.h
 * <File description>
 *
 * $Id: client_messages.h,v 1.4 2004/12/08 13:26:42 besson Exp $
 */



#ifndef RY_EGS_CLIENT_MESSAGES_H
#define RY_EGS_CLIENT_MESSAGES_H



/**
 * class used to handle message from client with the new IOS message forwaeding system
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2002
 */
class CClientMessages
{
public:
	static void init();
	static void release();
};


#endif // RY_EGS_CLIENT_MESSAGES_H

/* End of client_messages.h */
