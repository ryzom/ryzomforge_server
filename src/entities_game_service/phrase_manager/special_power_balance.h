/** \file special_power_balance.h
 * 
 *
 * $Id: special_power_balance.h,v 1.5 2004/12/08 13:26:44 besson Exp $
 */


#ifndef RYZOM_SPECIAL_POWER_BALANCE_H
#define RYZOM_SPECIAL_POWER_BALANCE_H

#include "special_power.h"


/**
 * Specialized class for balance powers
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CSpecialPowerBalance : public CSpecialPower
{
public:
	/// Constructor
	CSpecialPowerBalance(TDataSetRow actorRowId, CSpecialPowerPhrase *phrase, float disableTimeInSeconds, float lossFactor, float range, POWERS::TPowerType powerType)
	:CSpecialPower()
	{
		_AffectedScore = SCORES::hit_points;
		_Phrase = phrase;
		_LossFactor = lossFactor;
		_Range = range;
		_DisablePowerTime = NLMISC::TGameCycle(disableTimeInSeconds / CTickEventHandler::getGameTimeStep());

		_PowerType = powerType;
		
		if(TheDataset.isAccessible(actorRowId))
			_ActorRowId = actorRowId;
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
	/// loss factor on total value (1 = 100%, 0.5 = 50%, 0.3 = 30%)
	float			_LossFactor;
	/// max Range in meters
	float			_Range;
	/// affected score (Hp, sap, sta)
	SCORES::TScores	_AffectedScore;
};

#endif // RYZOM_SPECIAL_POWER_BALANCE_H

/* End of special_power_balance.h */

