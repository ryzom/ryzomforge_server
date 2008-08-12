/** \file spawn_zones_back_compat.h
 * Used for spawn zones backward compatibility with branch 1_0_1
 *
 * $Id: spawn_zones_back_compat.h,v 1.3 2004/12/08 13:26:48 besson Exp $
 */

#ifndef RY_SPAWN_ZONES_BACK_COMPAT_H
#define RY_SPAWN_ZONES_BACK_COMPAT_H

namespace BACK_COMPAT
{

void initSpawnZonesCompat();
uint16 oldToNewSpawnZoneId(uint16 oldId);

} // namespace BACK_COMPAT


#endif // RY_SPAWN_ZONES_BACK_COMPAT_H

/* End of spawn_zones_back_compat.h */
