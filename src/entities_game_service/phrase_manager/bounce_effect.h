/** \file bounce_effect.h
 * <File description>
 *
 * $Id: bounce_effect.h,v 1.7 2007/01/03 16:20:28 coutelas Exp $
 */



#ifndef RY_BOUNCE_EFFECT_H
#define RY_BOUNCE_EFFECT_H

//
#include "phrase_manager/s_effect.h"
#include "entity_manager/entity_base.h"



/**
 * class for 'bounce' effects
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CBounceEffect : public CSTimedEffect
{
public:
	NLMISC_DECLARE_CLASS(CBounceEffect)

	/// ctor
	CBounceEffect() : CSTimedEffect()
	{}

	///\ctor
	CBounceEffect( const TDataSetRow & creatorRowId, 
						const TDataSetRow & targetRowId, 
						EFFECT_FAMILIES::TEffectFamily family, 
						sint32 effectValue, 
						NLMISC::TGameCycle endDate
						)
		:	CSTimedEffect(creatorRowId, targetRowId, family, false, effectValue,(uint8)0, endDate)
	{
		// range of the effect in meters = effecValue
	}

	/**
	 * apply the effects of the... effect
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect) { return false; }

	/// callback called when the effect is actually removed
	virtual void removed();

	/// get entity on which the attack is redirected
	CEntityBase *getTargetForBounce() const;

private:
	/// check entity is a valid target
	bool isEntityValidTarget(CEntityBase *entity) const;

private:
	/// affected entity
	mutable CEntityBaseRefPtr _AffectedEntity;
};


#endif // RY_BOUNCE_EFFECT_H

/* End of bounce_effect.h */
