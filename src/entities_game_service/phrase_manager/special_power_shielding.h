/** \file special_power_shielding.h
 * Specialized class for power "shielding"
 *
 * $Id: special_power_shielding.h,v 1.4 2004/12/08 13:26:44 besson Exp $
 */



#ifndef RYZOM_SPECIAL_POWER_SHIELDING_H
#define RYZOM_SPECIAL_POWER_SHIELDING_H

#include "special_power.h"


/**
 * Specialized class for power "shielding"
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CSpecialPowerShielding : public CSpecialPower
{
public:
	/// Default Constructor
	CSpecialPowerShielding() : CSpecialPower()
	{
		init();
	}

	/// Constructor
	CSpecialPowerShielding(TDataSetRow actorRowId, CSpecialPowerPhrase *phrase, float durationInSeconds, float disableTimeInSeconds)
	{
		init();
		_Phrase = phrase;
		_Duration = NLMISC::TGameCycle(durationInSeconds / CTickEventHandler::getGameTimeStep());;		
		_DisablePowerTime = NLMISC::TGameCycle(disableTimeInSeconds / CTickEventHandler::getGameTimeStep());

		_PowerType = POWERS::Shielding;
		
		if(TheDataset.isAccessible(actorRowId))
			_ActorRowId = actorRowId;
		else
		{
			nlwarning("<CSpecialPowerShielding> invalid data set row passed as actor");
		}
	}

	/// validate the power utilisation
	virtual bool validate(std::string &errorCode);

	/// apply effects
	virtual void apply();

	// set protections
	inline void setNoShieldProtection(float factor, uint16 max) { _NoShieldFactor = factor; _NoShieldMaxProtection = max; }
	inline void setBucklerProtection(float factor, uint16 max) { _BucklerFactor = factor; _BucklerMaxProtection = max; }
	inline void setShieldProtection(float factor, uint16 max) { _ShieldFactor = factor; _ShieldMaxProtection = max; }

protected:
	inline void init()
	{
		_NoShieldFactor = 0.0f;
		_BucklerFactor = 0.0f;
		_ShieldFactor = 0.0f;
		
		_NoShieldMaxProtection = 0;
		_BucklerMaxProtection = 0;
		_ShieldMaxProtection = 0;

		_Duration = 0;
	}

	/// granted protections 
	float					_NoShieldFactor;
	float					_BucklerFactor;
	float					_ShieldFactor;
	
	uint16					_NoShieldMaxProtection;
	uint16					_BucklerMaxProtection;
	uint16					_ShieldMaxProtection;

	// effect duration
	NLMISC::TGameCycle		_Duration;
	
};

#endif // RYZOM_SPECIAL_POWER_SHIELDING_H

/* End of special_power_shielding.h */
