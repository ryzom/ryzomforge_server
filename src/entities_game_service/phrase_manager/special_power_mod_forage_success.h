/** \file special_power_mod_forage_success.h
 * Specialized class for power "ModForageSuccess"
 *
 * $Id: special_power_mod_forage_success.h,v 1.2 2007/06/12 12:45:07 coutelas Exp $
 */



#ifndef RYZOM_SPECIAL_POWER_MOD_FORAGE_SUCCESS_H
#define RYZOM_SPECIAL_POWER_MOD_FORAGE_SUCCESS_H

#include "special_power.h"


/**
 * Specialized class for power "ModForageSuccess"
 * \author Stephane Coutelas
 * \author Nevrax France
 * \date 2006
 */
class CSpecialPowerModForageSuccess : public CSpecialPower
{
public:
	/// Default Constructor
	CSpecialPowerModForageSuccess() : CSpecialPower()
	{}

	/// Constructor
	CSpecialPowerModForageSuccess(TDataSetRow actorRowId, CSpecialPowerPhrase *phrase, float durationInSeconds,  
		const std::string& ecosystem, float modifier1, float modifier2 );

	/// apply effects
	virtual void apply();


protected:
	/// ecosystem
	std::string	_Ecosystem;

	// score modifier 
	float _Modifier1;
	float _Modifier2;

	/// Duration in ticks
	NLMISC::TGameCycle	_Duration;
};

#endif // RYZOM_SPECIAL_POWER_MOD_FORAGE_SUCCESS_H

/* End of special_power_mod_forage_success.h */
