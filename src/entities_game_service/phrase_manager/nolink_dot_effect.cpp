/** \file nolink_dot_effect.cpp
 * <File description>
 *
 * $Id: nolink_dot_effect.cpp,v 1.19 2005/08/03 15:01:24 saffray Exp $
 */



#include "stdpch.h"
// net
#include "nel/net/message.h"
//
#include "nolink_dot_effect.h"
#include "phrase_manager/phrase_utilities_functions.h"

#include "entity_manager/entity_base.h"
#include "player_manager/character.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

extern CPlayerManager PlayerManager;


//--------------------------------------------------------------
//		CNoLinkDOTEffect::update()
//--------------------------------------------------------------
bool CNoLinkDOTEffect::update(CTimerEvent * event, bool applyEffect)
{
	// if needed check if caster is dead
	if (_EndsAtCasterDeath)
	{
		const CEntityBase *caster = CEntityBaseManager::getEntityBasePtr(_CreatorRowId);
		if ( !caster || caster->isDead())
		{
			_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
			return true;
		}
	}

	CEntityBase	*targetEntity = CEntityBaseManager::getEntityBasePtr(_TargetRowId);
	if (targetEntity == NULL)
	{
		_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
		return true;
	}
	
	if (applyEffect)
	{
		sint32 maxDamage = sint32(_CycleDamage);
		_RemainingDamage += (float)fabs(_CycleDamage - float(maxDamage));

		if (_RemainingDamage >= 1.0f)
		{
			_RemainingDamage -= 1.0f;
			++maxDamage;
		}

		sint32 realDamage;

		bool kill = false;
		switch(_AffectedScore)
		{ 
		case SCORES::hit_points:
			realDamage = targetEntity->applyDamageOnArmor( _DamageType, maxDamage );
			kill = targetEntity->changeCurrentHp( -realDamage, _CreatorRowId);
			break;
		default:
			realDamage = targetEntity->applyDamageOnArmor( _DamageType, maxDamage );
			targetEntity->changeScore(_AffectedScore, -realDamage);
			return true;
		}

		if (targetEntity != NULL && _CreatorRowId.isValid() && TheDataset.isDataSetRowStillValid(_CreatorRowId))
			PHRASE_UTILITIES::sendScoreModifierSpellMessage( TheDataset.getEntityId(_CreatorRowId), targetEntity->getId(), -realDamage, -maxDamage, SCORES::hit_points , ACTNATURE::OFFENSIVE_MAGIC);

		if (kill)
		{
			PHRASE_UTILITIES::sendDeathMessages(_CreatorRowId,_TargetRowId);
			_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
			return true;
		}
	}

	// set timer next event
	_UpdateTimer.setRemaining(_CycleLength, event);
	
	return false;
} // update //

//--------------------------------------------------------------
//		CNoLinkDOTEffect::removed()
//--------------------------------------------------------------
void CNoLinkDOTEffect::removed()
{
	CEntityBase	*targetEntity = CEntityBaseManager::getEntityBasePtr(_TargetRowId);
	if (targetEntity == NULL)
	{
		return;
	}

	// if entity is dead, do not send messages
	if (targetEntity->isDead())
		return;

	DEBUGLOG("EFFECT: DoT effect ends on entity %s", targetEntity->getId().toString().c_str());
	
	// send messages to target
/*	if (_TargetEntity->getId().getType() == RYZOMID::player)
		PHRASE_UTILITIES::sendDynamicSystemMessage( _TargetRowId, "EFFECT_BLEED_ENDED");

	// try to inform actor
	if ( _CreatorRowId != _TargetRowId && _CreatorRowId.isValid() && TheDataset.isDataSetRowStillValid(_CreatorRowId))
	{
		CCharacter *actor = PlayerManager.getChar(_CreatorRowId);
		if (actor != NULL)
		{
			TVectorParamCheck params;
			params.resize(1);
			params[0].Type = STRING_MANAGER::entity;
			params[0].EId = _TargetEntity->getId();
			PHRASE_UTILITIES::sendDynamicSystemMessage( actor->getEntityRowId(), "EFFECT_BLEED_ENDED_ACTOR", params);
		}
	}
*/
} // removed //
