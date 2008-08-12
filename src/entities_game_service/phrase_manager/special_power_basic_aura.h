/** \file special_power_basic_aura.h
 * Specialized class for basic auras (LifeAura, StaminaAura, SapAura...)
 *
 * $Id: special_power_basic_aura.h,v 1.7 2005/09/08 10:06:32 coutelas Exp $
 */



#ifndef RYZOM_SPECIAL_POWER_BASIC_AURA_H
#define RYZOM_SPECIAL_POWER_BASIC_AURA_H

#include "special_power.h"


/**
 * Specialized class for auras
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CSpecialPowerBasicAura : public CSpecialPowerAuras
{
public:
	/// Default Constructor
	CSpecialPowerBasicAura() : CSpecialPowerAuras()
	{		
	}

	/// Constructor
	CSpecialPowerBasicAura(TDataSetRow actorRowId, CSpecialPowerPhrase *phrase, float durationInSeconds, float userDisableTimeInSeconds, float targetsDisableTimeInSeconds, POWERS::TPowerType powerType)
	:CSpecialPowerAuras()
	{
		_Phrase = phrase;
		_Duration = NLMISC::TGameCycle(durationInSeconds / CTickEventHandler::getGameTimeStep());;		
		_DisablePowerTime = NLMISC::TGameCycle(userDisableTimeInSeconds / CTickEventHandler::getGameTimeStep());
		_TargetsDisableAuraTime = NLMISC::TGameCycle(targetsDisableTimeInSeconds / CTickEventHandler::getGameTimeStep());

		_PowerType = powerType;
		
		if(TheDataset.isAccessible(actorRowId))
			_ActorRowId = actorRowId;
		else
		{
			nlwarning("<CSpecialPowerBasicAura> invalid data set row passed as actor");
		}
	}

	/// apply effects
	virtual void apply();

	/// set families
	inline void setFamilies(EFFECT_FAMILIES::TEffectFamily rootEffectFamily, EFFECT_FAMILIES::TEffectFamily createdEffectFamily)
	{
		_RootEffectFamily = rootEffectFamily;
		_CreatedEffectFamily = createdEffectFamily;
	}

	/// set param value
	inline void setParamValue(sint32 value) { _ParamValue = value; }

protected:
	/// effect duration
	NLMISC::TGameCycle		_Duration;

	/// param value
	sint32					_ParamValue;

	/// root effect family (used for txt msg)
	EFFECT_FAMILIES::TEffectFamily	_RootEffectFamily;
	/// created effect family
	EFFECT_FAMILIES::TEffectFamily	_CreatedEffectFamily;	
	
};

#endif // RYZOM_SPECIAL_POWER_BASIC_AURA_H

/* End of special_power_basic_aura.h */
