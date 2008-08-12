/** \file entities_game_service.h
 * entities_game_service
 *
 * $Id: entities_game_service.h,v 1.30 2007/03/09 09:56:47 boucher Exp $
 */



#ifndef EGS_ENTITIES_GAME_SERVICE_H
#define EGS_ENTITIES_GAME_SERVICE_H

#include "nel/misc/time_nl.h"
#include "nel/misc/common.h"
#include "nel/misc/log.h"
#include "nel/misc/displayer.h"
#include "nel/misc/hierarchical_timer.h"

#include "nel/net/service.h"

#include "game_share/backup_service_interface.h"
#include "world_instances.h"
#include "cdb_group.h"

// Callback connection / disconnection management
void cbConnection( const std::string &serviceName, NLNET::TServiceId sid, void *arg );
void cbDisconnection( const std::string &serviceName, NLNET::TServiceId sid, void *arg );
void cbMirrorUp( const std::string &serviceName, NLNET::TServiceId sid, void *arg );
void cbMirrorDn( const std::string &serviceName, NLNET::TServiceId sid, void *arg );

/**
 * CPlayerService
 *
 * \author Stephane Coutelas
 * \author Nevrax France
 * \date 2001
 */
class CPlayerService : 
	public NLNET::IService, 
	public CWorldInstances::IAIInstanceReady
{
public:

	/** 
	 * init the service
	 */
	void init();

	/**
	 * load the sart position and other parameters
	 */
	void initConfigFileVars();

	/**
	 * main loop
	 */
	bool update();

	/**
	 * EGS update
	 */
	static void egsUpdate();

	/**
	 * EGS synchronization
	 */
	static void egsSync();

	/**
	 * update regen due to variable change in cfg
	 */
	static void updateRegen(NLMISC::IVariable &var);

	/**
	 * release
	 */
	void release();

	// ai instance ready callback
	void onAiInstanceReady(const CReportStaticAIInstanceMsg &msg);

	// ai instance down callback
	void onAiInstanceDown(const CReportStaticAIInstanceMsg &msg);

	// call back character ready for monkey loader
	void egsAddMonkeyPlayerCallback(uint32 userId);

private:
	// monkey players load simulation
	static void egsLoadMonkey();
	
	// add a random player
	static void egsAddMonkeyPlayer();

	// remove a random player
	static void removeMonkeyPlayer();
};

extern std::string				StatPath;
extern NLMISC::CLog				EgsStat;
extern CCDBGroup				DbGroupGlobal;

#endif //EGS_ENTITIES_GAME_SERVICE_H



