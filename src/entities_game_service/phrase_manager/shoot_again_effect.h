/** \file shoot_again_effect.h
 * <File description>
 *
 * $Id: shoot_again_effect.h,v 1.2 2007/01/03 16:20:28 coutelas Exp $
 */



#ifndef RY_SHOOT_AGAIN_EFFECT_H
#define RY_SHOOT_AGAIN_EFFECT_H

// game share
#include "game_share/scores.h"
//
#include "phrase_manager/s_effect.h"
#include "entity_manager/entity_base.h"



/** Class for shoot again proc buff (the first spell cast when this buff is in
 * effect consumes the effect)
 * \author Jerome Vuarand
 * \author Nevrax France
 * \date 2005
 * 
 * This class is inspired from CEnchantWeaponEffect and thus may have residual
 * side effects from the copy'n'paste.
*/
class CShootAgainEffect
: public CSTimedEffect
{
public:
	NLMISC_DECLARE_CLASS(CShootAgainEffect)

	CShootAgainEffect(
		TDataSetRow const& creatorRowId,
		TDataSetRow const& targetRowId,
		EFFECT_FAMILIES::TEffectFamily family,
		sint32 effectValue,
		uint32 power,
		NLMISC::TGameCycle endDate)
	: CSTimedEffect(creatorRowId, targetRowId, family, false, effectValue, power, endDate)
	{
	}
	
	/// apply the effect
	virtual bool update(CTimerEvent * event, bool applyEffect);
	
	/// callback called when the effect is actually removed
	virtual void removed();
	
	virtual NLMISC::CSheetId getAssociatedSheetId() const;

	virtual bool automaticallyReplaceFamily() const { return true; }
	
	virtual bool canBeInactive() const { return false; }

private:
	// private ctor for use in NLMISC class registry
	CShootAgainEffect() {}
};

#endif
