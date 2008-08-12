/** \file sabrina_phrase_manager.cpp
 *
 * $Id: sabrina_phrase_manager.cpp,v 1.3 2004/03/01 19:22:19 lecroart Exp $
 */



/////////////
// INCLUDE 
/////////////
// game_share
#include "game_share/tick_event_handler.h" 
// sabrina
#include "sabrina_phrase_manager.h" 
#include "sabrina_ai_interface.h" 

//////////////////////////
// SINGLETON DATA
//////////////////////////
CSabrinaPhraseManager::TPhraseVector CSabrinaPhraseManager::_PhraseVectors[256];

//--------------------------------------------------------------
//						init()  
//--------------------------------------------------------------
void CSabrinaPhraseManager::init()
{
	CSabrinaAIInterface::init();
}

//--------------------------------------------------------------
//						update()  
//--------------------------------------------------------------
void CSabrinaPhraseManager::update()
{
	// select this game cycle's phrase event vector
	TPhraseVector &vect= _PhraseVectors[(uint8)CTickEventHandler::getGameCycle()];
	for (uint32 i=0;i<vect.size();++i)
	{
		vect[i]->updatePhrase();
	}
	// clear the phrase event vector
	vect.clear();

	CSabrinaAIInterface::flushEvents();
}

//--------------------------------------------------------------
//						release()  
//--------------------------------------------------------------
void CSabrinaPhraseManager::release()
{
	CSabrinaAIInterface::release();
}

//--------------------------------------------------------------
//						setNextPhraseEvent()  
//--------------------------------------------------------------
void CSabrinaPhraseManager::setNextPhraseEvent(CSabrinaPhraseInstance* phrase,NLMISC::TGameCycle nextEventTime)
{
	if (uint32(nextEventTime-CTickEventHandler::getGameCycle())>=256)
	{
		nlwarning("Phrase Event too far in future - truncated from %d to 25.5seconds", nextEventTime-CTickEventHandler::getGameCycle());
		nextEventTime=CTickEventHandler::getGameCycle()+255;
		#ifdef NL_DEBUG
			nlerror("CSabrinaPhraseManager::setNextPhraseEvent(): Invlid nextEventTime parameter");
		#endif
	}
	_PhraseVectors[(uint8)nextEventTime].push_back(phrase);
}

