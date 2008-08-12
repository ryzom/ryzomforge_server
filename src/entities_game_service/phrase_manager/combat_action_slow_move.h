/** \file combat_action_slow_move.h
 * <File description>
 *
 * $Id: combat_action_slow_move.h,v 1.11 2004/12/08 13:26:43 besson Exp $
 */



#ifndef RY_COMBAT_ACTION_SLOW_MOVE_H
#define RY_COMBAT_ACTION_SLOW_MOVE_H

#include "combat_action.h"


/**
 * Class managing the creation of slow move effects for combat
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CCombatActionSlowMove : public CCombatAction
{
public:
	/// Constructor
	CCombatActionSlowMove(): _Duration(0), _SpeedModifier(0)
	{
	}

	/// Constructor
	CCombatActionSlowMove(const TDataSetRow & actorRowId, CCombatPhrase *phrase, NLMISC::TGameCycle duration, sint16 speedModifier)
	: _Duration(duration), _SpeedModifier(speedModifier)
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

	/// apply on entity
	virtual void applyOnEntity( CEntityBase *entity, float successFactor );

private:	
	/// bleed total duration (in ticks)
	NLMISC::TGameCycle			_Duration;
	/// speed modifier
	sint16						_SpeedModifier;
};


#endif // RY_COMBAT_ACTION_SLOW_MOVE_H

/* End of combat_action_slow_move.h */
