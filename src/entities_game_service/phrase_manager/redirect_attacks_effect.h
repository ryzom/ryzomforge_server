/** \file redirect_attacks_effect.h
 * <File description>
 *
 * $Id: redirect_attacks_effect.h,v 1.7 2007/01/03 16:20:28 coutelas Exp $
 */



#ifndef RY_REDIRECT_ATTACKS_EFFECT_H
#define RY_REDIRECT_ATTACKS_EFFECT_H

//
#include "phrase_manager/s_effect.h"
#include "entity_manager/entity_base.h"
#include "creature_manager/creature.h"



/**
 * class for redirect attacks effects
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CRedirectAttacksEffect : public CSTimedEffect
{
public:
	NLMISC_DECLARE_CLASS(CRedirectAttacksEffect)

	/// ctor
	CRedirectAttacksEffect() : CSTimedEffect(), _Range(50.0f)
	{}

	///\ctor
	CRedirectAttacksEffect( const TDataSetRow & creatorRowId, 
						const TDataSetRow & targetRowId, 
						EFFECT_FAMILIES::TEffectFamily family, 
						sint32 effectValue, 
						NLMISC::TGameCycle endDate,
						float range = 50.0f
						);
	
	/**
	 * apply the effects of the... effect
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect) { return false; }

	/// callback called when the effect is actually removed
	virtual void removed();

	/// get entity on which the attack is redirected
	CEntityBase *getTargetForRedirection() const;	

	/// set range
	inline void setRange(float r) { _Range = r;	}

private:
	/// check entity is a valid target
	bool isEntityValidTarget(CEntityBase *entity) const;

private:
	/// range in meters
	float					_Range;

	/// affected entity
	mutable CCreatureRefPtr _AffectedCreature;

	/// affected entity
	mutable CEntityBaseRefPtr _TargetEntityForRedirection;
};


#endif // RY_REDIRECT_ATTACKS_EFFECT_H

/* End of redirect_attacks_effect.h */
