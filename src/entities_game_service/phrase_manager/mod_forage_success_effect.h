/** \file mod_forage_success_effect.h
 * Mod Forage Success Effect
 *
 * $Id: mod_forage_success_effect.h,v 1.2 2007/06/12 12:45:07 coutelas Exp $
 */



#ifndef RY_MOD_FORAGE_SUCCESS_EFFECT_H
#define RY_MOD_FORAGE_SUCCESS_EFFECT_H

#include "phrase_manager/s_effect.h"

#include "game_share/persistent_data.h"

/**
 * Effect class affecting forage success chance
 * \author Stephane Coutelas
 * \author Nevrax France
 * \date 2006
 */
class CModForageSuccessEffect : public CSTimedEffect
{
public:
	NLMISC_DECLARE_CLASS(CModForageSuccessEffect)
		
	DECLARE_PERSISTENCE_METHODS

	/// default ctor
	CModForageSuccessEffect() : CSTimedEffect() {}

	///\ctor
	CModForageSuccessEffect( const TDataSetRow & creatorRowId, uint32 endDate, EFFECT_FAMILIES::TEffectFamily effectFamily, std::string& ecosystem, float modifier1, float modifier2)
		:CSTimedEffect(creatorRowId, creatorRowId, effectFamily, true, 0/*paramvalue*/, 0/*power*/, endDate)
	{
#ifdef NL_DEBUG
		_LastUpdateDate = CTickEventHandler::getGameCycle();
#endif
		_Modifier1 = modifier1;
		_Modifier2 = modifier2;
		_Family = effectFamily;
		_Ecosystem = ecosystem;
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
	
	/// Ecosystem
	std::string _Ecosystem;

	/// characteristics modifiers
	float			_Modifier1;
	float			_Modifier2;

	NLMISC::CEntityId	_CreatorEntityId;
			
#ifdef NL_DEBUG
	NLMISC::TGameCycle		_LastUpdateDate;
#endif
};


#endif // RY_MOD_FORAGE_SUCCESS_EFFECT_H

/* End of mod_forage_success_effect.h */
