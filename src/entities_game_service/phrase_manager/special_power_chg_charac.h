/** \file special_power_chg_charac.h
 * Specialized class for power "ChgCharac"
 *
 * $Id: special_power_chg_charac.h,v 1.3 2006/10/09 15:25:31 saffray Exp $
 */



#ifndef RYZOM_SPECIAL_POWER_CHG_CHARAC_H
#define RYZOM_SPECIAL_POWER_CHG_CHARAC_H

#include "special_power.h"


/**
 * Specialized class for power "ChgCharac"
 * \author Stephane Coutelas
 * \author Nevrax France
 * \date 2005
 */
class CSpecialPowerChgCharac : public CSpecialPower
{
public:
	/// Default Constructor
	CSpecialPowerChgCharac() : CSpecialPower()
	{}

	/// Constructor
	CSpecialPowerChgCharac(TDataSetRow actorRowId, CSpecialPowerPhrase *phrase, float durationInSeconds,  
		POWERS::TPowerType powerType, const std::string& charac, float modifier1, float modifier2 )
	{
		if(TheDataset.isAccessible(actorRowId))
			_ActorRowId = actorRowId;
		else
		{
			nlwarning("<CSpecialPowerChgCharac> invalid data set row passed as actor");
		}

		_Phrase = phrase;
		
		_DisablePowerTime = 0;
		_Duration = NLMISC::TGameCycle(durationInSeconds / CTickEventHandler::getGameTimeStep());		

		_PowerType = powerType;
		_AffectedCharac = charac;
		_Modifier1 = modifier1;
		_Modifier2 = modifier2;
	}

	/// apply effects
	virtual void apply();


protected:
	/// affected characteristic
	std::string	_AffectedCharac;

	// score modifier 
	float _Modifier1;
	float _Modifier2;

	/// Duration in ticks
	NLMISC::TGameCycle	_Duration;
};

#endif // RYZOM_SPECIAL_POWER_CHG_CHARAC_H

/* End of special_power_chg_charac.h */
