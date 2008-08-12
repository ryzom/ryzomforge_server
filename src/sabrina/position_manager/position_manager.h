/** \file position_manager.h
 * Manager for entities positions
 *
 * $Id: position_manager.h,v 1.2 2004/03/01 19:22:19 lecroart Exp $
 */



#ifndef RY_POSITION_MANAGER_H
#define RY_POSITION_MANAGER_H

// misc
#include "nel/misc/types_nl.h"
#include "nel/misc/vector.h"
//
#include "sabrina_actor.h"


/**
 * Entities position manager, provides an interface for positions related requests
 * \author Fleury David
 * \author Nevrax France
 * \date 2003
 */
class CPositionManager
{
	/// getInstance
	static inline CPositionManager *getInstance()
	{
		if (_Instance == NULL)
			_Instance = new CPositionManager();
	
		return _Instance;
	}

	/**
	 * get all the entities in the given area around a center entity (2D distance test)
	 * \param centerEntity pointer on the entity which is the area center
	 * \param radius selected area radius in meters
	 * \param selectedEntities vector that will receive all the selected entities
	 * \param testLOS flag indicating if we should test LOS (includes only entities which are in center's entity LOS)
	 */
	void getEntitiesInArea( const ISabrinaActor *centerEntity, double radius, std::vector<ISabrinaActor*> &selectedEntities, bool testLOS = true );

	/**
	 * test if an entity is in the line of sight of another entity (3D test always)
	 * \param sourceEntity pointer on the first entity (the one looking)
	 * \param targetEntity pointer on the targeted entity
	 * \return true if the source can see the target, false otherwise
	 */
	bool isInLineOfSight( const ISabrinaActor *sourceEntity, const ISabrinaActor *targetEntity );

private:
	/**
	 * private constructor (singleton)
	 */
	 CPositionManager() {}

private:
	/// unique instance
	static CPositionManager*	_Instance;
};

#endif// RY_POSITION_MANAGER_H
