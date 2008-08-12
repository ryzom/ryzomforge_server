/** \file slow_move_effect.h
 * <File description>
 *
 * $Id: slow_move_effect.h,v 1.5 2007/01/03 16:20:28 coutelas Exp $
 */



#ifndef RY_SLOW_MOVE_EFFECT_H
#define RY_SLOW_MOVE_EFFECT_H

//
#include "phrase_manager/s_effect.h"
#include "phrase_manager/phrase_utilities_functions.h"


/**
 * class for slow move effects
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CSlowMoveEffect : public CSTimedEffect
{
public:
	NLMISC_DECLARE_CLASS(CSlowMoveEffect)

	///\ctor
	CSlowMoveEffect() 
	{_SlowedEntity = NULL; _FirstUpdate = true;}

	CSlowMoveEffect( const TDataSetRow & creatorRowId, 
						const TDataSetRow & targetRowId, 
						EFFECT_FAMILIES::TEffectFamily family, 
						sint32 effectValue, // should be -100..0, -20 means -20%
						NLMISC::TGameCycle endDate,
						CEntityBase *slowedEntity
						)
		:	CSTimedEffect(creatorRowId, targetRowId, family, false, effectValue, (uint8)abs(effectValue), endDate),
			_FirstUpdate(true), _SlowedEntity(slowedEntity)
	{
		if (slowedEntity)
			DEBUGLOG("EFFECT: create slow move effect (value %d) on entity %s", _Value, _SlowedEntity->getId().toString().c_str());
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

private:
	/// affected entity
	CEntityBase				*_SlowedEntity;

	/// flag, true if first update
	bool					_FirstUpdate;
};


#endif // RY_SLOW_MOVE_EFFECT_H

/* End of slow_move_effect.h */
