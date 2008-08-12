/** \file ai_route.h
 *
 * $Id: ai_route.h,v 1.8 2004/03/01 19:19:20 lecroart Exp $
 */



//class CAIRoute;

#ifndef RYAI_ROUTE_H
#define RYAI_ROUTE_H

//#include "nel/misc/types_nl.h"
#include "ai_share/ai_coord.h"
#include "ai_pos.h"

/*
	This is the virtual base class for abstracting pathfinding algorithms
	Routes are generaly spawned by CAIPlace classes (the 'place' is the destination)
*/


class CAIRoute
{
public:
	virtual ~CAIRoute() {}
	// get direction vector from current coordinate
	virtual double getDirection(CAIPos currentCoord)=0;

	// have we arrived at the destination
	// - dist defines the distance that the entity moves/ tick
	// returns true if distance from currentCoord to dest <= dist
	virtual bool haveArrived(CAIPos currentCoord,uint dist)=0;
};

#endif
