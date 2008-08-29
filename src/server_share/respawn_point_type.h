/** \file respawn_point_type.h
 * definition of re-spawn point
 *
 * $Id: respawn_point_type.h,v 1.6 2004/09/28 16:24:07 brigand Exp $
 */



#ifndef RYZOM_RESPAWN_POINT_TYPE_H
#define RYZOM_RESPAWN_POINT_TYPE_H

#include "nel/misc/types_nl.h"

#include <string>

namespace RESPAWN_POINT
{
	enum TRespawnPointType
	{
		KAMI = 0,
		KARAVAN,
		NEWBIELAND,
		OUTPOST,
		RESPAWNABLE,
		NORMAL,// invalid flag ( but != from unknown as we use this enum for spawn zone that are not player respawn points after death ). I know it is not the best name but we had to choose it because of AI compatiblity purposes
		UNKNOWN,
		NB_RESPAWN_POINT_TYPE = UNKNOWN
	};


	/**
	 * get respawn point type corresponding to input string
	 * \param str the input string
	 * \return the TRespawnPointType associated to this string (UNKNOWN if the string cannot be interpreted)
	 */
	TRespawnPointType toRespawnPointType(const std::string &str);

	/**
	 * get the respawn point type string corresponding to enum
	 * \param type the TRespawnPointType value
	 * \return type as a string (or UNKNOWN)
	 */
	const std::string& toString(TRespawnPointType type);
}; // RESPAWN_POINT

#endif // RYZOM_RESPAWN_POINT_TYPE_H
/* End of respawn_point_type.h */
