/** \file stun_effect.h
 * <File description>
 *
 * $Id: stun_effect.h,v 1.8 2007/01/03 16:20:28 coutelas Exp $
 */



#ifndef RY_STUN_EFFECT_H
#define RY_STUN_EFFECT_H

#include "phrase_manager/s_effect.h"
#include "entity_manager/entity_base.h"


/**
 * <Class description>
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CStunEffect : public CSTimedEffect
{
public:
	NLMISC_DECLARE_CLASS(CStunEffect)
	///\ctor
	CStunEffect()
	{}

	CStunEffect( const TDataSetRow & creatorRowId, const TDataSetRow & targetRowId, EFFECT_FAMILIES::TEffectFamily family, sint32 effectValue, uint32 endDate)
		:CSTimedEffect(creatorRowId, targetRowId, family, false, effectValue,0,endDate)
	{}

	/**
	 * apply the effects of the... effect
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect);

	/// callback called when the effect is actually removed
	virtual void removed();
};


#endif // RY_STUN_EFFECT_H

/* End of stun_effect.h */
