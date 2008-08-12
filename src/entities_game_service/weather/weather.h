/** \file weather.h
 * PLAYER SERVICE
 *
 * $Id: weather.h,v 1.4 2004/12/08 13:26:48 besson Exp $
 */



#ifndef RY_WEATHER_H
#define RY_WEATHER_H

#include "game_share/cdb.h"
#include "game_share/cdb_leaf.h"
#include "game_share/cdb_branch.h"
#include "game_share/cdb_synchronised.h"

#include "game_share/weather_cfg.h"

#include "game_share/property_base_type.h"
#include "game_share/property_container.h"
#include "game_share/container_property_receiver.h"

class CWeather
{
public:
	enum EDayCycle
	{
		dawn = 0,
		day,
		twilight,
		night
	};

	// Constructor
	static void init();

	// Update Ryzom time
	static void updateRyzomTime();

	// Get Ryzom Time
	static float getRyzomTime() { return _RyzomTime.getValue(); }

	// Get Day Cycle
	static uint8 getDayCycle() { return _DayCycle.getValue(); } 

	// get string of day cycle
	static const std::string& toString( uint8 );
	
private:
	static CPropertyBaseType< float >	_RyzomTime;
	static CPropertyBaseType< uint8 >	_DayCycle;
};
#endif // RY_WEATHER_H

/* End of file weather.h */
