/** \file ai_continent.h
 *
 * $Id: ai_continent.h,v 1.6 2004/03/01 19:19:20 lecroart Exp $
 */



class CAIContinent;

#ifndef RYAI_CONTINENT_H
#define RYAI_CONTINENT_H

#include "nel/misc/types_nl.h"
#include "ai_route.h"

/*
	This class implements the data set and related methods for a continent.
	Continent data includes collision maps and so on.
*/


class CAIContinent  
{
public:
	// classic init(), update() and release()
	static void init()		{}
	static void update()	{}
	static void release()	{}

	// the name of the continent
	std::string Name;
};

#endif
