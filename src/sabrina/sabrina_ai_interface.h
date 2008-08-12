/** \file sabrina_ai_interface.h
 *
 * $Id: sabrina_ai_interface.h,v 1.3 2004/03/01 19:22:19 lecroart Exp $
 */



#ifndef RY_SABRINA_AI_INTERFACE_H
#define RY_SABRINA_AI_INTERFACE_H

// std
#include <vector>
// misc
#include "nel/misc/types_nl.h"
// game share
#include "game_share/ai_event.h"
#include "game_share/ai_event_report.h"

/**
 * The Sabrina AI Service Interface singleton
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CSabrinaAIInterface
{	
public:
	// init method called at service init by CSabrinaPhraseManager::init()
	static void init();

	// update called each tick by CSabrinaPhraseManager::update() - dispatches events to the AI services
	static void flushEvents();

	// release method called at service release	by CSabrinaPhraseManager::release()
	static void release();

	/**
	 * register a service to the event broadcast for AI
	 * \param serviceName name of the registered service
	 */
	static void registerAIService( uint8 serviceId );

	/**
	 * unregister a service to the event broadcast
	 * \param serviceName name of the service to remove
	 */
	static void unregisterAIService( uint8 serviceId );

	/**
	 * add an AI event report for the current tick
	 * \param report the AI event report to add
	 */
	static void addAiEventReport( const CAiEventReport &report );

	/**
	 * add an AI event for the current tick
	 * \param report the event to add
	 */
	static void addAIEvent( const IAIEvent *event );

private:
	// this is a singleton so prohibit construction
	CSabrinaAIInterface();

	/// list of registered services for Event Broadcast for AI
	static std::vector<uint8>			_RegisteredServices;

	/// the list of ai events
	typedef std::list<IAIEvent*>		TAIEventList;
	static TAIEventList					_AIEvents;

	/// the ai event reports
	static std::vector<CAiEventReport>	_AIEventReports;
};


#endif 
