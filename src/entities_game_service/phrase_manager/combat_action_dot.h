/** \file combat_action_dot.h
 * <File description>
 *
 * $Id: combat_action_dot.h,v 1.6 2004/12/08 13:26:43 besson Exp $
 */



#ifndef RY_COMBAT_ACTION_DOT_H
#define RY_COMBAT_ACTION_DOT_H


#include "combat_action.h"
#include "game_share/effect_families.h"
#include "game_share/damage_types.h"
#include "game_share/scores.h"

class CCombatPhrase;

class CCombatActionDoT : public CCombatAction
{
public:
	CCombatActionDoT()
	{
		_EffectDuration = 0;
	}

	/// build from an ai action
	virtual bool initFromAiAction( const CStaticAiAction *aiAction, CCombatPhrase *phrase );

	// validate
	virtual bool validate(CCombatPhrase * phrase, std::string &errorCode) 
	{ return true; }

	// apply
	virtual void apply(CCombatPhrase *phrase);

	/// apply on entity
	virtual void applyOnEntity( CEntityBase *entity, float successFactor );
protected:	
	/// apply combat action effects on target
	void applyOnTarget( uint8 targetIndex, CCombatPhrase *phrase);

protected:
	/// effect family
	EFFECT_FAMILIES::TEffectFamily _EffectFamily;
	/// effect duration
	NLMISC::TGameCycle		_EffectDuration;
	/// UpdateFrequency
	NLMISC::TGameCycle		_UpdateFrequency;
	/// Affected score
	SCORES::TScores			_AffectedScore;
	/// effect param value
	sint32					_TotalDamageValue;
	/// damage type
	DMGTYPE::EDamageType	_DamageType;
};


#endif // RY_COMBAT_ACTION_DOT_H

/* End of combat_action_dot.h */





















