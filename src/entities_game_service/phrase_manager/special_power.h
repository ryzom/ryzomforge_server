/** \file special_power.h
 * Base class for special powers
 *
 * $Id: special_power.h,v 1.16 2005/06/23 18:14:21 boucher Exp $
 */



#ifndef RYZOM_SPECIAL_POWER_H
#define RYZOM_SPECIAL_POWER_H

//
#include "entity_manager/entity_base.h"
//
#include "game_share/power_types.h"

class CSpecialPowerPhrase;


/**
 * Base class for special powers
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CSpecialPower
{
	NL_INSTANCE_COUNTER_DECL(CSpecialPower);
public:
	/// Constructor
	CSpecialPower() : _Phrase(NULL), _ApplyOnTargets(true), _PowerType(POWERS::UnknownType), _DisablePowerTime(0)
	{}

	/// validate the power utilisation
	virtual bool validate(std::string &errorCode);

	/// apply effects
	virtual void apply() {}

	/// apply on targets or on actor
	inline bool applyOnTargets() const { return _ApplyOnTargets; }
	inline void applyOnTargets(bool b) { _ApplyOnTargets = b; }

protected:
	/// actor
	TDataSetRow			_ActorRowId;

	/// flag indicating if the action is done on the combat phrase targets or actor
	bool				_ApplyOnTargets;

	/// special power type
	POWERS::TPowerType	_PowerType;

	// disable power for x ticks
	NLMISC::TGameCycle	_DisablePowerTime;

	/// related phrase
	CSpecialPowerPhrase	*_Phrase;
};

/**
 * Base class for special powers
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CSpecialPowerAuras : public CSpecialPower
{
public:
	/// Constructor
	CSpecialPowerAuras() : CSpecialPower()
	{
		_TargetsDisableAuraTime = 0;
		_AuraRadius = 0.0f;
		_AffectGuild = false;
	}

	/// validate the power utilisation
	virtual bool validate(std::string &errorCode);

	// getRadius
	inline float getRadius() const { return _AuraRadius; }

	// setRadius
	inline void setRadius(float radius) { _AuraRadius = radius; }

	/// set affect guild flag
	inline void affectGuild(bool flag) { _AffectGuild = flag; }
	
protected:
	// disable this aura on targets for x ticks
	NLMISC::TGameCycle	_TargetsDisableAuraTime;
	// radius of the aura
	float				_AuraRadius;
	/// affect guild members ? (always affect teammates)
	bool				_AffectGuild;
};

#endif // RYZOM_SPECIAL_POWER_H

/* End of special_power.h */
