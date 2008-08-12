/** \file spell_target.h
 * class used for spell targets
 *
 * $Id: spell_target.h,v 1.6 2004/12/08 13:26:44 besson Exp $
 */



#ifndef RY_SPELL_TARGET_H
#define RY_SPELL_TARGET_H

/////////////
// INCLUDE //
/////////////
// Game Share
#include "game_share/mirror_prop_value.h"

/**
 * Structure used for spell targets (to fill TargetList mirror property)
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CSpellTarget
{
public:
	CSpellTarget(){}

	CSpellTarget(TDataSetRow id) : _TargetRowId(id){}

	/// set row id, and reset data
	inline void setId(TDataSetRow id) { _TargetRowId = id; }
	// get target id
	inline const TDataSetRow & getId() const { return _TargetRowId; }
	
protected:
	/// target row id
	TDataSetRow		_TargetRowId;
};


#endif // RY_SPELL_TARGET_H

/* End of spell_target.h */
