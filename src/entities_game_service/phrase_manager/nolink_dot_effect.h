/** \file nolink_dot_effect.h
 * <File description>
 *
 * $Id: nolink_dot_effect.h,v 1.12 2007/01/03 16:20:28 coutelas Exp $
 */



#ifndef RY_NOLINK_DOT_EFFECT_H
#define RY_NOLINK_DOT_EFFECT_H

// game share
#include "game_share/scores.h"
//
#include "phrase_manager/s_effect.h"
#include "entity_manager/entity_base.h"



/**
 * class for dot effects that are not links
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CNoLinkDOTEffect : public CSTimedEffect
{
public:
	NLMISC_DECLARE_CLASS(CNoLinkDOTEffect)

	///\ctor
	CNoLinkDOTEffect ( const TDataSetRow & creatorRowId, 
						const TDataSetRow & targetRowId, 
						EFFECT_FAMILIES::TEffectFamily family, 
						sint32 effectValue, 
						NLMISC::TGameCycle endDate,
						NLMISC::TGameCycle cycleLenght,
						SCORES::TScores	affectedScore,
						float cycleDamage,
						DMGTYPE::EDamageType damageType
						)
		:	CSTimedEffect(creatorRowId, targetRowId, family, false, effectValue, abs((sint32)cycleDamage), endDate),
			_CycleLength(cycleLenght),
			_CycleDamage(cycleDamage),
			_AffectedScore(affectedScore),
			_DamageType(damageType)
	{
		_RemainingDamage = 0;
		_EndsAtCasterDeath = false;
		_Stackable = false;
	}

	/**
	 * apply the effects of the... effect
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect);

	/// callback called when the effect is actually removed
	virtual void removed();

	/// if true effect ends at caster death 
	inline void endsAtCasterDeath(bool flag) { _EndsAtCasterDeath = flag; }

	/// set the stackable flag
	inline void stackable(bool flag) { _Stackable = flag; }

private:
	/// cycle lenght in ticks
	NLMISC::TGameCycle		_CycleLength;

	/// number of score points lost by target each cycle
	float					_CycleDamage;
	/// fraction of lost points when not integer (0-1)
	float					_RemainingDamage;

	/// affected score
	SCORES::TScores			_AffectedScore;

	/// damage type
	DMGTYPE::EDamageType	_DamageType;

	/// if true effect ends at caster death 
	bool					_EndsAtCasterDeath;

	/// if true DoT can stacks, otherwise they don't stack
	bool					_Stackable;

	// private ctor for use in NLMISC class registry
	CNoLinkDOTEffect() {}

};


#endif // RY_NOLINK_DOT_EFFECT_H

/* End of nolink_dot_effect.h */
