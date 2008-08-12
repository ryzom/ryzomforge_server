/** \file special_power_mod_defense.h
 * Specialized class for power "ModDefense", "ModDodge" and "ModParry"
 *
 * $Id: special_power_mod_defense.h,v 1.4 2007/06/12 12:45:07 coutelas Exp $
 */



#ifndef RYZOM_SPECIAL_POWER_MOD_DEFENSE_H
#define RYZOM_SPECIAL_POWER_MOD_DEFENSE_H

#include "special_power.h"


/**
 * Specialized class for power "ModDefense"
 * \author Stephane Coutelas
 * \author Nevrax France
 * \date 2006
 */
class CSpecialPowerModDefense : public CSpecialPower
{
public:
	/// Default Constructor
	CSpecialPowerModDefense() : CSpecialPower()
	{}

	/// Constructor
	CSpecialPowerModDefense(TDataSetRow actorRowId, CSpecialPowerPhrase *phrase, float durationInSeconds,  
		const std::string& defenseMode, float modifier1, float modifier2 )
	{
		if(TheDataset.isAccessible(actorRowId))
			_ActorRowId = actorRowId;
		else
		{
			nlwarning("<CSpecialPowerModDefense> invalid data set row passed as actor");
		}

		_Phrase = phrase;
		
		_DisablePowerTime = 0;
		_Duration = NLMISC::TGameCycle(durationInSeconds / CTickEventHandler::getGameTimeStep());		

		_DefenseMode = defenseMode;
		_Modifier1 = modifier1;
		_Modifier2 = modifier2;

		if( NLMISC::toLower(_DefenseMode) == "dodge" )
			_PowerType = POWERS::ModDodgeSkill;
		else
		if( NLMISC::toLower(_DefenseMode) == "parry" )
			_PowerType = POWERS::ModParrySkill;
		else
			_PowerType = POWERS::ModDefenseSkill;
	}

	/// apply effects
	virtual void apply();


protected:
	/// Dodge or Parry ?
	std::string	_DefenseMode;

	// score modifier 
	float _Modifier1;
	float _Modifier2;

	/// Duration in ticks
	NLMISC::TGameCycle	_Duration;
};

#endif // RYZOM_SPECIAL_POWER_MOD_DEFENSE_H

/* End of special_power_mod_defense.h */
