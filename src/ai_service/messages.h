/** \file messages.h
 *
 * $Id: messages.h,v 1.7 2007/03/09 09:56:41 boucher Exp $
 */



#ifndef RYAI_MESSAGES_H
#define RYAI_MESSAGES_H

#include "ai_share/aids_messages.h"
#include "ai_share/ais_messages.h"
#include "game_share/pet_interface_msg.h"

class CMessages
{
public:
	// singleton initialisation and release
	static void init();
	static void release();

	/// notify a bot despawn to a service (if requested before)
	static void notifyBotDespawn(NLNET::TServiceId serviceId, uint32 botAlias, const NLMISC::CEntityId& botId);
	static void notifyBotDeath(NLNET::TServiceId serviceId, uint32 botAlias, const NLMISC::CEntityId& botId);	
	static void notifyBotStopNpcControl(NLNET::TServiceId serviceId, uint32 botAlias, const NLMISC::CEntityId& botId);
};

#endif
