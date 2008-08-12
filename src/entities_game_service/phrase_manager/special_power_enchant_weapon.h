/** \file special_power_enchant_weapon.h
 *
 * $Id: special_power_enchant_weapon.h,v 1.1 2005/06/06 13:20:55 vuarand Exp $
 */

#ifndef RYZOM_SPECIAL_POWER_ENCHANT_WEAPON_H
#define RYZOM_SPECIAL_POWER_ENCHANT_WEAPON_H

#include "special_power.h"

/** Specialized class for weapon enchants
 * \author Jerome Vuarand
 * \author Nevrax France
 * \date 2005
 * 
 * This class is based on CSpecialPowerDoT, thus residual side effects may
 * exist due to copy'n'paste.
 */
class CSpecialPowerEnchantWeapon
: public CSpecialPower
{
public:
	/// Constructor
	CSpecialPowerEnchantWeapon(
		TDataSetRow actorRowId,
		CSpecialPowerPhrase* phrase,
		float durationInSeconds,
		float disableTimeInSeconds,
		POWERS::TPowerType powerType)
	: CSpecialPower()
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
			nlwarning("<CSpecialPowerEnchantWeapon> invalid data set row passed as actor");
	}
	
	/// set the damage type
	void setDamageType(DMGTYPE::EDamageType damageType) { _DamageType = damageType; }
	
	/// set the damage type
	void setDpsBonus(float dpsBonus) { _DpsBonus = dpsBonus; }
	
	/// set the update frequency
//	void setUpdateFrequency(float updateFrequencyInSeconds) { _UpdateFrequency = NLMISC::TGameCycle(updateFrequencyInSeconds / CTickEventHandler::getGameTimeStep()); }
	
	/// set the damage per update
//	void setDamagePerUpdate(float damage) { _DamagePerUpdate = damage; }
	
	/// apply effects
	virtual void apply();
	
	/// set effect family
	void setEffectFamily(EFFECT_FAMILIES::TEffectFamily family) { _EffectFamily = family; }
	
	/// set param value
	void setParamValue(sint32 value) { _ParamValue = value; }
	
protected:
	/// damage type
	DMGTYPE::EDamageType	_DamageType;
	
	/// dps bonus
	float					_DpsBonus;
	
	/// effect duration
	NLMISC::TGameCycle		_Duration;
	
	/// update rate in ticks
//	NLMISC::TGameCycle		_UpdateFrequency;
	
	/// damage per update
//	float					_DamagePerUpdate;
	
	/// effect param value
	sint32					_ParamValue;
	
	/// effect family
	EFFECT_FAMILIES::TEffectFamily	_EffectFamily;
};

#endif
