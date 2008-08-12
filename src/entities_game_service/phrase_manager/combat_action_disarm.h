/** \file combat_action_disarm.h
 * <File description>
 *
 * $Id: combat_action_disarm.h,v 1.4 2004/12/08 13:26:43 besson Exp $
 */



#ifndef RY_COMBAT_ACTION_DISARM_H
#define RY_COMBAT_ACTION_DISARM_H

#include "combat_action.h"

class CCombatPhrase;

class CCombatActionDisarm : public CCombatAction
{
public:
	CCombatActionDisarm()
	{
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

private:
	/// pointer on acting entity
	CEntityBaseRefPtr	_ActingEntity;

};


#endif // RY_COMBAT_ACTION_DISARM_H

/* End of combat_action_disarm.h */





















