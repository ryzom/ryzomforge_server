/** \file sabrina_phrase_manager.h
 *
 * $Id: sabrina_phrase_manager.h,v 1.3 2004/03/01 19:22:19 lecroart Exp $
 */



#ifndef RY_SABRINA_PHRASE_MANAGER_H
#define RY_SABRINA_PHRASE_MANAGER_H

// stl
#include <vector>
// misc
#include "nel/misc/types_nl.h"
// sabrina
#include "sabrina_phrase_instance.h"
#include "sabrina_pointers.h"


/**
 * The Sabrina phrase manager singleton
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CSabrinaPhraseManager
{	
public:
	// singleton init - called in service init
	static void init();

	// update called each tick in service update
	// updates phrases and dispatches events to AI
	static void update();

	// singleton release - called in service release
	static void release();

	// activate a phrase & setup the next event time (time should be >=0 and <256)
	static void setNextPhraseEvent(CSabrinaPhraseInstance* phrase,NLMISC::TGameCycle nextEventTime);

private:
	// this is a singleton so prohibit construction
	CSabrinaPhraseManager();

	typedef std::vector<CSabrinaPhraseInstancePtr> TPhraseVector;
	static TPhraseVector _PhraseVectors[256];
};


#endif 
