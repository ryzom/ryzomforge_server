/** \file ai_route_beeline.h
 *
 * $Id: ai_route_beeline.h,v 1.5 2004/03/01 19:19:20 lecroart Exp $
 */



class CAIRouteBeeline;

#ifndef RYAI_ROUTE_BEELINE_H
#define RYAI_ROUTE_BEELINE_H

#include "nel/misc/types_nl.h"
#include "ai_route.h"

/*
	This class implements beeline routes towards points - it is the most
	basic form of pathfinding imaginable
*/


class CAIRouteBeeline: public CAIRoute
{
public:
	// ctors and dtors -------------------------------------------------
	CAIRouteBeeline(CAIPos destination)
	{
		_destination=destination;
	}

public:
	// respecting the inheritted interface -----------------------------

	virtual double getDirection(CAIPos currentCoord);
	virtual bool haveArrived(CAIPos currentCoord,uint dist);

private:
	CAIPos _destination;
};


//----------------------------------------------------------------------
// methods

double CAIRouteBeeline::getDirection(CAIPos currentCoord)
{
	return currentCoord.directionTo(_destination);
}

double CAIRouteBeeline::haveArrived(CAIPos currentCoord,uint dist)
{
	return currentCoord.distTo(_destination)<=dist;
}

#endif
