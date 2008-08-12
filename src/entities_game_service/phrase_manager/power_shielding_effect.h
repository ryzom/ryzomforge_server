/** \file power_shielding_effect.h
 * Shielding Effect
 *
 * $Id: power_shielding_effect.h,v 1.11 2006/10/09 15:25:30 saffray Exp $
 */



#ifndef RY_POWER_SHIELDING_EFFECT_H
#define RY_POWER_SHIELDING_EFFECT_H

#include "phrase_manager/s_effect.h"
#include "combat_defender.h"


/**
 * Effect class for shielding effect
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CShieldingEffect : public CSTimedEffect
{
public:
	NLMISC_DECLARE_CLASS(CShieldingEffect)
		
	DECLARE_PERSISTENCE_METHODS

	// Default ctor for factory
	CShieldingEffect() : CSTimedEffect() {}

	///\ctor
	CShieldingEffect( const TDataSetRow & creatorRowId, const TDataSetRow & targetRowId, uint32 endDate, uint8 power )
		:CSTimedEffect(creatorRowId, targetRowId, EFFECT_FAMILIES::PowerShielding, false, 0, power, endDate)
	{
	}

	/**
	 * apply the effects of the... effect
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect) { return false; }

	/// callback called when the effect is actually removed
	virtual void removed();

	// set protections
	inline void setNoShieldProtection(float factor, uint16 max) { _NoShieldFactor = factor; _NoShieldMaxProtection = max; }
	inline void setBucklerProtection(float factor, uint16 max) { _BucklerFactor = factor; _BucklerMaxProtection = max; }
	inline void setShieldProtection(float factor, uint16 max) { _ShieldFactor = factor; _ShieldMaxProtection = max; }

	// get protection factor and max for given CCombatDefender
	inline void getProtectionParams( const CCombatDefender *bodyguard, float &factor, uint16 &max ) const
	{
#ifdef NL_DEBUG
		nlassert(bodyguard != NULL);
#endif
		CCombatShield shield;
		bodyguard->getShield(shield);
		switch(shield.ShieldType)
		{
		case SHIELDTYPE::SMALL_SHIELD:
			factor = _BucklerFactor;
			max = _BucklerMaxProtection;
			break;
		case SHIELDTYPE::LARGE_SHIELD:
			factor = _ShieldFactor;
			max = _ShieldMaxProtection;
			break;
		default:
			factor = _NoShieldFactor;
			max = _NoShieldMaxProtection;
			break;
		};
	}

	// for activate saved effect after character load
	void activate();

private:
	/// granted protections 
	float					_NoShieldFactor;
	float					_BucklerFactor;
	float					_ShieldFactor;

	uint16					_NoShieldMaxProtection;
	uint16					_BucklerMaxProtection;
	uint16					_ShieldMaxProtection;

	NLMISC::CEntityId		_CreatorEntityId;
	NLMISC::CEntityId		_TargetEntityId;
};


#endif // RY_POWER_SHIELDING_EFFECT_H

/* End of power_shielding_effect.h */
