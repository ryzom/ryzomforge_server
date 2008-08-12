/** \file environmental_effect.h
 * <File description>
 *
 * $Id: environmental_effect.h,v 1.6 2005/06/23 18:14:20 boucher Exp $
 */



#ifndef NL_ENVIRONMENTAL_EFFECT_H
#define NL_ENVIRONMENTAL_EFFECT_H

#include "nel/misc/vector_2f.h"
#include "game_share/base_types.h"
#include "egs_mirror.h"

#include "phrase_manager/simple_entity_manager.h"

/**
 * Environmental Effect
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CEnvironmentalEffect
{
	NL_INSTANCE_COUNTER_DECL(CEnvironmentalEffect);
public:

	inline CEnvironmentalEffect() { _TimeToLive = 0; _Radius = 0.0f; }

	/// Virtual destructor (required for proper NL_INSTANCE_COUNTER_DECL count of derived classes)
	virtual ~CEnvironmentalEffect() {}

	/// Init
	inline void			init( const NLMISC::CVector& pos, float radius, NLMISC::TGameCycle lifetime=DefaultLifetime ) { _Pos = pos; _Radius = radius; _TimeToLive = lifetime; }

	/**
	 * Spawn the effect as an entity in mirror. Return false in case of failure.
	 * \param sheet sheet id of the effect (for visual FX)
	 */
	virtual bool		spawn( const NLMISC::CSheetId &sheet ) = 0;

	/// Tick update. Return false if the source's life has ended.
	virtual bool		update();

	// Accessors
	inline const TDataSetRow&		rowId() const { return _DataSetRow; }
	inline const NLMISC::CVector2f&	pos() const { return _Pos; }
	inline const float&				radius() const { return _Radius; }
	inline const NLMISC::TGameCycle&timeToLive() const { return _TimeToLive; }
	
	static NLMISC::TGameCycle	DefaultLifetime;

protected:
	/// Despawn the toxic cloud in mirror
	void				despawn();

protected:
	/// Entity representing the effect, valid after spawn()
	TDataSetRow			_DataSetRow;

	/// Position (coordinates in meters)
	NLMISC::CVector2f	_Pos;

	/// Radius
	float				_Radius;

	/// Toxic cloud remaining Time To Live (in ticks, decremented by every update)
	NLMISC::TGameCycle	_TimeToLive;
};


/**
 * Environmental effect manager class
 */
class CEnvironmentalEffectManager : public CSimpleEntityManager<CEnvironmentalEffect>
{
	NL_INSTANCE_COUNTER_DECL(CEnvironmentalEffectManager);
public:

	/// Singleton access
	static CEnvironmentalEffectManager *getInstance() { return (CEnvironmentalEffectManager*)_Instance; }

	/// Release
	static void	release() { delete (CEnvironmentalEffectManager*)_Instance; }
};




#endif // NL_ENVIRONMENTAL_EFFECT_H

/* End of environmental_effect.h */
