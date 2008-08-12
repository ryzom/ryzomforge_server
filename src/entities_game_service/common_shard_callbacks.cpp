/** \file common_shard_callbacks.cpp
 * <File description>
 *
 * $Id: common_shard_callbacks.cpp,v 1.12 2007/03/09 09:56:47 boucher Exp $
 */



#include "stdpch.h"
#include "common_shard_callbacks.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"
#include "nel/net/unified_network.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

extern CPlayerManager				PlayerManager;

/// Received an string-id association from IOS
void cbStoreStringResult( NLNET::CMessage& msgin, const std::string &serviceName, NLNET::TServiceId serviceId )
{
	/*
	ucstring str;
	uint32 stringId;
	
	msgin.serial( str );
	msgin.serial( stringId );
	
	// put here code for other managers
	if (PlayerManager.setStringId(str, stringId))
		return;

	nlwarning("<cbStoreStringResult> unused string '%s'", str.toString().c_str() ); 
	*/
}

// received stall order form backup service due to server problem on writing player saves
void cbStallShard( NLNET::CMessage& msgin, const std::string &serviceName, NLNET::TServiceId serviceId )
{
	string filename;
	msgin.serial( filename );

	nlwarning("Backup service send Stall order when trying write %s file", filename.c_str() );
	PlayerManager.broadcastMessage( 2, 0, 5, "Technical problem occured on the server,");
	PlayerManager.broadcastMessage( 2, 0, 5, "All non administrator accounts are disconnected immediately.");
	PlayerManager.broadcastMessage( 2, 0, 5, "Customer Support is already working on it.");
	PlayerManager.broadcastMessage( 2, 0, 5, "Sorry for any inconveniences.");
	PlayerManager.broadcastMessage( 2, 0, 5, "...");
	PlayerManager.setStallMode( true );
}

// received resume order from backup service
void cbResumeShard( NLNET::CMessage& msgin, const std::string &serviceName, NLNET::TServiceId serviceId )
{
	PlayerManager.setStallMode( false );
	PlayerManager.broadcastMessage( 1, 0, 0, "Server resumed");
}



void	cbStallMode( NLNET::CMessage& msgin, const std::string &serviceName, NLNET::TServiceId serviceId )
{
	try
	{
		bool		stalled;
		std::string	reason;

		msgin.serial(stalled, reason);

		if (stalled)
		{
			CMessage	msgout("HALT_TICK");
			msgout.serial(reason);

			nlwarning("Shard stalled by %s: %s", serviceName.c_str(), reason.c_str());

			CUnifiedNetwork::getInstance()->send("TICKS", msgout);
		}
		else
		{
			CMessage	msgout("RESUME_TICK");

			nlwarning("Shard resumed by %s: %s", serviceName.c_str(), reason.c_str());

			CUnifiedNetwork::getInstance()->send("TICKS", msgout);
		}
	}
	catch (Exception&)
	{
	}

}



void CCommonShardCallbacks::init()
{
/*	/// the array of callbacks
	TUnifiedCallbackItem array[]=
	{
		{ "STORE_STRING_RESULT",					cbStoreStringResult },
		{ "STALL_SHARD",							cbStallShard		},
		{ "RESUME_SHARD",							cbResumeShard		},
	}; 
	// setup the callback array
	CUnifiedNetwork::getInstance()->addCallbackArray( array, sizeof(array)/sizeof(array[0]) );
	*/

	/// the array of callbacks
	TUnifiedCallbackItem array[]=
	{
		{ "STALL_MODE",								cbStallMode			},
	}; 
	// setup the callback array
	CUnifiedNetwork::getInstance()->addCallbackArray( array, sizeof(array)/sizeof(array[0]) );
}

void CCommonShardCallbacks::release()
{
}
