/** \file combat_action_simple_effect.h
 * <File description>
 *
 * $Id: combat_action_simple_effect.h,v 1.11 2004/12/08 13:26:43 besson Exp $
 */



#ifndef RY_COMBAT_ACTION_SIMPLE_EFFECT_H
#define RY_COMBAT_ACTION_SIMPLE_EFFECT_H

#include "combat_action.h"
#include "simple_effect.h"


/**
 * Class managing the creation of simple effects for combat
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CCombatActionSimpleEffect : public CCombatAction
{
public:
	/// Constructor
	CCombatActionSimpleEffect()
		: _EffectValue(0),_Duration(0),_EffectPower(0),_Family(EFFECT_FAMILIES::Unknown),_Effect(0)
	{
		_UsePhraseLatencyAsDuration = false;
	}

	/// Constructor
	CCombatActionSimpleEffect(	const TDataSetRow & actorRowId,
								CCombatPhrase *phrase, 
								NLMISC::TGameCycle duration, 
								EFFECT_FAMILIES::TEffectFamily family, 
								sint32 value, 
								uint8 power)
		: _EffectValue(value),
		_Duration(duration), 
		_EffectPower(power), 
		_Family(family),
		_Effect(0)
	{
		_CombatPhrase = phrase;
		
		if(TheDataset.isAccessible(actorRowId))
			_ActorRowId = actorRowId;
		else
		{
			nlwarning("<CCombatActionSimpleEffect> invalid data set row passed as actor");
		}

		_UsePhraseLatencyAsDuration = false;
	}

	/// validate the combat action
	inline virtual bool validate(CCombatPhrase *phrase, std::string &errorCode) 
	{ return true; }

	/// apply combat action effects
	virtual void apply(CCombatPhrase *phrase);

	/// set use Phrase Latency as duration flag
	inline void usePhraseLatencyAsDuration(bool b) { _UsePhraseLatencyAsDuration = b; }

	/// apply on entity
	virtual void applyOnEntity( CEntityBase *entity, float successFactor );

private:
	/// total duration (in ticks)
	NLMISC::TGameCycle		_Duration;

	/// bool indicating if we use the phrase latency duration as duration for the effect, otherwise keep given Duration
	bool					_UsePhraseLatencyAsDuration;

	/// effect value
	sint32					_EffectValue;

	/// effect power
	uint8					_EffectPower;

	/// effect family
	EFFECT_FAMILIES::TEffectFamily	_Family;
	
	/// the effect
	CSimpleEffect			*_Effect;
};


#endif // RY_COMBAT_ACTION_SIMPLE_EFFECT_H

/* End of combat_action_simple_effect.h */
