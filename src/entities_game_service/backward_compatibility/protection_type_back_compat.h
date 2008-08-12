/** \file protection_type_back_compat.h
 * Used for backward compatibility with old item protection system
 *
 * $Id: protection_type_back_compat.h,v 1.2 2005/10/03 15:52:19 guignot Exp $
 */



#ifndef RY_PROTECTION_TYPE_BACK_COMPAT_H
#define RY_PROTECTION_TYPE_BACK_COMPAT_H

#include "nel/misc/types_nl.h"

namespace BACK_COMPAT
{
namespace OLD_PROTECTION_TYPE
{

enum TOldProtectionType
{
	Cold = 0,
	Acid,
	Rot,
	Fire,			// Fyros speciality
	Shockwave,		// Tryker speciality
	Poison,			// Matis speciality
	Electricity,	// Zorai speciality
	Madness,
	Slow,
	Snare,
	Sleep,
	Stun,
	Root,
	Blind,
	Fear,
	
	None,
	
	NB_OLD_PROTECTION_TYPE = None
};

TOldProtectionType fromString(const std::string & str);
const std::string & toString(TOldProtectionType oldType);

} // namespace OLD_PROTECTION_TYPE
} // namespace BACK_COMPAT


#endif // RY_PROTECTION_TYPE_BACK_COMPAT_H

