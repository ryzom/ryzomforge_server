/** \file s_link_effect_debuff_stat.h
 * <File description>
 *
 * $Id: s_link_effect_debuff_stat.h,v 1.2 2004/03/01 19:22:18 lecroart Exp $
 */



#ifndef RY_S_LINK_EFFECT_DEBUFF_STAT_H
#define RY_S_LINK_EFFECT_DEBUFF_STAT_H

#include "nel/misc/types_nl.h"
#include "s_link_effect.h"


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
		sint32 cost,
		SCORES::TScores energyCost,
		SKILLS::ESkills skill,
		sint32 modifier,
		float multiplier,
		STAT_TYPES::TStatType type,
		uint stat,
		uint8 power)
		 :CSLinkEffectOffensive( creatorRowId,targetRowId,family,cost,energyCost, skill, modifier, power),
		 _Multiplier( multiplier ),
		_Type( type ),
		_Stat( stat )
	{
		
	}

	/**
	 * apply the effects of the... effect
	 * \return true if the effect must be removed
	 */
	bool update(uint32 & updateFlag);

protected:
	float					_Multiplier;
	sint32			  		_Stat;
	STAT_TYPES::TStatType	_Type;
	
};


#endif // RY_S_LINK_EFFECT_DEBUFF_STAT_H

/* End of s_link_effect_debuff_stat.h */
