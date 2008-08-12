/** \file regen_modifier_effect.h
 * effect class for effects on regen
 *
 * $Id: regen_modifier_effect.h,v 1.8 2007/01/03 16:20:28 coutelas Exp $
 */



#ifndef RY_REGEN_MODIFIER_EFFECT_H
#define RY_REGEN_MODIFIER_EFFECT_H

//
#include "game_share/scores.h"
//
#include "phrase_manager/s_effect.h"


/**
 * Effect class for simple effects
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CRegenModifierEffect : public CSTimedEffect
{
public:
	NLMISC_DECLARE_CLASS(CRegenModifierEffect)

	///\ctor
	CRegenModifierEffect(	const TDataSetRow & creatorRowId,
							const TDataSetRow & targetRowId,
							EFFECT_FAMILIES::TEffectFamily family,
							uint32 endDate,
							uint8 power,
							float factor,
							SCORES::TScores score)
		:CSTimedEffect(creatorRowId, targetRowId, family, false, 0, power, endDate),
		_AffectedScore(score),
		_DebuffFactor(factor),
		_FirstUpdate(true)
	{
	}

	/**
	 * apply the effects of the... effect
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect);

	/// callback called when the effect is actually removed
	virtual void removed();

	/// set the effect name
	inline void effectName(const std::string &str) { _EffectName = str; }
	/// get the effect name
	inline const std::string &effectName() { return _EffectName; }

private:
	/// affected score
	SCORES::TScores			_AffectedScore;

	/// debuff factor
	float					_DebuffFactor;

	/// "name" of the effect, used for client chat messages
	std::string				_EffectName;

	/// flag, true if first update
	bool					_FirstUpdate;

	/// the value added to the regen modifier (<0)
	float					_RegenModifier;

	// private ctor for use in NLMISC class registry
	CRegenModifierEffect() {}
};


#endif // RY_REGEN_MODIFIER_EFFECT_H

/* End of regen_modifier_effect.h */
