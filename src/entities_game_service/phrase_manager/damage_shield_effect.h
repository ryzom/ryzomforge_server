/** \file damage_shield_effect.h
 * <File description>
 *
 * $Id: damage_shield_effect.h,v 1.8 2007/01/03 16:20:28 coutelas Exp $
 */



#ifndef RY_DAMAGE_SHIELD_EFFECT_H
#define RY_DAMAGE_SHIELD_EFFECT_H

//
#include "phrase_manager/s_effect.h"
#include "entity_manager/entity_base.h"



/**
 * class for damage shields
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CDamageShieldEffect : public CSTimedEffect
{
public:
	NLMISC_DECLARE_CLASS(CDamageShieldEffect)

	///\ctor
	CDamageShieldEffect( const TDataSetRow & creatorRowId, 
						const TDataSetRow & targetRowId, 
						EFFECT_FAMILIES::TEffectFamily family, 
						sint32 damagePerHit, 
						NLMISC::TGameCycle endDate,
						float drainFactor
						)
		:	CSTimedEffect(creatorRowId, targetRowId, family, true, damagePerHit, damagePerHit, endDate),
			_DrainFactor(drainFactor)
	{
	}
	/**
	 * apply the effects of the... effect
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect) { return false; }

	/// callback called when the effect is actually removed
	virtual void removed();

	/// get drain factor
	inline float getDrainFactor() const { return _DrainFactor; }

	/// set drain factor
	inline void setDrainFactor(float f) { _DrainFactor = f; }

private:
	/// factor of inflicted damage recovered by the effect creator
	float					_DrainFactor;

	CDamageShieldEffect() {}
};


#endif // RY_DAMAGE_SHIELD_EFFECT_H

/* End of damage_shield_effect.h */
