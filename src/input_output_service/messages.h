 /** \file messages.h
 * Callbacks of the IOS
 *
 * $Id: messages.h,v 1.4 2007/05/09 15:33:10 boucher Exp $
 */



#ifndef RY_OPS_MESSAGES_H
#define RY_OPS_MESSAGES_H

class CMessages
{
public:
	// singleton initialisation and release
	static void init();
	static void release();

private:
};


#endif // RY_OPS_MESSAGES_H

