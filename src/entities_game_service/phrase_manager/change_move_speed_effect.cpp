/** \file change_move_speed_effect.cpp
 * <File description>
 *
 * $Id: change_move_speed_effect.cpp,v 1.11 2005/02/22 10:22:30 besson Exp $
 */



#include "stdpch.h"
// net
#include "nel/net/message.h"
//
#include "change_move_speed_effect.h"
#include "phrase_manager/phrase_utilities_functions.h"
#include "phrase_manager/effect_factory.h"
#include "entity_manager/entity_base.h"
#include "entity_manager/entity_manager.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

//--------------------------------------------------------------
//		CChangeMoveSpeedEffect::update()
//--------------------------------------------------------------
bool CChangeMoveSpeedEffect::update(CTimerEvent * event, bool applyEffect)
{
	NL_ALLOC_CONTEXT(CMSE_UPD);
	if (!_AffectedEntity)
	{
		_AffectedEntity = CEntityBaseManager::getEntityBasePtr(_TargetRowId);
		if (!_AffectedEntity)
		{
			_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
			return true;
		}
	}

	if (applyEffect)
	{
		_AffectedEntity->getPhysScores().SpeedVariationModifier += _Value;
		
		// for players, add the value each tick, and doesn't reset it at the end
/*		if (_AffectedEntity->getId().getType() == RYZOMID::player)
		{
			_UpdateTimer.setRemaining(1, event);
		}
		// if entity is a creature, only apply the effect at the beginning, and remove it at the end so no more updates
		else
		{
		}
*/	}

	return false;
} // update //

//--------------------------------------------------------------
//		CChangeMoveSpeedEffect::removed()
//--------------------------------------------------------------
void CChangeMoveSpeedEffect::removed()
{
	if (!_AffectedEntity) return;

	// snare
	if ( _Value  < 0)
	{
		
		DEBUGLOG("EFFECT: slow move effect (value %d) ends on entity %s", _Value, _AffectedEntity->getId().toString().c_str());
		
		// restore entity speed
		_AffectedEntity->getPhysScores().SpeedVariationModifier -= _Value;

		// test if an end message should be sent or not
		if (_AffectedEntity->getId().getType() != RYZOMID::player)
		{
			// if entity still slowed, do not send chat messages
			if (_AffectedEntity->getPhysScores().SpeedVariationModifier < 0)
			{
				return;
			}
		}
		else
		{
			const std::vector<CSEffectPtr>& effects = _AffectedEntity->getSEffects();
			for (uint i = 0 ; i < effects.size() ; ++i)
			{
				if (effects[i] && effects[i] != this && (effects[i]->getFamily() == EFFECT_FAMILIES::SlowMove || effects[i]->getFamily() == EFFECT_FAMILIES::CombatMvtSlow) )
					return;
			}
		}
	}
	// speed increase
	else
	{
		// restore entity speed
		_AffectedEntity->getPhysScores().SpeedVariationModifier -= _Value;
	}

	// send end message unless entity is dead
	if ( !_AffectedEntity->isDead())
		sendEffectEndMessages();

} // removed //

CEffectTFactory<CChangeMoveSpeedEffect> *CCombatSnareEffectFactory = new CEffectTFactory<CChangeMoveSpeedEffect>(EFFECT_FAMILIES::CombatMvtSlow);
CEffectTFactory<CChangeMoveSpeedEffect> *CPowerHasteEffectFactory = new CEffectTFactory<CChangeMoveSpeedEffect>(EFFECT_FAMILIES::PowerSpeedingUp);
