/** \file combat_action_simple_dynamic_effect.h
 * <File description>
 *
 * $Id: combat_action_simple_dynamic_effect.h,v 1.8 2004/12/08 13:26:43 besson Exp $
 */



#ifndef RY_COMBAT_ACTION_SIMPLE_DYN_EFFECT_H
#define RY_COMBAT_ACTION_SIMPLE_DYN_EFFECT_H

#include "combat_action.h"
#include "simple_effect.h"


/**
 * Class managing the creation of simple effects with dynamic factor for combat
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CCombatActionDynamicEffect : public CCombatDynamicAction
{
public:
	/// Constructor
	CCombatActionDynamicEffect()
		: _EffectValue(0),_Duration(0),_Family(EFFECT_FAMILIES::Unknown)
	{
		_UsePhraseLatencyAsDuration = false;
	}

	/// Constructor
	CCombatActionDynamicEffect(	const TDataSetRow & actorRowId,
								CCombatPhrase *phrase, 
								NLMISC::TGameCycle duration, 
								EFFECT_FAMILIES::TEffectFamily family)
		: _Duration(duration), 
		_Family(family)
	{
		_CombatPhrase = phrase;
		
		if(TheDataset.isAccessible(actorRowId))
			_ActorRowId = actorRowId;
		else
		{
			nlwarning("<CCombatActionDynamicEffect> invalid data set row passed as actor");
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
	virtual void applyOnEntity( CEntityBase *entity, float succesFactor );

private:
	/// total duration (in ticks)
	NLMISC::TGameCycle		_Duration;

	/// bool indicating if we use the phrase latency duration as duration for the effect, otherwise keep given Duration
	bool					_UsePhraseLatencyAsDuration;

	/// effect family
	EFFECT_FAMILIES::TEffectFamily	_Family;

	/// effect value
	sint32					_EffectValue;
};


#endif // RY_COMBAT_ACTION_SIMPLE_DYN_EFFECT_H

/* End of combat_action_simple_dynamic_effect.h */
