/** \file place_type.h
 * Enumeration of different place type and convert methodes
 *
 * $Id: place_type.h,v 1.2 2006/05/31 12:15:01 boucher Exp $
 */



#ifndef RY_PLACE_TYPE_H
#define RY_PLACE_TYPE_H

#include "nel/misc/types_nl.h"

namespace PLACE_TYPE
{
	// action nature
	enum TPlaceType
	{
		Capital,
		Village,
		Outpost,
		Place,
		Street,
		Undefined,
	};

	/**
	 * convert string to enum
	 * \param str the input string
	 * \return the TPlaceType associated to this string (UNKNOWN if the string cannot be interpreted)
	 */
	TPlaceType fromString(const std::string &str);

	/**
	 * convert TPlaceType to string
	 * \param place_type the TPlaceType value
	 * \return nature as a string (or UNKNOWN)
	 */
	const std::string& toString(TPlaceType place_type);
};

#endif // RY_PLACE_TYPE_H
/* End of place_type.h */
