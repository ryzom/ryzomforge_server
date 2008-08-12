/** \file aura_regen_effect.h
 * LifeAura Effect
 *
 * $Id: aura_regen_effect.h,v 1.9 2005/02/08 18:59:00 boucher Exp $
 */



#ifndef RY_AURA_REGEN_EFFECT_H
#define RY_AURA_REGEN_EFFECT_H

#include "aura_effect.h"


/**
 * Effect class for aura affecting regen
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CRegenAuraEffect : public CAuraBaseEffect
{
public:
	///\ctor
	CRegenAuraEffect( const CAuraRootEffect &rootEffect, TDataSetRow targetRowId ) : CAuraBaseEffect(rootEffect, targetRowId)
	{
		NL_ALLOC_CONTEXT(RAE_CTR);
		_RegenModifier = float(rootEffect.getParamValue()) / 10.0f;

		switch(_PowerType)
		{
		case POWERS::LifeAura:
			_AffectedScore = SCORES::hit_points;
			break;
		case POWERS::StaminaAura:
			_AffectedScore = SCORES::stamina;
			break;
		case POWERS::SapAura:
			_AffectedScore = SCORES::sap;
			break;
		default:
			nlwarning("CRegenAuraEffect : cannot manage power type %s", POWERS::toString(_PowerType).c_str());
			_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
			_AffectedScore = SCORES::unknown;
		};
	}
	
	/**
	 * apply the effects of the... effect
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect);

	/// callback called when the effect is actually removed
	virtual void removed();

private:
	/// regen modifier
	float			_RegenModifier;

	/// affected score
	SCORES::TScores _AffectedScore;
};


#endif // RY_AURA_REGEN_EFFECT_H

/* End of aura_regen_effect.h */
