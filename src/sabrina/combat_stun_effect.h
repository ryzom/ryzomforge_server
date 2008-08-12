/** \file combat_stun_effect.h
 * <File description>
 *
 * $Id: combat_stun_effect.h,v 1.2 2004/03/01 19:22:18 lecroart Exp $
 */



#ifndef NL_COMBAT_STUN_EFFECT_H
#define NL_COMBAT_STUN_EFFECT_H

#include "nel/misc/types_nl.h"
#include "s_effect.h"


/**
 * <Class description>
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CCombatStunEffect : public CSEffect
{
public:
	///\ctor
	CCombatStunEffect( const TDataSetRow & creatorRowId, const TDataSetRow & targetRowId, EFFECT_FAMILIES::TEffectFamily family, sint32 effectValue, uint32 endDate)
		:CSEffect(creatorRowId, targetRowId, family, effectValue,0), _StunEndDate(endDate)
	{
	}

	/**
	 *  return true if it is time to update the effect. It modifies the next update of the effect
	 */
	virtual bool isTimeToUpdate();

	/**
	 * apply the effects of the... effect
	 * \param updateFlag is a flag telling which effect type has been already processed for an entity. An effect shoud set to 1 the bit corresponding to its effect family
	 * \return true if the effect ends and must be removed
	 */
	virtual bool update( uint32 & updateFlag );

	/// callback called when the effect is actually removed
	virtual void removed();

	/// set stunned entity
	inline void stunnedEntity(CEntityBase *entity) { _StunnedEntity = entity; }

	/// get stunned entity
	inline CEntityBase *stunnedEntity() { return _StunnedEntity; }

private:
	/// effect end date in ticks
	NLMISC::TGameCycle		_StunEndDate;

	/// affected entity
	CEntityBase				*_StunnedEntity;
};


#endif // NL_COMBAT_STUN_EFFECT_H

/* End of combat_stun_effect.h */
