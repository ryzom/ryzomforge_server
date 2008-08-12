/** \file death_penalties.h
* <File description>
*
* $Id: death_penalties.h,v 1.17 2007/05/04 16:51:52 coutelas Exp $
*/

#ifndef RY_DEATH_PENALTIES_H
#define RY_DEATH_PENALTIES_H

#include "egs_variables.h"
#include "game_share/persistent_data.h"
#include "game_share/skills.h"

#include "game_share/timer.h"


class CCharacter;

/**
 * properties to manage death penalties
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CDeathPenalties
{
	NL_INSTANCE_COUNTER_DECL(CDeathPenalties);
public:

	// Start by declaring methods for persistent load/ save operations
	// The following macro is defined in persistent_data.h
	// At time of writing it evaluated to:
	//	void store(CPersistentDataRecord &pdr) const;
	//	void apply(CPersistentDataRecord &pdr);

	DECLARE_PERSISTENCE_METHODS

	CDeathPenalties()
		:_NbDeath(0),_CurrentDeathXP(0.0),_DeathXPToGain(0.0),_BonusUpdateTime(0),_DeathPenaltyFactor(1.0f){}
	
	void clear()
	{
		_NbDeath = 0;
		_CurrentDeathXP = 0.0;
		_DeathXPToGain = 0.0;
		_BonusUpdateTime = 0;
	}

	void reset(CCharacter& user)
	{
		clear();
		updataDb(user);
	}

	void addDeath(CCharacter& user, float deathPenaltyFactor);
	
	uint32 updateResorption( CCharacter& user );
	
	void addXP( CCharacter& user, SKILLS::ESkills usedSkill, double & xp );
	
	void addXP( CCharacter& user, SKILLS::ESkills usedSkill, double & xp, double xpRaw );
		
	void serial( NLMISC::IStream & f )
	{
		f.xmlPush("death_penalties");
			f.xmlPush("nb_death");
				f.serial(_NbDeath);
			f.xmlPop();
			f.xmlPush("current_death_xp");
				f.serial(_CurrentDeathXP);
			f.xmlPop();
			f.xmlPush("death_xp_to_gain");
				f.serial(_DeathXPToGain);
			f.xmlPop();
			f.xmlPush("bonus_update_time");
				f.serial(_BonusUpdateTime);
			f.xmlPop();
		f.xmlPush("nb_death");
	}

	void updataDb(CCharacter& user);

	bool isNull() const { return (_NbDeath == 0); }

private:
	/// number of death of the player ( reset when there is no more XP malus )
	uint8							_NbDeath;
	/// XP gained to recover from death
	double							_CurrentDeathXP;
	/// XP to gain to recover from death malus
	double							_DeathXPToGain;
	/// Last time at which bonus was given
	uint32							_BonusUpdateTime;
	/// factor of xp used for death penalty
	float							_DeathPenaltyFactor;
};

class CDeathPenaltiesTimerEvent:public CTimerEvent
{
public:
	CDeathPenaltiesTimerEvent(CCharacter *parent);
	void timerCallback(CTimer *owner);
private:
	CCharacter *_Parent;
};

#endif // RY_DEATH_PENALTIES_H

/* End of death_penalties.h */
