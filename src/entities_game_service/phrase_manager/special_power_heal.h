/** \file special_power_heal.h
 * Specialized class for heal powers
 *
 * $Id: special_power_heal.h,v 1.6 2005/09/21 13:55:04 diaconu Exp $
 */


#ifndef RYZOM_SPECIAL_POWER_HEAL_H
#define RYZOM_SPECIAL_POWER_HEAL_H

#include "special_power.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"
#include "player_manager/character.h"


/**
 * Specialized class for healing powers
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CSpecialPowerHeal : public CSpecialPower
{
public:
	/// Constructor
	CSpecialPowerHeal(TDataSetRow actorRowId, CSpecialPowerPhrase *phrase, float disableTimeInSeconds, sint32 healValue, float healFactorValue, POWERS::TPowerType powerType)
	:CSpecialPower()
	{
		_AffectedScore = SCORES::hit_points;
		_Phrase = phrase;
		_HealValue = healValue;
		_HealFactorValue = healFactorValue;

		_DisablePowerTime = NLMISC::TGameCycle(disableTimeInSeconds / CTickEventHandler::getGameTimeStep());

		_PowerType = powerType;
		
		if(TheDataset.isAccessible(actorRowId))
		{
			_ActorRowId = actorRowId;
		}
		else
		{
			nlwarning("<CSpecialPowerBalance> invalid data set row passed as actor");
		}
	}

	/// validate the power utilisation
	virtual bool validate(std::string &errorCode);
	
	/// set affected score
	inline void setAffectedScore( SCORES::TScores score ) { _AffectedScore = score; }

	/// apply effects
	virtual void apply();

protected:
	/// affected score (Hp, sap, sta)
	SCORES::TScores	_AffectedScore;
	/// healing value
	sint32			_HealValue;
	/// heal factor value, in % of max HP
	float			_HealFactorValue;
};

#endif // RYZOM_SPECIAL_POWER_HEAL_H

/* End of special_power_heal.h */

