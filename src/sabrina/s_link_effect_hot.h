/** \file s_link_effect_hot.h
 * <File description>
 *
 * $Id: s_link_effect_hot.h,v 1.2 2004/03/01 19:22:18 lecroart Exp $
 */



#ifndef RY_S_LINK_EFFECT_HOT_H
#define RY_S_LINK_EFFECT_HOT_H

#include "nel/misc/types_nl.h"


#include "nel/misc/types_nl.h"
#include "s_link_effect.h"

class CSLinkEffectHot : public CSLinkEffect
{
public:
	inline CSLinkEffectHot( const TDataSetRow & creatorRowId,
		const TDataSetRow & targetRowId,
		sint32 cost,
		SCORES::TScores energyCost,
		SKILLS::ESkills skill, 
		uint8 power,
		sint32 healHp, sint32 healSap, sint32 healSta)
		:CSLinkEffect ( creatorRowId,targetRowId,EFFECT_FAMILIES::Hot,cost,energyCost,skill,0,power),
		_HealHp(healHp),_HealSap(healSap),_HealSta(healSta)
	{
	}

	/**
	 * apply the effects of the... effect
	 * \return true if the effect must be removed
	 */
	bool update(uint32 & updateFlag);

protected:
	void applyOnScore( CEntityBase * caster, CEntityBase * target,SCORES::TScores scoreType, sint32 value );
	sint32 _HealHp;
	sint32 _HealSap;
	sint32 _HealSta;
};


#endif // RY_S_LINK_EFFECT_HOT_H

/* End of s_link_effect_hot.h */
