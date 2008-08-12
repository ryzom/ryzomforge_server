/** \file special_power_dot.h
 * Specialized class for dot-like powers(berserk..)
 *
 * $Id: special_power_dot.h,v 1.4 2004/12/08 13:26:44 besson Exp $
 */


#ifndef RYZOM_SPECIAL_POWER_DOT_H
#define RYZOM_SPECIAL_POWER_DOT_H

#include "special_power.h"


/**
 * Specialized class for dot-like powers such as berserk
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CSpecialPowerDoT : public CSpecialPower
{
public:
	/// Constructor
	CSpecialPowerDoT(TDataSetRow actorRowId, CSpecialPowerPhrase *phrase, float durationInSeconds, float disableTimeInSeconds, POWERS::TPowerType powerType)
	:CSpecialPower()
	{
		_EffectFamily = EFFECT_FAMILIES::Unknown;
		_ParamValue = 0;		
		_Phrase = phrase;
		_Duration = NLMISC::TGameCycle(durationInSeconds / CTickEventHandler::getGameTimeStep());
		_DisablePowerTime = NLMISC::TGameCycle(disableTimeInSeconds / CTickEventHandler::getGameTimeStep());

		_PowerType = powerType;
		
		if(TheDataset.isAccessible(actorRowId))
			_ActorRowId = actorRowId;
		else
		{
			nlwarning("<CSpecialPowerDoT> invalid data set row passed as actor");
		}
	}

	/// set the update frequency
	inline void setUpdateFrequency(float updateFrequencyInSeconds) { _UpdateFrequency = NLMISC::TGameCycle(updateFrequencyInSeconds / CTickEventHandler::getGameTimeStep()); }

	/// set the damage per update
	inline void setDamagePerUpdate(float damage) { _DamagePerUpdate = damage; }

	/// apply effects
	virtual void apply();

	/// set effect family
	inline void setEffectFamily(EFFECT_FAMILIES::TEffectFamily family) { _EffectFamily = family; }

	/// set param value
	inline void setParamValue(sint32 value) { _ParamValue = value; }

protected:
	/// effect duration
	NLMISC::TGameCycle		_Duration;

	/// update rate in ticks
	NLMISC::TGameCycle		_UpdateFrequency;

	/// damage per update
	float					_DamagePerUpdate;

	/// effect param value
	sint32					_ParamValue;

	/// effect family
	EFFECT_FAMILIES::TEffectFamily	_EffectFamily;
};

#endif // RYZOM_SPECIAL_POWER_DOT_H

/* End of special_power_dot.h */
