/** \file basic_effect.h
 * <File description>
 *
 * $Id: basic_effect.h,v 1.6 2004/03/01 19:21:52 lecroart Exp $
 */



#ifndef RY_BASIC_EFFECT_H
#define RY_BASIC_EFFECT_H

#include "nel/misc/types_nl.h"
#include "game_share/base_types.h"
#include "game_share/effect_families.h"


/**
 * <Class description>
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CBasicEffect
{
public:
	/// Constructor
	CBasicEffect(EFFECT_FAMILIES::TEffectFamily family, const TDataSetRow & creatorId, const TDataSetRow & targetRowId) 
	: _Family(family), _CreatorRowId(creatorId), _TargetRowId(targetRowId)
	{
		_EffectId = ++_EffectCounter;
	}

	CBasicEffect( EFFECT_FAMILIES::TEffectFamily family, const TDataSetRow & creatorId, const TDataSetRow & targetRowId, uint32 effectId ) 
		: _Family(family), _CreatorRowId(creatorId), _TargetRowId(targetRowId), _EffectId(effectId)
	{
	}



	/// Destructor
	virtual ~CBasicEffect() {}

	/// get the effect creator Id
	inline const TDataSetRow &creatorRowId() const { return _CreatorRowId; }
	
	/// get the effect target rowId
	inline const TDataSetRow &targetRowId() const { return _TargetRowId; }

	/// get the effect family
	inline EFFECT_FAMILIES::TEffectFamily family() const { return _Family; }

	/// get the effect Id
	inline uint32 effectId() const { return _EffectId; }

	/// get the effect counter
	inline static uint32 effectCounter() { return _EffectCounter; }

protected:
	/// effect creator Id
	TDataSetRow						_CreatorRowId;

	/// effect target Id
	TDataSetRow						_TargetRowId;

	/// effect family
	EFFECT_FAMILIES::TEffectFamily	_Family;

	/// effect ID
	uint32							_EffectId;

	/// counter, increased by one with every effect creation, give a unique Id per effect
	static uint32					_EffectCounter;
};


#endif // RY_BASIC_EFFECT_H

/* End of basic_effect.h */
