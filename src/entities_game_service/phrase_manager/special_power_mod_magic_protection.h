/** \file special_power_mod_magic_protection.h
 * Specialized class for power "ModMagicProtection"
 *
 * $Id: special_power_mod_magic_protection.h,v 1.2 2006/10/09 15:25:31 saffray Exp $
 */



#ifndef RYZOM_SPECIAL_POWER_MOD_MAGIC_PROTECTION_H
#define RYZOM_SPECIAL_POWER_MOD_MAGIC_PROTECTION_H

#include "special_power.h"


/**
 * Specialized class for power "ModMagicProtection"
 * \author Alain Saffray
 * \author Nevrax France
 * \date 2006
 */
class CSpecialPowerModMagicProtection : public CSpecialPower
{
public:
	/// Default Constructor
	CSpecialPowerModMagicProtection() : CSpecialPower()
	{}

	/// Constructor
	CSpecialPowerModMagicProtection(TDataSetRow actorRowId, CSpecialPowerPhrase *phrase, float durationInSeconds,  
		POWERS::TPowerType powerType, const std::string& protection, float modifier1, float modifier2 )
	{
		if(TheDataset.isAccessible(actorRowId))
			_ActorRowId = actorRowId;
		else
		{
			nlwarning("<CSpecialPowerModMagicProtection> invalid data set row passed as actor");
		}

		_Phrase = phrase;
		
		_Duration = NLMISC::TGameCycle(durationInSeconds / CTickEventHandler::getGameTimeStep());		
		_DisablePowerTime = _Duration;

		_PowerType = powerType;
		_AffectedProtection = protection;
		_Modifier1 = modifier1;
		_Modifier2 = modifier2;
	}

	/// apply effects
	virtual void apply();


protected:
	/// affected protection
	std::string	_AffectedProtection;

	// score modifier 
	float _Modifier1;
	float _Modifier2;

	/// Duration in ticks
	NLMISC::TGameCycle	_Duration;
};

#endif // RYZOM_SPECIAL_POWER_MOD_MAGIC_PROTECTION_H

/* End of special_power_mod_magic_protection.h */
