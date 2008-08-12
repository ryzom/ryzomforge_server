/** \file gus_net_types.h
 *
 * common type definitions used in gus net modules
 *
 * $id$
 *
 */

#ifndef GUS_NET_TYPES_H
#define GUS_NET_TYPES_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "nel/misc/smart_ptr.h"
#include "nel/misc/mem_stream.h"


//-----------------------------------------------------------------------------
// GUS namespace
//-----------------------------------------------------------------------------

namespace GUS
{
	//-----------------------------------------------------------------------------
	// forward class declarations
	//-----------------------------------------------------------------------------

	class IModule;
	class CModuleManager;
}


//-----------------------------------------------------------------------------
// GUSNET namespace
//-----------------------------------------------------------------------------

namespace GUSNET
{
	//-----------------------------------------------------------------------------
	// forward class declarations
	//-----------------------------------------------------------------------------

	class CConnectionModule;
	class CHubModule;

	class IRemoteModule;
	class CRemoteModuleOnHub;
	class CRemoteModuleViaConnection;

	// messages
	class CModuleMessage;
	class CMsgRegisterModule;


	//-----------------------------------------------------------------------------
	// class CRawMsgBody
	//-----------------------------------------------------------------------------

	class CRawMsgBody: public NLMISC::CRefCount, public NLMISC::CMemStream
	{
	};
	typedef NLMISC::CSmartPtr<CRawMsgBody> TRawMsgBodyPtr;


	//-----------------------------------------------------------------------------
	// global typedefs
	//-----------------------------------------------------------------------------

	typedef std::vector<uint32> TModuleIdVector;
	typedef uint32 TRemoteModuleId;
	const TRemoteModuleId InvalidRemoteModuleId=~0u;


	//-----------------------------------------------------------------------------
	// public pointer type definitions
	//-----------------------------------------------------------------------------

	typedef NLMISC::CSmartPtr<CHubModule>			THubModulePtr;
	typedef NLMISC::CSmartPtr<CConnectionModule>	TConnectionModulePtr;

	typedef NLMISC::CSmartPtr<IRemoteModule> TRemoteModulePtr;
	typedef NLMISC::CSmartPtr<CRemoteModuleOnHub> TRemoteModuleOnHubPtr;
	typedef NLMISC::CSmartPtr<CRemoteModuleViaConnection> TRemoteModuleViaConnectionPtr;
}

//-----------------------------------------------------------------------------
#endif
