/** \file weather_everywhere.h
 * <File description>
 *
 * $Id: weather_everywhere.h,v 1.7 2004/12/08 13:26:43 besson Exp $
 */



#ifndef NL_WEATHER_EVERYWHERE_H
#define NL_WEATHER_EVERYWHERE_H

#include "game_share/time_weather_season/weather_function.h"
#include "game_share/time_weather_season/time_and_season.h"


/**
 * Utility class to query the weather at any time and position.
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2004
 */
class CWeatherEverywhere
{
public:

	/// Constructor
	CWeatherEverywhere() : _WeatherFunctionParamsSheet(NULL) {}

	/// Destructor
	~CWeatherEverywhere();

	/// Initialization (must be called after the initialization of static sheets)
	void						init();

	/**
	 * Return the weather at the specified position & time.
	 * In case of failure (such as a position outside a continent), return unknownWeather.
	 */
	CRyzomTime::EWeather		getWeather( const NLMISC::CVector& pos, const CRyzomTime& ryzomTime ) const;

private:

	/// All weather functions (the vector contains a pointer to EGSPD::CSeason::Invalid values)
	std::vector< CWeatherFunction * >				_WeatherFunctionsBySeasonByContinent;

	/// Pointer to the weather function parameter sheet
	const class CWeatherFunctionParamsSheetBase		*_WeatherFunctionParamsSheet;
};


/// Singleton instance
extern CWeatherEverywhere	WeatherEverywhere;


#endif // NL_WEATHER_EVERYWHERE_H

/* End of weather_everywhere.h */
