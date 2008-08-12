/** \file nolink_hot_effect.h
 * <File description>
 *
 * $Id: nolink_hot_effect.h,v 1.9 2007/01/03 16:20:28 coutelas Exp $
 */



#ifndef RY_NOLINK_HOT_EFFECT_H
#define RY_NOLINK_HOT_EFFECT_H

// game share
#include "game_share/scores.h"
//
#include "phrase_manager/s_effect.h"
#include "entity_manager/entity_base.h"



/**
 * class for hot effects that are not links
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CNoLinkHoTEffect : public CSTimedEffect
{
public:
	NLMISC_DECLARE_CLASS(CNoLinkHoTEffect)

	///\ctor
	CNoLinkHoTEffect ( const TDataSetRow & creatorRowId, 
						const TDataSetRow & targetRowId, 
						EFFECT_FAMILIES::TEffectFamily family, 
						sint32 effectValue, 
						NLMISC::TGameCycle endDate,
						NLMISC::TGameCycle cycleLenght,
						SCORES::TScores	affectedScore,
						float cycleHeal
						)
		:	CSTimedEffect(creatorRowId, targetRowId, family, false, effectValue, abs((sint32)cycleHeal), endDate),
			_CycleLength(cycleLenght),
			_CycleHeal(cycleHeal),
			_AffectedScore(affectedScore)
	{
		_TargetEntity = NULL;
		_RemainingHeal = 0;
	}

	/**
	 * apply the effects of the... effect
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect);

	/// callback called when the effect is actually removed
	virtual void removed();

private:
	/// cycle lenght in ticks
	NLMISC::TGameCycle		_CycleLength;

	/// number of score points healed each cycle
	float					_CycleHeal;
	/// fraction of healed points when not integer (0-1)
	float					_RemainingHeal;

	/// affected score
	SCORES::TScores			_AffectedScore;

	/// affected entity
	CEntityBaseRefPtr		_TargetEntity;

	// private ctor for use in NLMISC class registry
	CNoLinkHoTEffect() {}
};


#endif // RY_NOLINK_HOT_EFFECT_H

/* End of nolink_hot_effect.h */
