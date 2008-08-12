/** \file damage_aura_effect.h
 * <File description>
 *
 * $Id: damage_aura_effect.h,v 1.7 2007/01/03 16:20:28 coutelas Exp $
 */



#ifndef RY_DAMAGE_AURA_EFFECT_H
#define RY_DAMAGE_AURA_EFFECT_H

//
#include "phrase_manager/s_effect.h"
#include "entity_manager/entity_base.h"



/**
 * class for damage auras effects (like Stench)
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CDamageAuraEffect : public CSTimedEffect
{
public:
	NLMISC_DECLARE_CLASS(CDamageAuraEffect)

	///\ctor
	CDamageAuraEffect() : CSTimedEffect()
	{
		_AffectAttackableEntities = false;
		_AffectPlayers = true;
		_AuraRadius = 0.0f;
	}

	///\ctor
	CDamageAuraEffect( const TDataSetRow & creatorRowId, 
						const TDataSetRow & targetRowId, 
						EFFECT_FAMILIES::TEffectFamily family, 
						sint32 effectValue, 
						NLMISC::TGameCycle endDate,
						NLMISC::TGameCycle cycleLenght,
						uint16 cycleDamage,
						float radius = 5.0f
						)
		:	CSTimedEffect(creatorRowId, targetRowId, family, true, effectValue,(uint8)cycleDamage, endDate),
			_CycleLength(cycleLenght),
			_CycleDamage(cycleDamage)
	{
		_AffectAttackableEntities = false;
		_AffectPlayers = true;
		_AuraRadius = radius;
	}

	/**
	 * apply the effects of the... effect
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect);

	/// callback called when the effect is actually removed
	virtual void removed();
	/// set radius
	inline void setRadius(float radius) { _AuraRadius = radius; }	

	/// accessors on _AffectAttackableEntities
	void affectAttackableEntities(bool b) { _AffectAttackableEntities = b; }
	bool affectAttackableEntities() const { return _AffectAttackableEntities; }

	void affectPlayers(bool b) { _AffectPlayers = b; }
	bool affectPlayers() const { return _AffectPlayers; }

private:
	/// check entity is a valid target
	bool isEntityValidTarget(CEntityBase *entity) const;

private:
	/// cycle lenght in ticks
	NLMISC::TGameCycle		_CycleLength;

	/// number of hp lost by surrounding entities each cycle
	uint16					_CycleDamage;

	/// aura radius in meters
	float					_AuraRadius;

	/// affect players ?
	bool					_AffectPlayers;
	/// affect attackable entities
	bool					_AffectAttackableEntities;

	/// affected entity
	mutable CEntityBaseRefPtr	_AffectedEntity;
};


#endif // RY_DAMAGE_AURA_EFFECT_H

/* End of damage_aura_effect.h */
