/** \file ai_map.h
 *
 * $Id: ai_map.h,v 1.4 2004/03/01 19:19:20 lecroart Exp $
 */



class CAIMap;

#ifndef RYAI_MAP_H
#define RYAI_MAP_H

#include "nel/misc/types_nl.h"
#include "ai_route.h"

/*
	This class implements the data set and related methods for a map.
	Map data includes collision maps and so on.
*/


class CAIMap  
{
public:
	// a method for releasing self cleanly before destruction
	void release() {}

	// the name of the map
	std::string Name;
};

#endif
