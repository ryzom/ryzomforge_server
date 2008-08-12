/** \file aids_interface.h
 *
 * $Id: aids_interface.h,v 1.3 2004/03/01 19:19:20 lecroart Exp $
 */




#ifndef RYAI_BOT_CHAT_INTERFACE_H
#define RYAI_AIDS_INTERFACE_H

// Nel Misc
#include "nel/misc/types_nl.h"
#include "nel/misc/entity_id.h"
#include "game_share/news_types.h"
#include "game_share/bot_chat_types.h"

// the class
class CAIDSInterface
{
public:
	// classic init() and release()
	static void init();
	static void release();

	// send text messages back to the AIDS
	static void info(const std::string &s);
	static void debug(const std::string &s);
	static void warning(const std::string &s);
};

#endif
