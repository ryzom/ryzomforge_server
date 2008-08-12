/** \file gus_net_connection.h
 *
 * $id$
 *
 */

#ifndef GUS_NET_CONNECTION_H
#define GUS_NET_CONNECTION_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "nel/net/callback_client.h"

#include "gus_module_factory.h"
#include "gus_net_types.h"


//-----------------------------------------------------------------------------
// GUSNET namespace
//-----------------------------------------------------------------------------

namespace GUSNET
{
	//-----------------------------------------------------------------------------
	// class CConnectionModule
	//-----------------------------------------------------------------------------

	class CConnectionModule: public GUS::IModule
	{
	public:
		// IModule specialisation implementation
		bool initialiseModule(const NLMISC::CSString& rawArgs);
		void release();
		void serviceUpdate(NLMISC::TTime localTime);
		NLMISC::CSString getState() const;
		NLMISC::CSString getName() const;
		NLMISC::CSString getParameters() const;
		void displayModule() const;

	public:
		// remaining public interface
		CConnectionModule();

		// management of registration / unregistration of local modules
		void registerModule(GUS::TModulePtr module);
		void unregisterModule(GUS::TModulePtr module);

		// management of registration / unregistration of remote modules
		void registerRemoteModule(TRemoteModuleViaConnectionPtr module);
		void unregisterRemoteModule(TRemoteModuleViaConnectionPtr module);
		TRemoteModuleViaConnectionPtr lookupRemoteModule(uint32 uniqueId);
		TRemoteModuleViaConnectionPtr getRemoteModuleByRemoteId(uint32 remoteId);
		bool isRemoteModuleConnected(const IRemoteModule* module) const;

		// establish a connection to a gus hub module on a gus service at the given internet address and port
		void connect(const NLMISC::CSString& address);

		// send a message to the hub for forwarding to the appropriate module(s)
		void sendMessage(const NLMISC::CSString& msgName, const TRawMsgBodyPtr& msgBody,const TModuleIdVector& remoteIds,TRemoteModuleId senderModuleId=InvalidRemoteModuleId);
		void broadcastMessage(const NLMISC::CSString& msgName, const TRawMsgBodyPtr& msgBody,TRemoteModuleId senderModuleId=InvalidRemoteModuleId);

		// treat incoming messages
		void treatBroadcastMessage(NLNET::CMessage &msgin);
		void treatModuleMessage(NLNET::CMessage &msgin);

		// simple read accessors
		const NLMISC::CSString&		getConnectionAddress() const;
		NLNET::CCallbackClient*		getCbClient() const;
		CRemoteModuleViaConnection*	getRemoteModuleByRemoteId(uint32 remoteId) const;

	private:
		// a flag that tracks state changes from connected to not connected and back
		bool _IsConnected;
		uint32 _ReconnectDelayCounter;

		// private data
		NLMISC::CSString _ConnectionAddress;

		// the callback server for the network connection
		NLNET::CCallbackClient* _CbClient;

		// the set of remote modules (ie modules visible via the different hubs) - indexed by remote id
		typedef std::map<uint32,TRemoteModuleViaConnectionPtr> TRemoteModules;
		TRemoteModules _RemoteModules;
	};
}

//-----------------------------------------------------------------------------
#endif
