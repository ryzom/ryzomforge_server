/** \file s_effect.h
 * <File description>
 *
 * $Id: s_effect.h,v 1.2 2004/03/01 19:22:18 lecroart Exp $
 */




#ifndef RY_S_EFFECT_H
#define RY_S_EFFECT_H


#include "nel/misc/types_nl.h"
#include "game_share/effect_families.h"
#include "game_share/damage_types.h"
#include "game_share/base_types.h"

/**
 * Class representing an effect managed by the EGS
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2003
 */
class CSEffect
{
public:

	///\ctor
	inline CSEffect( const TDataSetRow & creatorRowId, const TDataSetRow & targetRowId, EFFECT_FAMILIES::TEffectFamily family, sint32 effectValue, uint8 power)
		:_CreatorRowId(creatorRowId),_TargetRowId(targetRowId),_Family(family),_Value(effectValue),_Power(power)
	{
	}

	/**
	 *  return true if it is time to update the effect. It modifies the next update of the effect
	 */
	virtual bool isTimeToUpdate() = 0;

	/**
	 * apply the effects of the... effect
	 * \param updateFlag is a flag telling which effect type has been already processed for an entity. An effect shoud set to 1 the bit corresponding to its effect family
	 * \return true if the effect ends must be removed
	 */
	virtual bool update( uint32 & updateFlag ) = 0;

	/// callback called when the effect is actually removed. Does nothing by default
	virtual void removed(){};

	///\name accessors
	//@{
	inline uint32							getEffectId()		const{ return	_EffectId;}
	inline EFFECT_FAMILIES::TEffectFamily	getFamily()			const{ return	_Family;}
	inline const TDataSetRow &				getCreatorRowId()	const{ return	_CreatorRowId;}
	inline const TDataSetRow &				getTargetRowId()	const{ return	_TargetRowId;}
	inline sint32							getParamValue()		const{ return	_Value;}
	inline uint8							getPower()			const{ return	_Power;}
	//@}
	
	///\set the id of the effect. Should be set by the effect manager
	inline void setEffectId(uint32 id)	{ _EffectId = id; }

protected:
	/// effect creator Id
	TDataSetRow						_CreatorRowId;
	/// effect target Id
	TDataSetRow						_TargetRowId;
	/// effect family
	EFFECT_FAMILIES::TEffectFamily	_Family;
	/// effect ID
	uint32							_EffectId;
	/// effect Value
	sint32							_Value;
	/// power of the effect (to be counter with cures)
	uint8							_Power;
};




#endif // RY_S_EFFECT_H


/* End of s_effect.h */
