/** \file tick_proxy.h
 * Mirror service tick proxy
 *
 * $Id: tick_proxy.h,v 1.8 2007/03/09 09:56:55 boucher Exp $
 */




#ifndef TICK_PROXY_H
#define TICK_PROXY_H

#include "nel/misc/types_nl.h"
#include "game_share/tick_proxy_time_measure.h"


enum TTickTockState
{
	ExpectingLocalTocks, ExpectingMasterTick
};


namespace NLNET
{
	class CMessage;
};


/**
 *
 */
class CTickProxy
{
public :
	
	/** 
	 * Get the current universal game time
	 */
	static const NLMISC::TGameTime getGameTime() { return _GameTime; }

	/** 
	 * Set the current universal game time
	 */
	static void setGameTime( NLMISC::TGameTime gameTime) { _GameTime = gameTime; }

	/** 
	 * Get the current step time of the tick service
	 */
	static const NLMISC::TGameTime getGameTimeStep() { return _GameTimeStep; }

	/** 
	 * Set the current game time step 
	 */
	static void setGameTimeStep( NLMISC::TGameTime gameTimeStep) { _GameTimeStep = gameTimeStep; }

	/** 
	 * Get the number of ellapsed game cycles
	 */
	static const NLMISC::TGameCycle& getGameCycle() { return _GameCycle; }

	/** 
	 * Get the number of ellapsed game cycles
	 */
	static void setGameCycle( NLMISC::TGameCycle gameCycle ) { _GameCycle = gameCycle; }

	static void setMasterTickService( NLNET::TServiceId serviceId ) { _MasterTickService = serviceId; }
	static bool alreadySyncd() { return _GameTimeStep != 0; }
	
	/// Register a client service
	static void	addService( NLNET::TServiceId serviceId );

	/// Supports any service id, even one not added before (ignored then)
	static void removeService( NLNET::TServiceId serviceId );

	static void masterTickUpdate( NLNET::TServiceId serviceId );

	static void sendSyncToClient( NLNET::TServiceId serviceId );
	static void sendSyncs();
	static void sendTicks();

	static void receiveTockFromClient( NLNET::CMessage& msgin, NLNET::TServiceId senderId, bool real=true );
	static void displayExpectedTocks( /*NLMISC::CDisplayer *log*/ );
	
	static bool checkIfAllClientTocksReceived() { if ( State != ExpectingLocalTocks ) return false; else return (_NbTocked == _Services.size()); }
	
	static void sendMasterTock();

	/// Called when nothing remains to be done in the current tick
	static void setEndOfTick();

	static const std::vector<NLNET::TServiceId>& services() { return _Services; }

	/** 
	 * Initialize the tick proxy.
	 *
	 * \param updateFunc will be called when we receive a new tick
	 * \param syncFunc will be called when the ticks send the syncro (initialisation)
	 */
	static void init( void (*updateFunc)(),
					  void (*syncFunc)() );

	static TTickTockState				State;

	static CMirrorGameCycleTimeMeasure	TimeMeasures;
	
private :

	static void	sendTockBack( NLNET::TServiceId serviceId );

	/// Time according to the game (used for determining day, night...) (double in seconds)
	static NLMISC::TGameTime	_GameTime;

	/// game time step
	static NLMISC::TGameTime	_GameTimeStep;
	
	///number of game cycles
	static NLMISC::TGameCycle	_GameCycle;

	static uint					_NbTocked;

	static TAccurateTime		_BeginOfTickTime;

	static std::vector<NLNET::TServiceId>	_Services;

	static std::vector<NLNET::TServiceId>	_TockedServices;

	static NLNET::TServiceId				_MasterTickService;

	CTickProxy() {}
};


#endif

