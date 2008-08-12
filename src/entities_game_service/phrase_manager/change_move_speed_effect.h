/** \file change_move_speed_effect.h
 * <File description>
 *
 * $Id: change_move_speed_effect.h,v 1.9 2007/01/03 16:20:28 coutelas Exp $
 */



#ifndef RY_CHANGE_MOVE_SPEED_EFFECT_H
#define RY_CHANGE_MOVE_SPEED_EFFECT_H

//
#include "phrase_manager/s_effect.h"
#include "phrase_manager/phrase_utilities_functions.h"
#include "entity_manager/entity_base.h"


/**
 * class for haste or snare effects
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CChangeMoveSpeedEffect : public CSTimedEffect
{
public:
	NLMISC_DECLARE_CLASS(CChangeMoveSpeedEffect)
		
	///\ctor
	CChangeMoveSpeedEffect() 
	{}

	CChangeMoveSpeedEffect( const TDataSetRow & creatorRowId, 
						const TDataSetRow & targetRowId, 
						EFFECT_FAMILIES::TEffectFamily family, 
						sint32 effectValue, // in % of base speed >0 haste, <0 snare
						NLMISC::TGameCycle endDate,
						CEntityBase *affectedEntity
						)
		:	CSTimedEffect(creatorRowId, targetRowId, family, false, effectValue, abs(effectValue), endDate),
			_AffectedEntity(affectedEntity)
	{
		_AffectedEntity = affectedEntity;
		if (_AffectedEntity)
			DEBUGLOG("EFFECT: create slow move effect (value %d) on entity %s", _Value, _AffectedEntity->getId().toString().c_str());
	}

	/**
	 * apply the effects of the... effect
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect);

	/// callback called when the effect is actually removed
	virtual void removed();

private:
	/// affected entity
	CEntityBaseRefPtr		_AffectedEntity;
};


#endif // RY_CHANGE_MOVE_SPEED_EFFECT_H

/* End of change_move_speed_effect.h */
