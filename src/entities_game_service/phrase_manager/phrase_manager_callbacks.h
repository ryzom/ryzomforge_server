/** \file phrase_manager_callbacks.h
 * <File description>
 *
 * $Id: phrase_manager_callbacks.h,v 1.6 2007/03/09 09:56:50 boucher Exp $
 */



#ifndef EGS_PHRASE_MANAGER_CALLBACKS_H
#define EGS_PHRASE_MANAGER_CALLBACKS_H

//
#include "server_share/msg_brick_service.h"

/**
 * Implementation of the phrase execution description Transport class
 */
class CEGSExecuteMsgImp : public CEGSExecuteMsg
{
public:
	virtual void callback (const std::string &name, NLNET::TServiceId sid);
};

/**
 * Implementation of the Ai Action execution description Transport class
 */
class CEGSExecuteAiActionMsgImp : public CEGSExecuteAiActionMsg
{
public:
	virtual void callback(const std::string &serviceName, NLNET::TServiceId sid);
};

/// register a service for event reports
void cbRegisterService( NLNET::CMessage& msgin, const std::string &serviceName, NLNET::TServiceId serviceId );

/// unregister a service for event reports
void cbUnregisterService( NLNET::CMessage& msgin, const std::string &serviceName, NLNET::TServiceId serviceId );

/// register a service for AI event reports
void cbRegisterServiceAI( NLNET::CMessage& msgin, const std::string &serviceName, NLNET::TServiceId serviceId );

/// unregister a service for AI event reports
void cbUnregisterServiceAI( NLNET::CMessage& msgin, const std::string &serviceName, NLNET::TServiceId serviceId );

/// receive a disengage notification for specified entity (from CMS typically)
void cbDisengageNotification( NLNET::CMessage& msgin, const std::string &serviceName, NLNET::TServiceId serviceId );

/// receive a Disengage command
void cbDisengage( NLNET::CMessage& msgin, const std::string &serviceName, NLNET::TServiceId serviceId );

#endif // EGS_PHRASE_MANAGER_CALLBACKS_H

/* End of brick_manager_callbacks.h */
