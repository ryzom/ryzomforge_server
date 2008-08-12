/** \file bleed_effect.h
 * <File description>
 *
 * $Id: bleed_effect.h,v 1.11 2007/01/03 16:20:28 coutelas Exp $
 */



#ifndef RY_BLEED_EFFECT_H
#define RY_BLEED_EFFECT_H

//
#include "phrase_manager/s_effect.h"
#include "entity_manager/entity_base.h"


struct CSlaveBleedEffect
{
	CSlaveBleedEffect() : CycleDamage(0.0f), EndDate(0) {}

	/// number of hp lost by target each cycle
	float				CycleDamage;
	/// effect end date
	NLMISC::TGameCycle	EndDate;
};

/**
 * class for bleeding effects
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CBleedEffect : public CSTimedEffect
{
public:
	NLMISC_DECLARE_CLASS(CBleedEffect)

	///\ctor
	CBleedEffect( const TDataSetRow & creatorRowId, 
						const TDataSetRow & targetRowId, 
						EFFECT_FAMILIES::TEffectFamily family, 
						sint32 effectValue, 
						NLMISC::TGameCycle endDate,
						NLMISC::TGameCycle cycleLength,
						float cycleDamage
						)
		:	CSTimedEffect(creatorRowId, targetRowId, family, true, effectValue,(uint8)cycleDamage, endDate)
	{
		_CycleLength = cycleLength;

		CSlaveBleedEffect effect;
		effect.CycleDamage = cycleDamage;
		effect.EndDate = endDate;
		_Effects.push_back(effect);
	}

	/**
	 * apply the effects of the... effect
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect);

	/// callback called when the effect is actually removed
	virtual void removed();

	/// set bleeding entity
	inline void bleedingEntity(CEntityBase *entity) { _BleedingEntity = entity; }

	/// get cycle length
	inline NLMISC::TGameCycle getCycleLength() const { return _CycleLength; }

	/**
	 * bleeding effect are special, as they often occurs using a melee stanza and are stackable, instead of
	 * having many instances we keep only one effect. CycleLength MUST BE IDENTICAL
	 */
	void stackWithEffect(float cycleDamage, NLMISC::TGameCycle endDate)
	{
		CSlaveBleedEffect effect;
		effect.CycleDamage = cycleDamage;
		effect.EndDate = endDate;
		_Effects.push_back(effect);

		if (endDate > _EndDate)
		{
			_EndDate = endDate;
			_EndTimer.set(_EndDate, new CEndEffectTimerEvent(this));
		}
	}

private:
	/// cycle lenght in ticks
	NLMISC::TGameCycle		_CycleLength;

	/// number of hp lost by target each cycle
	float					_CycleDamage;
	/// fraction of hp when not integer (0-1)
	float					_RemainingDamage;

	/// affected entity
	CEntityBaseRefPtr		_BleedingEntity;

	/// slave effects
	std::list<CSlaveBleedEffect> _Effects;

	// private ctor for use in NLMISC class registry
	CBleedEffect() {}
};


#endif // RY_BLEED_EFFECT_H

/* End of bleed_effect.h */
