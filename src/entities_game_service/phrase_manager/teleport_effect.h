/** \file teleport_effect.h
 * <File description>
 *
 * $Id: teleport_effect.h,v 1.6 2005/02/22 10:22:29 besson Exp $
 */

#ifndef RY_TELEPORT_EFFECT_H
#define RY_TELEPORT_EFFECT_H


//
#include "entity_manager/entity_base.h"
#include "phrase_manager/s_effect.h"

class TDataSetRow;
class CStaticItem;

/**
 * class for teleport effects. Used when player uses a teleport
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CTeleportEffect : public CSTimedEffect
{
public:
	///\ctor
	CTeleportEffect( const TDataSetRow & creatorRowId, 
						const TDataSetRow & targetRowId, 
						EFFECT_FAMILIES::TEffectFamily family, 
						sint32 effectValue, 
						NLMISC::TGameCycle endDate,
						const CStaticItem & form
						);

	virtual bool update(CTimerEvent * event, bool applyEffect){ return false; }
	/// callback called when the effect is actually removed
	virtual void removed();

private:
	const CStaticItem & _Form;
};


#endif // RY_TELEPORT_EFFECT_H

/* End of teleport_effect.h */
