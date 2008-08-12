/** \file combat_bleed_effect.cpp
 * <File description>
 *
 * $Id: combat_bleed_effect.cpp,v 1.8 2005/02/22 10:22:30 besson Exp $
 */



#include "stdpch.h"
// net
#include "nel/net/message.h"
//
#include "combat_bleed_effect.h"
#include "phrase_manager/phrase_utilities_functions.h"

#include "entity_manager/entity_base.h"
#include "player_manager/character.h"
#include "player_manager/player_manager.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

extern CPlayerManager PlayerManager;


//--------------------------------------------------------------
//		CCombatBleedEffect::isTimeToUpdate()
//--------------------------------------------------------------
bool CCombatBleedEffect::isTimeToUpdate()
{
	const TGameCycle time = CTickEventHandler::getGameCycle();
	return (_NextCycleDate <= time || _BleedEndDate <= time);
} // isTimeToUpdate //

//--------------------------------------------------------------
//		CCombatBleedEffect::update()
//--------------------------------------------------------------
bool CCombatBleedEffect::update( uint32 & updateFlag )
{
	const TGameCycle time = CTickEventHandler::getGameCycle();

	if (_NextCycleDate <= time)
	{
		_NextCycleDate = time + _CycleLength;
		
		// remove hp
		if (_BleedingEntity)
		{
			_BleedingEntity->changeCurrentHp( (-1) * _CycleDamage, _CreatorRowId);

			// send messages
			// to target
			if (_BleedingEntity->getId().getType() == RYZOMID::player)
			{
				SM_STATIC_PARAMS_1(params, STRING_MANAGER::integer)
				params[0].Int = _CycleDamage;
				PHRASE_UTILITIES::sendDynamicSystemMessage( _BleedingEntity->getEntityRowId(), "EFFECT_BLEED_LOSE_HP", params);
			}
			// to actor
			if ( _CreatorRowId != _TargetRowId && TheDataset.isAccessible(_CreatorRowId))
			{
				CCharacter *actor = PlayerManager.getChar(_CreatorRowId);
				if (actor != NULL)
				{
					SM_STATIC_PARAMS_2(params, STRING_MANAGER::entity, STRING_MANAGER::integer)
					params[0].EId = _BleedingEntity->getId();
					params[1].Int = _CycleDamage;
					PHRASE_UTILITIES::sendDynamicSystemMessage( actor->getEntityRowId(), "EFFECT_BLEED_LOSE_HP_ACTOR", params);
				}
			}
		}
	}

	return (_BleedEndDate <= time);
} // update //

//--------------------------------------------------------------
//		CCombatBleedEffect::removed()
//--------------------------------------------------------------
void CCombatBleedEffect::removed()
{
	if (!_BleedingEntity) return;

	// if entity is dead, do not send messages
	if (_BleedingEntity->isDead())
		return;

	DEBUGLOG("COMBAT EFFECT: Bleed effect ends on entity %s", _BleedingEntity->getId().toString().c_str());
	
	// send messages to target
	if (_BleedingEntity->getId().getType() == RYZOMID::player)
		PHRASE_UTILITIES::sendDynamicSystemMessage( _BleedingEntity->getEntityRowId(), "EFFECT_BLEED_ENDED");

	// try to inform actor
	if ( _CreatorRowId != _TargetRowId && TheDataset.isAccessible(_CreatorRowId))
	{
		CCharacter *actor = PlayerManager.getChar(_CreatorRowId);
		if (actor != NULL)
		{
			SM_STATIC_PARAMS_1(params, STRING_MANAGER::entity)
			params[0].EId = _BleedingEntity->getId();
			PHRASE_UTILITIES::sendDynamicSystemMessage( actor->getEntityRowId(), "EFFECT_BLEED_ENDED_ACTOR", params);
		}
	}

} // removed //

