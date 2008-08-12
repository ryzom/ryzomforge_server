/** \file mod_magic_protection_effet.h
 * Magic protection modify effect
 *
 * $Id: mod_magic_protection_effet.h,v 1.2 2006/10/09 15:25:30 saffray Exp $
 */



#ifndef RY_MOD_MAGPRO_EFFECT_H
#define RY_MOD_MAGPRO_EFFECT_H

#include "phrase_manager/s_effect.h"
#include "game_share/protection_type.h"

#include "game_share/persistent_data.h"

/**
 * Effect class modify magic protection
 * \author Alain Saffray
 * \author Nevrax France
 * \date 2005
 */
class CModMagicProtectionEffect : public CSTimedEffect
{
public:
	NLMISC_DECLARE_CLASS(CModMagicProtectionEffect)
	
	DECLARE_PERSISTENCE_METHODS

	// default ctor
	CModMagicProtectionEffect() : CSTimedEffect() {}

	///\ctor
	CModMagicProtectionEffect( const TDataSetRow & creatorRowId, uint32 endDate, EFFECT_FAMILIES::TEffectFamily effectFamily, PROTECTION_TYPE::TProtectionType affectedProtection, float modifier1, float modifier2)
		:CSTimedEffect(creatorRowId, creatorRowId, effectFamily, true, 0, 0, endDate)
	{
#ifdef NL_DEBUG
		_LastUpdateDate = CTickEventHandler::getGameCycle();
#endif
		_Modifier1 = (sint32)modifier1;
		_Modifier2 = (sint32)modifier2;
		_AffectedProtection = affectedProtection;
	}
	
	/**
	 * apply the effects of the... effect
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect);

	/// callback called when the effect is actually removed
	virtual void removed();

	// set disable time for targets
	inline void setTargetDisableTime(NLMISC::TGameCycle time) { _TargetDisableTime = time; }

	// get effect value
	inline sint32 getEffectValue() const { return _Modifier1 + _Modifier2; }

	// get affected protection
	inline PROTECTION_TYPE::TProtectionType getAffectedProtection() const { return _AffectedProtection; }

	// re-activate a magic protection modifier loaded with character
	void activate();

private:
	// disableTime for targets
	NLMISC::TGameCycle		_TargetDisableTime;
	
	/// affected protection
	PROTECTION_TYPE::TProtectionType _AffectedProtection;

	/// characteristics modifiers
	sint32				_Modifier1;
	sint32				_Modifier2;

	NLMISC::CEntityId	_CreatorEntityId;
			
#ifdef NL_DEBUG
	NLMISC::TGameCycle	_LastUpdateDate;
#endif
};


#endif // RY_MOD_MAGPRO_EFFECT_H

/* End of mod_magic_protection_effet.h */
