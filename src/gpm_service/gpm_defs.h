/** \file world_position_manager.h
 * This class manage world position of all entiy in shard, manage entity move and collide, 
 * respond to all messages around a position in world
 *
 * $Id: gpm_defs.h,v 1.4 2004/03/01 19:22:05 lecroart Exp $
 */



#ifndef RY_GPM_DEFS_H
#define RY_GPM_DEFS_H

#include "nel/misc/types_nl.h"

const uint16	MAX_SEEN_ENTITIES = 255;
const uint16	MAX_SEEN_OBJECTS = 64;
const sint32	GLOBAL_POSITION_TAG = 0x80000000;
const uint8		INVALID_CONTINENT_INDEX = 0xff;
const uint8		NO_CONTINENT_INDEX = 0xfe;

#define RECORD_LAST_PLAYER_POSITIONS


#endif
