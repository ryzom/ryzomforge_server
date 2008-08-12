/** \file special_power_taunt.h
 * Specialized class for power "taunt"
 *
 * $Id: special_power_taunt.h,v 1.8 2004/12/08 13:26:44 besson Exp $
 */



#ifndef RYZOM_SPECIAL_POWER_TAUNT_H
#define RYZOM_SPECIAL_POWER_TAUNT_H

#include "special_power.h"


/**
 * Specialized class for power "taunt"
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CSpecialPowerTaunt : public CSpecialPower
{
public:
	/// Default Constructor
	CSpecialPowerTaunt() : CSpecialPower()
	{}

	/// Constructor
	CSpecialPowerTaunt(TDataSetRow actorRowId, CSpecialPowerPhrase *phrase, uint16 power, float range, float disableTimeInSeconds) 
		: _TauntPower(power), _Range(range)
	{
		_Phrase = phrase;
		
		_DisablePowerTime = uint32(disableTimeInSeconds / CTickEventHandler::getGameTimeStep());

		_PowerType = POWERS::Taunt;
		
		if(TheDataset.isAccessible(actorRowId))
			_ActorRowId = actorRowId;
		else
		{
			nlwarning("<CSpecialPowerTaunt> invalid data set row passed as actor");
		}
	}

	/// validate the power utilisation
	virtual bool validate(std::string &errorCode);

	/// apply effects
	virtual void apply();

protected:
	/**
     *test if the taunt works on given entity
	 * \param entity the entity to taunt
	 * \return true if the taunt is successful, false otherwise
	 */
	bool testTauntSuccessOnEntity(const CEntityBase *entity);

protected:
	/// taunt power (cannot taunt creatures above this "level")
	uint16	_TauntPower;

	/// max range in meters
	float	_Range;
};

#endif // RYZOM_SPECIAL_POWER_TAUNT_H

/* End of special_power_taunt.h */
