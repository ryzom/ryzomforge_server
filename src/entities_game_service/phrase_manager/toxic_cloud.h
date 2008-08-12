/** \file toxic_cloud.h
 * <File description>
 *
 * $Id: toxic_cloud.h,v 1.6 2005/06/23 18:14:21 boucher Exp $
 */



#ifndef NL_TOXIC_CLOUD_H
#define NL_TOXIC_CLOUD_H

#include "nel/misc/vector_2f.h"
#include "nel/misc/variable.h"
#include "game_share/base_types.h"
#include "environmental_effect.h"
#include "entity_manager/entity_base.h"

/**
 * Toxic cloud
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2003
 */
class CToxicCloud : public CEnvironmentalEffect
{
	NL_INSTANCE_COUNTER_DECL(CToxicCloud);
public:

	CToxicCloud() {};

	/// Init
	inline void		init( const NLMISC::CVector& pos, float radius, sint32 dmgPerHit, NLMISC::TGameCycle updateFrequency, NLMISC::TGameCycle lifetime=ToxicCloudDefaultLifetime) 
	{ 
		CEnvironmentalEffect::init(pos, radius,lifetime);
		_DmgPerHit = dmgPerHit;
		_UpdateFrequency = updateFrequency;
	}

	/**
	 * Spawn the toxic cloud as an entity in mirror. Return false in case of failure.
	 * \param sheet sheet id of the effect (for visual FX)
	 */
	virtual bool		spawn( const NLMISC::CSheetId &sheet );

	/// Tick update. Return false if the source's life is ended.
	virtual bool		update();

	static NLMISC::TGameCycle	ToxicCloudDefaultLifetime;

private:
	/// test target validity, returns true if target is valid
	inline bool isTargetValid(CEntityBase *entity)
	{	
#ifdef NL_DEBUG
		nlassert(entity);
#endif
		uint8 entityType = entity->getId().getType();
		switch(entityType) 
		{
		case RYZOMID::player:
			return true;

		case RYZOMID::creature:
			if (entity->getRace() == EGSPD::CPeople::MektoubMount ||  entity->getRace() == EGSPD::CPeople::MektoubPacker)
				return true;
			return false;
		
		default:
			return false;
		}
	}

	/// Dmg per hit
	sint32				_DmgPerHit;

	/// update frequency
	NLMISC::TGameCycle	_UpdateFrequency;
};


#endif // NL_TOXIC_CLOUD_H

/* End of toxic_cloud.h */
