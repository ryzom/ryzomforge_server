/** \file rs_remote_saves.h
 *
 *	API for connecting to / working with SAVES modules
 *
 * $id$
 *
 */

#ifndef RS_REMOTE_SAVES_H
#define RS_REMOTE_SAVES_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

// game share
#include "game_share/file_description_container.h"

// local
#include "gus_module.h"


//-----------------------------------------------------------------------------
// SAVES namespace
//-----------------------------------------------------------------------------

namespace SAVES
{
	//-----------------------------------------------------------------------------
	// forward class decalarations
	//-----------------------------------------------------------------------------

	class CRemoteSavesInterface;
	typedef NLMISC::CSmartPtr<CRemoteSavesInterface> TRemoteSavesInterfacePtr;


	//-----------------------------------------------------------------------------
	// class IRemoteSavesConnection
	//-----------------------------------------------------------------------------

	class IRemoteSavesConnection: public GUS::IModule
	{
	public:
		virtual const CFileDescriptionContainer& getFileList() const =0;

		virtual uint32 requestFile(const NLMISC::CSString& fileName,CRemoteSavesInterface* requestor) =0;
		virtual uint32 uploadFile(const NLMISC::CSString& fileName,const NLMISC::CSString& fileBody,CRemoteSavesInterface* requestor) =0;
		virtual uint32 deleteFile(const NLMISC::CSString& fileName,CRemoteSavesInterface* requestor) =0;
		virtual uint32 moveFile(const NLMISC::CSString& fileName,const NLMISC::CSString& destination,CRemoteSavesInterface* requestor) =0;

		virtual bool isConnected() const =0;
	};
	typedef NLMISC::CSmartPtr<IRemoteSavesConnection> TRemoteSavesConnectionPtr;


	//-----------------------------------------------------------------------------
	// class CRemoteSavesManager
	//-----------------------------------------------------------------------------

	class CRemoteSavesManager: public NLMISC::CRefCount
	{
	public:
		static CRemoteSavesManager* getInstance();

		// interface used by CRemoteSavesInterface objects in their ctor to declare themselves
		virtual void registerSavesInterface(TRemoteSavesInterfacePtr si)=0;
		// interface used by CRemoteSavesInterface objects in their dtor to undeclare themselves
		virtual void unregisterSavesInterface(CRemoteSavesInterface* si)=0;

		// interface used by IRemoteSavesConnection objects in their ctor to declare themselves
		virtual void registerRemoteSavesConnectionModule(TRemoteSavesConnectionPtr connection)=0;
		// interface used by IRemoteSavesConnection objects in their dtor to undeclare themselves
		virtual void unregisterRemoteSavesConnectionModule(TRemoteSavesConnectionPtr connection)=0;

		// interface used to retrieve a pointer to a connection object for a given shard
		// a new one is instantiated if an appropriate module doesn't already exist
		virtual IRemoteSavesConnection* getConnection(const NLMISC::CSString& shardName,const NLMISC::CSString& type) const=0;
	};
}


//-----------------------------------------------------------------------------
#endif
