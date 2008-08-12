/** \file sabrina_message_callbacks.h
 * <File description>
 *
 * $Id: sabrina_message_callbacks.h,v 1.4 2007/05/25 09:47:42 verquerre Exp $
 */



#ifndef RY_SABRINA_MESSAGE_CALLBACKS_H
#define RY_SABRINA_MESSAGE_CALLBACKS_H

// Misc
#include "nel/misc/types_nl.h"
//
#include "game_share/msg_brick_service.h"

/**
 * Implementation of the phrase execution description Transport class
 */
class CEGSExecuteMsgImp : public CEGSExecuteMsg
{
public:
	virtual void callback (const std::string &name, NLNET::TServiceId id);
};

namespace SABRINA
{

	/// cancel a specified phrase
	void cbCancelPhrase( NLNET::CMessage& msgin, const std::string &serviceName, uint16 serviceId );

	/// cancel the sentence currently executed
	void cbCancelCurrentPhrase( NLNET::CMessage& msgin, const std::string &serviceName, uint16 serviceId );

	/// cancel all sentences of a specified entity
	void cbCancelAllPhrases( NLNET::CMessage& msgin, const std::string &serviceName, uint16 serviceId );

	/// register a service for event reports
	void cbRegisterService( NLNET::CMessage& msgin, const std::string &serviceName, uint16 serviceId );

	/// unregister a service for event reports
	void cbUnregisterService( NLNET::CMessage& msgin, const std::string &serviceName, uint16 serviceId );

	/// register a service for AI event reports
	void cbRegisterServiceAI( NLNET::CMessage& msgin, const std::string &serviceName, uint16 serviceId );

	/// unregister a service for AI event reports
	void cbUnregisterServiceAI( NLNET::CMessage& msgin, const std::string &serviceName, uint16 serviceId );

	/// receive a disengage notification for specified entity (from CMS typically)
	void cbDisengageNotification( NLNET::CMessage& msgin, const std::string &serviceName, uint16 serviceId );

	/// receive a Disengage command
	void cbDisengage( NLNET::CMessage& msgin, const std::string &serviceName, uint16 serviceId );

	/// receive a vision answer
	void cbVisionAnswer( NLNET::CMessage& msgin, const std::string &serviceName, uint16 serviceId );
}

#endif // EGS_PHRASE_MANAGER_CALLBACKS_H

/* End of brick_manager_callbacks.h */
