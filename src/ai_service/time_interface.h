/** \file time_interface.h
 *
 * $Id: time_interface.h,v 1.14 2005/04/26 12:37:02 brigand Exp $
 */




#ifndef RYAI_TIME_INTERFACE_H
#define RYAI_TIME_INTERFACE_H

// Nel Misc
#include "nel/misc/types_nl.h"
#include "nel/net/service.h"

// Game share
//#include "game_share/container_property_receiver.h"
//#include "game_share/property_manager_template.h"
#include "game_share/time_weather_season/time_date_season_manager.h"
#include "game_share/ryzom_entity_id.h"
#include "game_share/mirror_prop_value.h"


// the class
class CTimeInterface
{
//	friend void cbRyzomTimeSync( NLNET::CMessage& msgin, const std::string &serviceName, uint16 serviceId );

public:
	// a few important sets of constants
//	typedef CRyzomTime::ESeason ESeason ;
//	typedef CRyzomTime::ETimeOfDay ETimeOfDay;
//	typedef CRyzomTime::EWeather EWeather;

	// classic init(), update() and release()
	static void init()
	{
		_TimeDateSeason.init	();
		updateDay	();
	}

	static void update()
	{
		_TimeDateSeason.tickUpdate();		
		updateDay	();
	}

	static	void	updateDay	()
	{
		CRyzomTime::ETimeOfDay time=timeOfDay();
		_isDay	=	time==CRyzomTime::day	||	time==CRyzomTime::dawn;
	}

	static void release()
	{
	}

	static	const	bool	&isDay	()
	{
		return	_isDay;
	}

	// the key read accessors
	inline	static uint32		gameCycle()
	{
		return	CTickEventHandler::getGameCycle();
	}
	
	inline	static CRyzomTime::ETimeOfDay	timeOfDay()
	{
		return	_TimeDateSeason.getDayCycle();
	}
	
	inline	static	const	CRyzomTime	&getRyzomTime	()
	{
		return	_TimeDateSeason.getRyzomTimeReference();
	}

	inline	static	CRyzomTime	&getRyzomDebugTime	()
	{
		return	_DebugTime;
	}

	inline	static	CRyzomTime::ESeason	season()
	{
		return	_TimeDateSeason.getRyzomTimeReference().getRyzomSeason();
	}

//
//	inline	static EWeather		weather( uint8 continent )
//	{	}
	// -- to be completed ... --

	// Ryzom time class
//	static CRyzomTime	RyzomTime;

//	static	CMirrorPropValueRO<uint8> _CurrentDayCycle;

//	static	float	_PrevTime;
private:
	static	CTimeDateSeasonManager	_TimeDateSeason;
	static	CRyzomTime				_DebugTime;
	static	bool					_isDay;
};

// call back for synchronize time and day
void cbRyzomTimeSync( NLNET::CMessage& msgin, const std::string &serviceName, uint16 serviceId );

#endif
