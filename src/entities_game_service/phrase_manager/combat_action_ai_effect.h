/** \file combat_action_ai_effect.h
 * <File description>
 *
 * $Id: combat_action_ai_effect.h,v 1.8 2004/12/08 13:26:43 besson Exp $
 */



#ifndef RY_COMBAT_ACTION_AI_EFFECT_H
#define RY_COMBAT_ACTION_AI_EFFECT_H

#include "combat_action.h"

class CCombatPhrase;

class CCombatAiActionEffect : public CCombatAction
{
public:
	CCombatAiActionEffect()
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
	/// effect duration
	NLMISC::TGameCycle	_EffectDuration;
	/// effect family
	EFFECT_FAMILIES::TEffectFamily _EffectFamily;
	/// effect param value
	sint32				_ParamValue;
};


#endif // RY_COMBAT_ACTION_AI_EFFECT_H

/* End of combat_action_ai_effect.h */
