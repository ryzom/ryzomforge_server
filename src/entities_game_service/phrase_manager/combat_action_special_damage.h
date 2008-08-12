/** \file combat_action_special_damage.h
 * <File description>
 *
 * $Id: combat_action_special_damage.h,v 1.6 2004/12/08 13:26:43 besson Exp $
 */



#ifndef RY_COMBAT_ACTION_SPECIAL_DAMAGE_H
#define RY_COMBAT_ACTION_SPECIAL_DAMAGE_H

#include "combat_action.h"
#include "game_share/damage_types.h"

/**
 * Class managing special damage (fire, cold...) for combat
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CCombatActionSpecialDamage : public CCombatDynamicAction
{
public:
	/// Constructor
	CCombatActionSpecialDamage(): CCombatDynamicAction()
	{
	}

	/// Constructor
	CCombatActionSpecialDamage(const TDataSetRow & actorRowId, CCombatPhrase *phrase, DMGTYPE::EDamageType dmgType) : _DamageType(dmgType)
	{
		_CombatPhrase = phrase;
		
		if(TheDataset.isAccessible(actorRowId))
			_ActorRowId = actorRowId;
		else
		{
			nlwarning("<CCombatActionSpecialDamage> invalid data set row passed as actor");
		}
	}

	/// validate the combat action
	virtual bool validate(CCombatPhrase *phrase, std::string &errorCode) { return true; }

	/// apply combat action effects
	virtual void apply(CCombatPhrase *phrase);

private:
	/// apply combat action effects on target
	void applyOnTarget( uint8 targetIndex, CCombatPhrase *phrase);

	// type of damage
	DMGTYPE::EDamageType	_DamageType;
};


#endif // RY_COMBAT_ACTION_SPECIAL_DAMAGE_H

/* End of combat_action_special_damage.h */
