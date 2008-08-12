/** \file combat_action_stun.h
 * <File description>
 *
 * $Id: combat_action_stun.h,v 1.17 2004/12/08 13:26:43 besson Exp $
 */



#ifndef RY_COMBAT_ACTION_STUN_H
#define RY_COMBAT_ACTION_STUN_H

#include "combat_action.h"
#include "stun_effect.h"


/**
 * <Class description>
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CCombatActionStun : public CCombatAction
{
public:
	/// Constructor
	CCombatActionStun() : _StunDuration(0)
	{}

	/// Constructor
	CCombatActionStun(const TDataSetRow & actorRowId, CCombatPhrase *phrase, NLMISC::TGameCycle duration)
	: _StunDuration(duration)
	{
		_CombatPhrase = phrase;
		if ( TheDataset.isAccessible( actorRowId ) )
			_ActorRowId = actorRowId;
	}

	/// build from an ai action
	virtual bool initFromAiAction( const CStaticAiAction *aiAction, CCombatPhrase *phrase );

	/// validate the combat action
	virtual bool validate(CCombatPhrase *phrase, std::string &errorCode) { return true; }

	/// apply combat action effects
	virtual void apply(CCombatPhrase *phrase);

	/// apply on entity
	virtual void applyOnEntity( CEntityBase *entity, float successFactor );
	
private:
	/// stun duration if no resist (in ticks)
	NLMISC::TGameCycle		_StunDuration;
};


#endif // RY_COMBAT_ACTION_STUN_H

/* End of combat_action_stun.h */
