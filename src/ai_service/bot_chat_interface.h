/** \file bot_chat_interface.h
 *
 * $Id: bot_chat_interface.h,v 1.4 2004/03/01 19:19:20 lecroart Exp $
 */



#error "Deprecated"

#ifndef RYAI_BOT_CHAT_INTERFACE_H
#define RYAI_BOT_CHAT_INTERFACE_H

// Nel Misc
#include "nel/misc/types_nl.h"
#include "nel/misc/entity_id.h"
#include "game_share/news_types.h"
#include "game_share/bot_chat_types.h"

// the class
class CBotChatInterface
{
public:
	// the callback type for user callbacks for start of bot chat
	// returns the name of the bot chat automaton to use
	// if an empty string is returned no bot chat is launched
	typedef std::string (*TCallbackBegin)(NLMISC::CEntityId player,NLMISC::CEntityId bot);

	// the callback types for user callback for end of bot chat
	// called just after the chat session has been closed
	typedef void (*TCallbackEnd)(NLMISC::CEntityId player,NLMISC::CEntityId bot);

public:
	// classic init() and release()
	static void init(TCallbackBegin cbBegin=NULL,TCallbackEnd cbEnd=NULL);
	static void release();

	// build a vector of the players currently chatting with a given bot
	// this routine may not be very fast as the entire bot chat map is
	// parsed in order to build the vector
	static void getBotChatPartners(NLMISC::CEntityId bot,std::vector<NLMISC::CEntityId> &result);

	// routines to force the end of a bot chat
	static void endChatForPlayer(NLMISC::CEntityId player);
	static void endAllChatForBot(NLMISC::CEntityId bot);
};

#endif
