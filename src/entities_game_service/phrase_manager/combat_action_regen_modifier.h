/** \file combat_action_regen_modifier.h
 * <File description>
 *
 * $Id: combat_action_regen_modifier.h,v 1.9 2004/12/08 13:26:43 besson Exp $
 */



#ifndef RY_COMBAT_ACTION_REGEN_MODIFIER_H
#define RY_COMBAT_ACTION_REGEN_MODIFIER_H

#include "combat_action.h"


/**
 * Class managing the creation of regen modifiers effects
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CCombatActionRegenModifier : public CCombatDynamicAction
{
public:
	/// Constructor
	CCombatActionRegenModifier(): _Duration(0)
	{
	}

	/// Constructor
	CCombatActionRegenModifier(	const TDataSetRow & actorRowId, 
								CCombatPhrase *phrase,
								NLMISC::TGameCycle duration,
								SCORES::TScores score,
								EFFECT_FAMILIES::TEffectFamily family)
	: _Duration(duration), _AffectedScore(score), _Family(family)
	{
		_CombatPhrase = phrase;
		
		if(TheDataset.isAccessible(actorRowId))
			_ActorRowId = actorRowId;
		else
		{
			nlwarning("<CCombatActionSlowMove> invalid data set row passed as actor");
		}
	}

	/// validate the combat action
	virtual bool validate(CCombatPhrase *phrase, std::string &errorCode) { return true; }

	/// apply combat action effects
	virtual void apply(CCombatPhrase *phrase);

	/// set the effect name
	inline void effectName(const std::string &str) { _EffectName = str; }
	/// get the effect name
	inline const std::string &effectName() { return _EffectName; }

	/// apply on entity
	virtual void applyOnEntity( CEntityBase *entity, float successFactor );

private:
	/// duration (in ticks)
	NLMISC::TGameCycle				_Duration;

	/// affected score
	SCORES::TScores					_AffectedScore;

	/// effect family
	EFFECT_FAMILIES::TEffectFamily	_Family;

	/// effect code name used to send system messages to clients
	std::string						_EffectName;
	
};


#endif // RY_COMBAT_ACTION_REGEN_MODIFIER_H

/* End of combat_action_regen_modifier.h */
