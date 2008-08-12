/** \file simple_effect.h
 * Effect class for very simple effects, which does nothing more than existing and simply use a sint32 to stock their data
 * used for CombatDefenseMododifier, CombatAttackSlow, CombatCastSlow
 *
 * $Id: simple_effect.h,v 1.13 2007/01/03 16:20:28 coutelas Exp $
 */



#ifndef RY_SIMPLE_EFFECT_H
#define RY_SIMPLE_EFFECT_H

#include "phrase_manager/s_effect.h"


/**
 * Effect class for simple effects
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CSimpleEffect : public CSTimedEffect
{
public:
	NLMISC_DECLARE_CLASS(CSimpleEffect)

	CSimpleEffect() : CSTimedEffect()
	{
#ifdef NL_DEBUG
		_Applied =false;
#endif
	}
	
	CSimpleEffect( const TDataSetRow & creatorRowId, const TDataSetRow & targetRowId, EFFECT_FAMILIES::TEffectFamily family, sint32 effectValue, uint32 endDate, uint8 power )
		:CSTimedEffect(creatorRowId, targetRowId, family, false, effectValue, power, endDate)
	{
#ifdef NL_DEBUG
		_Applied =false;
#endif
	}

	/**
	 * apply the effects of the... effect
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect);

	/// callback called when the effect is actually removed
	virtual void removed();

#ifdef NL_DEBUG
private:
	bool			_Applied;
#endif
};


#endif // RY_SIMPLE_EFFECT_H

/* End of combat_simple_effect.h */
