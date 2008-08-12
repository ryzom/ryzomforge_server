/** \file combat_stun_effect.h
 * <File description>
 *
 * $Id: combat_stun_effect.h,v 1.8 2005/02/22 10:22:29 besson Exp $
 */



#ifndef RY_COMBAT_STUN_EFFECT_H
#define RY_COMBAT_STUN_EFFECT_H

#include "phrase_manager/s_effect.h"
#include "entity_manager/entity_base.h"


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


#endif // RY_COMBAT_STUN_EFFECT_H

/* End of combat_stun_effect.h */
