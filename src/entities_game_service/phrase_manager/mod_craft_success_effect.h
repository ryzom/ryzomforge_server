/** \file mod_craft_success_effect.h
 * Mod Craft Success Effect
 *
 * $Id: mod_craft_success_effect.h,v 1.1 2006/10/11 16:25:41 coutelas Exp $
 */



#ifndef RY_MOD_CRAFT_SUCCESS_EFFECT_H
#define RY_MOD_CRAFT_SUCCESS_EFFECT_H

#include "phrase_manager/s_effect.h"

#include "game_share/persistent_data.h"

/**
 * Effect class affecting craft success chance
 * \author Stephane Coutelas
 * \author Nevrax France
 * \date 2006
 */
class CModCraftSuccessEffect : public CSTimedEffect
{
public:
	NLMISC_DECLARE_CLASS(CModCraftSuccessEffect)
		
	DECLARE_PERSISTENCE_METHODS

	/// default ctor
	CModCraftSuccessEffect() : CSTimedEffect() {}

	///\ctor
	CModCraftSuccessEffect( const TDataSetRow & creatorRowId, uint32 endDate, EFFECT_FAMILIES::TEffectFamily effectFamily, float modifier1, float modifier2)
		:CSTimedEffect(creatorRowId, creatorRowId, effectFamily, true, 0/*paramvalue*/, 0/*power*/, endDate)
	{
#ifdef NL_DEBUG
		_LastUpdateDate = CTickEventHandler::getGameCycle();
#endif
		_Modifier1 = modifier1;
		_Modifier2 = modifier2;
	}
	
	/**
	 * apply the effects of the... effect
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect);

	/// callback called when the effect is actually removed
	virtual void removed();

	// set disable time for targets
	inline void setTargetDisableTime(NLMISC::TGameCycle time) { _TargetDisableTime = time; }

		// re-activate effect after loaded with a character
	void activate();

private:
	// disableTime for targets
	NLMISC::TGameCycle		_TargetDisableTime;
	
	/// characteristics modifiers
	float			_Modifier1;
	float			_Modifier2;

	NLMISC::CEntityId	_CreatorEntityId;

			
#ifdef NL_DEBUG
	NLMISC::TGameCycle		_LastUpdateDate;
#endif
};


#endif // RY_MOD_CRAFT_SUCCESS_EFFECT_H

/* End of mod_craft_success_effect.h */
