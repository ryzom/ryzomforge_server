/** \file places_back_compat.h
 * Used for places backward compatibility with branch 1_0_1
 *
 * $Id: places_back_compat.h,v 1.3 2004/12/08 13:26:48 besson Exp $
 */

#ifndef RY_PLACES_BACK_COMPAT_H
#define RY_PLACES_BACK_COMPAT_H


namespace BACK_COMPAT
{

void initPlacesCompat();
uint16 oldToNewPlaceId(uint16 oldId);

} // namespace BACK_COMPAT


#endif // RY_PLACES_BACK_COMPAT_H

/* End of places_back_compat.h */
