/** \file s_link_effect_hot.h
 * <File description>
 *
 * $Id: s_link_effect_hot.h,v 1.20 2005/02/22 10:22:29 besson Exp $
 */



#ifndef RY_S_LINK_EFFECT_HOT_H
#define RY_S_LINK_EFFECT_HOT_H

#include "phrase_manager/s_link_effect.h"
#include "entity_manager/entity_base.h"

class CSLinkEffectHot : public CSLinkEffect
{
public:
	inline CSLinkEffectHot( const TDataSetRow & creatorRowId,
		const TDataSetRow & targetRowId,
		sint32 cost,
		SCORES::TScores energyCost,
		SKILLS::ESkills skill,
		uint32 maxDistance,
		uint8 power,
		TReportAction& report,
		sint32 healHp, sint32 healSap, sint32 healSta)
		:CSLinkEffect ( creatorRowId,targetRowId,EFFECT_FAMILIES::Hot, cost,energyCost,skill,maxDistance, 0,power,report),
		_HealHp(healHp),_HealSap(healSap),_HealSta(healSta),_FirstUpdate(true)
	{
		_MagicFxType = MAGICFX::healtoMagicFx( _HealHp,_HealSap,_HealSta,true);
		_Report.ActionNature = ACTNATURE::CURATIVE_MAGIC;
	}

	/**
	 * apply the effects of the... effect
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect);

protected:
	void applyOnScore( CEntityBase * caster, CEntityBase * target,SCORES::TScores scoreType, sint32& value );
	sint32 _HealHp;
	sint32 _HealSap;
	sint32 _HealSta;
	bool   _FirstUpdate;
};


#endif // RY_S_LINK_EFFECT_HOT_H

/* End of s_link_effect_hot.h */
