/** \file special_power_speeding_up.h
 * Specialized class for power "SpeedingUp"
 *
 * $Id: special_power_speeding_up.h,v 1.5 2004/12/08 13:26:44 besson Exp $
 */



#ifndef RYZOM_SPECIAL_POWER_SPEEDING_UP_H
#define RYZOM_SPECIAL_POWER_SPEEDING_UP_H

#include "special_power.h"


/**
 * Specialized class for power "SpeedingUp"
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CSpecialPowerSpeedingUp : public CSpecialPower
{
public:
	/// Default Constructor
	CSpecialPowerSpeedingUp() : CSpecialPower()
	{}

	/// Constructor
	CSpecialPowerSpeedingUp(TDataSetRow actorRowId, CSpecialPowerPhrase *phrase, uint8 speedMod, float durationInSeconds, float disableTimeInSeconds) 
		: _SpeedMod(speedMod)
	{
		_Phrase = phrase;
		
		_DisablePowerTime = NLMISC::TGameCycle(disableTimeInSeconds / CTickEventHandler::getGameTimeStep());
		_Duration = NLMISC::TGameCycle(durationInSeconds / CTickEventHandler::getGameTimeStep());		

		_PowerType = POWERS::SpeedingUp;
		
		if(TheDataset.isAccessible(actorRowId))
			_ActorRowId = actorRowId;
		else
		{
			nlwarning("<CSpecialPowerSpeedingUp> invalid data set row passed as actor");
		}
	}

	/// apply effects
	virtual void apply();


protected:
	/// speed modifier in % (max 100%)
	uint8				_SpeedMod;

	/// Duration in ticks
	NLMISC::TGameCycle	_Duration;
};

#endif // RYZOM_SPECIAL_POWER_SPEEDING_UP_H

/* End of special_power_speeding_up.h */
