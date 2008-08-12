/** \file combat_stun_effect.cpp
 * <File description>
 *
 * $Id: combat_stun_effect.cpp,v 1.2 2004/03/01 19:22:18 lecroart Exp $
 */



#include "stdpch.h"
// net
#include "nel/net/message.h"
//
#include "combat_stun_effect.h"
#include "phrase_utilities_functions.h"

#include "entity_base.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;


//--------------------------------------------------------------
//		CEntityPhrases::cancelTopSentence()
//--------------------------------------------------------------
bool CCombatStunEffect::isTimeToUpdate()
{
	return (_StunEndDate <= CTickEventHandler::getGameCycle());
} // isTimeToUpdate //

//--------------------------------------------------------------
//		CEntityPhrases::cancelTopSentence()
//--------------------------------------------------------------
bool CCombatStunEffect::update( uint32 & updateFlag )
{
	// always return true as the test is made in isTimeToUpdate
	return true;
} // update //

//--------------------------------------------------------------
//		CEntityPhrases::cancelTopSentence()
//--------------------------------------------------------------
void CCombatStunEffect::removed()
{
	if (!_StunnedEntity) return;

	// wake entity
	_StunnedEntity->wake();

	// send message
	PHRASE_UTILITIES::sendSimpleMessage( _TargetRowId, "OPS_EFFECT_STUN_END" );
	PHRASE_UTILITIES::sendMessage( _CreatorRowId, "OPS_EFFECT_STUN_END_E", _TargetRowId );
} // removed //

