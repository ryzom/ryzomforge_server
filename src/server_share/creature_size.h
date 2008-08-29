/** \file creature_size.h
 * definition of the different creatue size (small, homin, big)
 *
 * $Id: creature_size.h,v 1.3 2004/03/01 19:21:52 lecroart Exp $
 */



#ifndef RY_CREATURE_SIZE_H
#define RY_CREATURE_SIZE_H

#include "nel/misc/types_nl.h"

namespace CREATURE_SIZE
{
	// Size
	enum ECreatureSize
	{
		SMALL = 0,
		HOMIN,
		BIG,

		// the number of size existing
		NB_SIZE,

		UNKNOWN,
	};


	/**
	 * get the ECreatureSize size from the input string
	 * \param str the input string
	 * \return the ECreatureSize associated to this string (UNKNOWN if the string cannot be interpreted)
	 */
	ECreatureSize stringToCreatureSize(const std::string &str);


	/**
	 * get the ECreatureSize size as a string
	 * \param size the ECreatureSize size
	 * \return the string associated to this ECreatureSize
	 */
	const std::string &creatureSizeToString(ECreatureSize size);


}; // CREATURE_SIZE

#endif // RY_CREATURE_SIZE_H
/* End of creature_size.h */
