/** \file range_selector.h
 * <File description>
 *
 * $Id: range_selector.h,v 1.18 2004/12/14 16:25:35 besson Exp $
 */



#ifndef RY_RANGE_SELECTOR_H
#define RY_RANGE_SELECTOR_H

#include "entity_matrix.h"

/**
 * <Class description>
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2003
 */
class CRangeSelector
{
public:
	
	/// init the range selector with the specified entity
	/// actor 
	/// x,y are the initial position , in EGS coords ( millimeters, y < 0, x > 0)
	/// radius is the radius in meters
	void buildDisc( CEntityBase * actor, sint32 x, sint32 y,float radius, CEntityMatrix & matrix, bool offensiveAction, bool ignoreMainTarget = false);

	/// init the range selector with the specified disc
	/// source is the cone source
	/// target is the initial point of the cone
	/// height is the height of the cone in meters
	/// minWidth is the minimum width of the cone (in meter  )
	/// maxWidth is the maximum width of the cone (in meter )
	/// dist is the distance between the 2 entities ( in meter ) ( passed in param because already computed before most of the time )
	///
	///	     minWidth
	///	   /---------\
	///	  /   |       \
	///	 /    | height \
	/// /     |         \
	// /-----------------\
	///     maxWidth
	void buildCone(CEntityBase* source , CEntityBase* target,float height,float minWidth, float maxWidth, CEntityMatrix & matrix, bool offensiveAction, bool ignoreMainTarget = false);

	void buildChain( CEntityBase* actor, CEntityBase* target, float range,uint maxEntities, CEntityMatrix & matrix, ACTNATURE::TActionNature nature, bool ignoreMainTarget = false);

	inline void clear()
	{
		_Entities.clear();
	}

	inline const std::vector< CEntityBase* > & getEntities()
	{
		return _Entities;
	}

	inline const std::vector< float > & getDistances()
	{
		return _Distances;
	}
	
	
protected:
	
	/// entities affected by the area. Slot zero is the main entity
	std::vector< CEntityBase* >			_Entities;
	/// distances from main target. We store the distance between caster and main target in slot 0
	std::vector< float >		_Distances;
};


#endif // RY_RANGE_SELECTOR_H

/* End of range_selector.h */






