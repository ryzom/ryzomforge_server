/** \file s_link_effect_debuff_stat.h
 * <File description>
 *
 * $Id: s_link_effect_debuff_stat.h,v 1.14 2005/02/22 10:22:29 besson Exp $
 */



#ifndef RY_S_LINK_EFFECT_DEBUFF_STAT_H
#define RY_S_LINK_EFFECT_DEBUFF_STAT_H

#include "phrase_manager/s_link_effect.h"
#include "entity_manager/entity_base.h"


/**
 * dbueff stat effect
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2003
 */
class CSLinkEffectDebuffStat : public CSLinkEffectOffensive
{
public:
	inline CSLinkEffectDebuffStat( 
		const TDataSetRow & creatorRowId,
		const TDataSetRow & targetRowId,
		EFFECT_FAMILIES::TEffectFamily family,
		sint32 costPerUpdate,
		SCORES::TScores energyCost,
		SKILLS::ESkills skill,
		uint32 maxDistance,
		sint32 modifier,
		float multiplier,
		STAT_TYPES::TStatType type,
		uint stat,
		uint8 power,
		TReportAction& report )
		 :CSLinkEffectOffensive( creatorRowId,targetRowId,family,costPerUpdate,energyCost, skill, maxDistance, modifier, power, report ),
		 _Multiplier( multiplier ),
		_Type( type ),
		_Stat( stat )
	{
		_Applied = false;
	}

	/**
	 * apply the effects of the... effect
	 * \return true if effects ends
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect);

	/// callback called when the effect is actually removed
	virtual void removed();

protected:
	float					_Multiplier;
	sint32			  		_Stat;
	STAT_TYPES::TStatType	_Type;
	bool					_Applied;
	
};


#endif // RY_S_LINK_EFFECT_DEBUFF_STAT_H

/* End of s_link_effect_debuff_stat.h */
