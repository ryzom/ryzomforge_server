/** \file damage_aura_effect.cpp
 * <File description>
 *
 * $Id: damage_aura_effect.cpp,v 1.22 2005/05/03 16:49:37 fleury Exp $
 */



#include "stdpch.h"
// net
#include "nel/net/message.h"
//
#include "damage_aura_effect.h"
#include "phrase_manager/phrase_utilities_functions.h"

#include "entity_manager/entity_manager.h"
#include "entity_manager/entity_base.h"
#include "player_manager/character.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"
#include "range_selector.h"
#include "phrase_manager/effect_factory.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

extern CPlayerManager PlayerManager;


//--------------------------------------------------------------
//		CDamageAuraEffect::update()
//--------------------------------------------------------------
bool CDamageAuraEffect::update(CTimerEvent * event, bool applyEffect)
{
	const TGameCycle time = CTickEventHandler::getGameCycle();

	if (!_AffectedEntity)
		_AffectedEntity = CEntityBaseManager::getEntityBasePtr(_TargetRowId);

	if (!_AffectedEntity)
	{
		_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
		return true;
	}

	// if main entity is being teleported, do not apply effect
	if (applyEffect && _AffectedEntity->getId().getType() == RYZOMID::player)
	{
		CCharacter *player = dynamic_cast<CCharacter*> (&(*_AffectedEntity));
		if (player && player->teleportInProgress())
		{
			applyEffect = false;
		}
	}
	
	if (applyEffect)
	{
		// get entities in surrouding area
		CRangeSelector entitiesSelector;
		entitiesSelector.buildDisc( CEntityBaseManager::getEntityBasePtr(getCreatorRowId()), _AffectedEntity->getX(), _AffectedEntity->getY(), _AuraRadius, EntityMatrix, true );
		
		// create or update effect on entities returned
		const vector<CEntityBase*> &entities = entitiesSelector.getEntities();
		const uint size = entities.size();
		for (uint i = 0; i < size ; ++i)
		{
			if (entities[i] && (entities[i] != (CEntityBase*)_AffectedEntity) && isEntityValidTarget(entities[i]) )
			{
				CEntityBase *entity = entities[i];

				SM_STATIC_PARAMS_2(params, STRING_MANAGER::entity, STRING_MANAGER::integer);
				// send messages
				// to victim
				if (entity->getId().getType() == RYZOMID::player)
				{
					params[0].setEIdAIAlias( _AffectedEntity->getId(), CAIAliasTranslator::getInstance()->getAIAlias(_AffectedEntity->getId()) );
					params[1].Int = _CycleDamage;
					PHRASE_UTILITIES::sendDynamicSystemMessage( entity->getEntityRowId(), "EFFECT_STENCH_LOSE_HP", params);
				}
				// to stinking entity
				if (_AffectedEntity->getId().getType() == RYZOMID::player)
				{
					params[0].setEIdAIAlias( entity->getId(), CAIAliasTranslator::getInstance()->getAIAlias(entity->getId()) );
					params[1].Int = _CycleDamage;
					PHRASE_UTILITIES::sendDynamicSystemMessage( _TargetRowId, "EFFECT_STENCH_LOSE_HP_ACTOR", params);
				}
				
				// remove HP
				if (entity->changeCurrentHp( -sint32(_CycleDamage), _TargetRowId))
				{
					// killed entity, so this effect and all other effects have been cleared send kill message and return true
					PHRASE_UTILITIES::sendDeathMessages( _TargetRowId, entity->getEntityRowId());
					//_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
					//return true;
				}
			}
		}
	}

	// set timer next event
	_UpdateTimer.setRemaining(_CycleLength, event);
	
	return false;
} // update //

//--------------------------------------------------------------
//		CDamageAuraEffect::removed()
//--------------------------------------------------------------
void CDamageAuraEffect::removed()
{
	if (!_AffectedEntity) return;

	// if entity is dead, do not send messages
	if (_AffectedEntity->isDead())
		return;

	DEBUGLOG("COMBAT EFFECT: Damage aura effect ends on entity %s", _AffectedEntity->getId().toString().c_str());
	
	sendEffectEndMessages();
} // removed //

//--------------------------------------------------------------
//		CDamageAuraEffect::removed()
//--------------------------------------------------------------
bool CDamageAuraEffect::isEntityValidTarget(CEntityBase *entity) const
{
#ifdef NL_DEBUG
	nlassert(entity);
#endif

	if (entity->isDead())
		return false;

	bool retValue;

	if (entity->getId().getType() == RYZOMID::player)
		retValue = _AffectPlayers;
	else if (_AffectAttackableEntities && entity->getContextualProperty().getValue().attackable() )
		retValue = true;
//	else if ( !_AffectAttackableEntities && !entity->getContextualProperty().getValue().attackable() )
//		retValue = true;
	else
		retValue = false;

	if (retValue)
	{
		// check entity isn't invulnerable
		CSEffect *effect = entity->lookForActiveEffect( EFFECT_FAMILIES::PowerInvulnerability);
		if (effect != NULL)
			retValue = false;
		else if (entity->lookForActiveEffect( EFFECT_FAMILIES::Invincibility) != NULL)
			retValue = false;
	}

	return retValue;
} // checkTargetValidity //

