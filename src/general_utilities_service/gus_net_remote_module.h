/** \file gus_net_remote_module.h
 *
 * $id$
 *
 */

#ifndef GUS_NET_REMOTE_MODULE_H
#define GUS_NET_REMOTE_MODULE_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "nel/net/callback_net_base.h"
#include "nel/misc/smart_ptr.h"
#include "nel/misc/sstring.h"

#include "gus_net_types.h"


//-----------------------------------------------------------------------------
// GUSNET namespace
//-----------------------------------------------------------------------------

namespace GUSNET
{
	//-----------------------------------------------------------------------------
	// class IRemoteModule
	//-----------------------------------------------------------------------------

	class IRemoteModule: public NLMISC::CRefCount
	{
	public:
		// ctor & virtual dtor
		IRemoteModule();
		virtual ~IRemoteModule();

		// display the module id and description
		virtual const NLMISC::CSString getInfoString() const=0;

		// read accessors
		virtual NLNET::TSockId getSockId() const=0;
		virtual uint32 getRemoteId() const=0;
		virtual uint32 getUniqueId() const=0;
		virtual const NLMISC::CSString& getName() const=0;
		virtual const NLMISC::CSString& getParameters() const=0;

		// message send routines
		virtual void sendMessage(const NLMISC::CSString& msgName, TRawMsgBodyPtr msgBody, TRemoteModuleId senderModuleId=InvalidRemoteModuleId)=0;

	protected:
		uint32 _UniqueId;
	};


	//-----------------------------------------------------------------------------
	// class CRemoteModuleViaConnection
	//-----------------------------------------------------------------------------

	class CRemoteModuleViaConnection: public IRemoteModule
	{
	public:
		// ctor
		CRemoteModuleViaConnection();

		// try to initialise self from msg and return false if there's a problem
		bool init(TConnectionModulePtr connection,CMsgRegisterModule& msg);

		// display the module id and description
		const NLMISC::CSString getInfoString() const;

		// read accessors
		const TConnectionModulePtr getConnection() const;
		NLNET::TSockId getSockId() const;
		uint32 getRemoteId() const;
		uint32 getUniqueId() const;
		const NLMISC::CSString& getName() const;
		const NLMISC::CSString& getParameters() const;

		// message send routines
		void sendMessage(const NLMISC::CSString& msgName, TRawMsgBodyPtr msgBody, TRemoteModuleId senderModuleId=InvalidRemoteModuleId);

	private:
		TConnectionModulePtr _Connection;
		uint32 _RemoteId;
		NLMISC::CSString _Name;
		NLMISC::CSString _Parameters;
	};


	//-----------------------------------------------------------------------------
	// class CRemoteModuleOnHub
	//-----------------------------------------------------------------------------

	class CRemoteModuleOnHub: public IRemoteModule
	{
	public:
		// ctor
		CRemoteModuleOnHub();

		// try to initialise self from msg and return false if there's a problem
		bool init(THubModulePtr hub,NLNET::TSockId tsid,CMsgRegisterModule& msg);

		// construct a module description message to forward to a new hub connection
		void buildDescriptionMsg(CMsgRegisterModule& msg);

		// display the module id and description
		const NLMISC::CSString getInfoString() const;

		// read accessors
		const THubModulePtr getHub() const;
		NLNET::TSockId getSockId() const;
		uint32 getRemoteId() const;
		uint32 getUniqueId() const;
		const NLMISC::CSString& getName() const;
		const NLMISC::CSString& getParameters() const;

		// message send routines
		void sendMessage(const NLMISC::CSString& msgName, TRawMsgBodyPtr msgBody, TRemoteModuleId senderModuleId=InvalidRemoteModuleId);

	private:
		THubModulePtr _Hub;
		NLNET::TSockId _SockId;
		uint32 _RemoteId;
		NLMISC::CSString _Name;
		NLMISC::CSString _Parameters;
	};
}

//-----------------------------------------------------------------------------
#endif
