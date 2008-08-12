/** \file combat_action_bleed.h
 * <File description>
 *
 * $Id: combat_action_bleed.h,v 1.14 2004/12/08 13:26:43 besson Exp $
 */



#ifndef RY_COMBAT_ACTION_BLEED_H
#define RY_COMBAT_ACTION_BLEED_H

#include "combat_action.h"
#include "bleed_effect.h"


/**
 * Class managing the creation of bleed effects for combat (nb: combat bleed effects stacks)
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CCombatActionBleed : public CCombatDynamicAction
{
public:
	/// Constructor
	CCombatActionBleed(): CCombatDynamicAction(), _BleedDuration(0), _BleedCycleDuration(0)
	{
	}

	/// Constructor
	CCombatActionBleed(const TDataSetRow & actorRowId, CCombatPhrase *phrase, NLMISC::TGameCycle totalDuration, NLMISC::TGameCycle cycleDuration)
	: _BleedDuration(totalDuration), _BleedCycleDuration(cycleDuration)
	{
		_CombatPhrase = phrase;
		
		if(TheDataset.isAccessible(actorRowId))
			_ActorRowId = actorRowId;
		else
		{
			nlwarning("<CCombatActionBleed> invalid data set row passed as actor");
		}
	}

	/// validate the combat action
	virtual bool validate(CCombatPhrase *phrase, std::string &errorCode) { return true; }

	/// apply combat action effects
	virtual void apply(CCombatPhrase *phrase);

	/// apply on entity
	virtual void applyOnEntity( CEntityBase *entity, float successFactor );

private:
	/// apply combat action effects on target
	void applyOnTarget( uint8 targetIndex, CCombatPhrase *phrase);

	/// bleed total duration (in ticks)
	NLMISC::TGameCycle		_BleedDuration;

	/// time between two hp loss (in ticks)
	NLMISC::TGameCycle		_BleedCycleDuration;

	// temp vars
	mutable sint32			_TotalBleedDamage;
	mutable float			_CycleDamage;
};


#endif // RY_COMBAT_ACTION_BLEED_H

/* End of combat_action_bled.h */
