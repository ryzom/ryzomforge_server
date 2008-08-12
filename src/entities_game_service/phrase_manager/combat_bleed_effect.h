/** \file combat_bleed_effect.h
 * <File description>
 *
 * $Id: combat_bleed_effect.h,v 1.6 2005/02/22 10:22:30 besson Exp $
 */



#ifndef RY_COMBAT_BLEED_EFFECT_H
#define RY_COMBAT_BLEED_EFFECT_H

//
#include "phrase_manager/s_effect.h"
#include "entity_manager/entity_base.h"



/**
 * class for bleeding effects
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CCombatBleedEffect : public CSEffect
{
public:
	///\ctor
	CCombatBleedEffect( const TDataSetRow & creatorRowId, 
						const TDataSetRow & targetRowId, 
						EFFECT_FAMILIES::TEffectFamily family, 
						sint32 effectValue, 
						NLMISC::TGameCycle endDate,
						NLMISC::TGameCycle cycleLenght,
						uint16 cycleDamage
						)
		:	CSEffect(creatorRowId, targetRowId, family, effectValue,0),
			_BleedEndDate(endDate),
			_CycleLength(cycleLenght),
			_CycleDamage(cycleDamage)
	{
		_NextCycleDate = CTickEventHandler::getGameCycle() + _CycleLength;
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

	/// set bleeding entity
	inline void bleedingEntity(CEntityBase *entity) { _BleedingEntity = entity; }

	/// get bleeding entity
	inline CEntityBase *bleedingEntity() { return _BleedingEntity; }

private:
	/// effect end date in ticks
	NLMISC::TGameCycle		_BleedEndDate;

	/// next cycle date (for hp loss)
	NLMISC::TGameCycle		_NextCycleDate;

	/// cycle lenght in ticks
	NLMISC::TGameCycle		_CycleLength;

	/// number of hp lost by target each cycle
	uint16					_CycleDamage;

	/// affected entity
	CEntityBase				*_BleedingEntity;
};


#endif // NL_COMBAT_STUN_EFFECT_H

/* End of combat_stun_effect.h */
