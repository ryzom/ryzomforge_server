/** \file building_enums.h
 * <File description>
 *
 * $Id: building_enums.h,v 1.2 2004/12/08 13:26:46 besson Exp $
 */

#ifndef RY_BUILDING_ENUMS_H
#define RY_BUILDING_ENUMS_H

namespace ROOM_RESTRICTION
{
	// restriction to have a valid destination
	enum TRestriction
	{
		Rm_Fight,
		Rm_Magic,
		Rm_Harvest,
		Rm_Craft,
		Unknown,
	};
	
	TRestriction fromString( const std::string & str );
}

namespace BUILDING_TYPES
{
	// restriction to have a valid destination
	enum TBuildingType
	{
		Common,
		Player,
		Guild,
		Unknown,
	};
	
	TBuildingType fromString( const std::string & str );
}



#endif // RY_BUILDING_ENUMS_H

/* End of building_enums.h */

