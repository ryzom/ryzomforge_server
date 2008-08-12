/** \file weather.cpp
 * PLAYER SERVICE
 *
 * $Id: weather.cpp,v 1.5 2005/02/08 18:59:04 boucher Exp $
 */



#include "stdpch.h"

#include "weather.h"

//	#include "game_share/property_manager_template.h"
//	#include "game_share/property_manager_container_template.h"
#include "game_share/cdb.h"
#include "game_share/cdb_leaf.h"
#include "game_share/cdb_branch.h"
#include "game_share/cdb_synchronised.h"

using namespace NLMISC;
using namespace std;

CMirrorPropValue< float >	CWeather::_RyzomTime;
CMirrorPropValue< uint8 >	CWeather::_DayCycle;

//-----------------------------------------------
// constructor
//-----------------------------------------------
void CWeather::init()
{ 
	NL_ALLOC_CONTEXT(WTHR_INIT);
	WeatherCfg.load( WeatherFileName ); 

ztrhetjyuety


	CPropertyManager * manager = CContainerPropertyEmiter::getPropertyManager( string("RyzomTime") );
	if( manager == 0 )
	{
		manager = new CSpecializedPropertyManager<float>( "RyzomTime", 0);
		CContainerPropertyEmiter::addPropertyManager( manager );
	}
	static_cast<CSpecializedPropertyManager<float> *>(manager)->addProperty( RYZOMID::World, &_RyzomTime );

	manager = CContainerPropertyEmiter::getPropertyManager( string("DayCycle") );
	if( manager == 0 )
	{
		manager = new CSpecializedPropertyManager<uint8>( "DayCycle", 0);
		CContainerPropertyEmiter::addPropertyManager( manager );
	}
	static_cast<CSpecializedPropertyManager<uint8> *>(manager)->addProperty( RYZOMID::World, &_DayCycle );
}

//-----------------------------------------------
// Update Ryzom time
//-----------------------------------------------
void CWeather::updateRyzomTime()
{
	uint32 Time = (uint32) ( CTickEventHandler::getGameTime() + 500) % ( (uint32) ( WeatherCfg.RealDayLength ) );
	float RyzomTime = Time * WeatherCfg.NumHours / WeatherCfg.RealDayLength;
	_RyzomTime = RyzomTime;

	if( ( RyzomTime < WeatherCfg.DawnTransitionStartHour ) || ( RyzomTime > WeatherCfg.NightTransitionEndHour ) )
	{
		_DayCycle = night;
	}
	else if( RyzomTime < WeatherCfg.DawnTransitionEndHour )
	{
		_DayCycle = dawn;
	}
	else if( RyzomTime < WeatherCfg.NightTransitionStartHour )
	{
		_DayCycle = day;
	}
	else
	{
		_DayCycle = twilight;
	}
}

static string DawnString("dawn");
static string DayString("day");
static string TwilightString("twilight");
static string NightString("night");
static string UnknownString("Unknown");

//-----------------------------------------------
// get string of day cycle
//-----------------------------------------------
const std::string& CWeather::toString( uint8 c )
{
	switch( c )
	{
		case dawn:
			return DawnString;
		case day:
			return DayString;
		case twilight:
			return TwilightString;
		case night:
			return NightString;
		default:
			return UnknownString;
	}
}
