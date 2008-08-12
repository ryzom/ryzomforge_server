/** \file special_power_mod_craft_success.h
 * Specialized class for power "ModCraftSuccess"
 *
 * $Id: special_power_mod_craft_success.h,v 1.1 2006/10/11 16:25:41 coutelas Exp $
 */



#ifndef RYZOM_SPECIAL_POWER_MOD_CRAFT_SUCCESS_H
#define RYZOM_SPECIAL_POWER_MOD_CRAFT_SUCCESS_H

#include "special_power.h"


/**
 * Specialized class for power "ModCraftSuccess"
 * \author Stephane Coutelas
 * \author Nevrax France
 * \date 2006
 */
class CSpecialPowerModCraftSuccess : public CSpecialPower
{
public:
	/// Default Constructor
	CSpecialPowerModCraftSuccess() : CSpecialPower()
	{}

	/// Constructor
	CSpecialPowerModCraftSuccess(TDataSetRow actorRowId, CSpecialPowerPhrase *phrase, float durationInSeconds,  
		POWERS::TPowerType powerType, float modifier1, float modifier2 )
	{
		if(TheDataset.isAccessible(actorRowId))
			_ActorRowId = actorRowId;
		else
		{
			nlwarning("<CSpecialPowerModCraftSuccess> invalid data set row passed as actor");
		}

		_Phrase = phrase;
		
		_DisablePowerTime = 0;
		_Duration = NLMISC::TGameCycle(durationInSeconds / CTickEventHandler::getGameTimeStep());		

		_PowerType = powerType;
		_Modifier1 = modifier1;
		_Modifier2 = modifier2;
	}

	/// apply effects
	virtual void apply();


protected:
	// score modifier 
	float _Modifier1;
	float _Modifier2;

	/// Duration in ticks
	NLMISC::TGameCycle	_Duration;
};

#endif // RYZOM_SPECIAL_POWER_MOD_CRAFT_SUCCESS_H

/* End of special_power_mod_craft_success.h */
