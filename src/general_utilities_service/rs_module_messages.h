/** \file rs_module_messages.h
 *
 * $id$
 *
 */

#ifndef RS_MODULE_MESSAGES_H
#define RS_MODULE_MESSAGES_H


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

// game share
#include "game_share/file_description_container.h"

// local
#include "gus_net_types.h"


//-----------------------------------------------------------------------------
// SAVES namespace
//-----------------------------------------------------------------------------

namespace SAVES
{
	//-----------------------------------------------------------------------------
	// class CMsgRSInit
	//-----------------------------------------------------------------------------

	class CMsgRSInit: public NLMISC::CRefCount
	{
	public:
		static const char* getName() 
		{
			return "RS_INIT"; 
		}

		CMsgRSInit()
		{
		}
		
		CMsgRSInit(GUSNET::TRawMsgBodyPtr msgBody)
		{
			msgBody->serial(*this);
		}

		CMsgRSInit(const CFileDescriptionContainer& fileList)
		{
			_FileList=	fileList;
		}

		void serial(NLMISC::IStream& stream)
		{
			stream.serial(_FileList);
		}

		const CFileDescriptionContainer& getFileList()	const	
		{
			return _FileList; 
		}

	private:
		CFileDescriptionContainer	_FileList;
	};
	typedef NLMISC::CSmartPtr<CMsgRSInit> TMsgRSInitPtr;


	//-----------------------------------------------------------------------------
	// class CMsgRSDownload
	//-----------------------------------------------------------------------------

	class CMsgRSDownload: public NLMISC::CRefCount
	{
	public:
		static const char* getName() 
		{
			return "RS_DOWNLOAD"; 
		}

		CMsgRSDownload()
		{
		}
		
		CMsgRSDownload(GUSNET::TRawMsgBodyPtr msgBody)
		{
			msgBody->serial(*this);
		}

		CMsgRSDownload(uint32 requestId,const NLMISC::CSString& fileName,const NLMISC::CSString& fileBody)
		{
			_RequestId=	requestId;
			_FileName=	fileName;
			_FileBody=	fileBody;
		}

		void serial(NLMISC::IStream& stream)
		{
			stream.serial(_RequestId);
			stream.serial(_FileName);
			stream.serial(_FileBody);
		}

		const uint32 getRequestId()	const	
		{
			return _RequestId;
		}

		const NLMISC::CSString& getFileName()	const	
		{
			return _FileName; 
		}

		const NLMISC::CSString& getFileBody()	const	
		{
			return _FileBody; 
		}

	private:
		uint32				_RequestId;
		NLMISC::CSString	_FileName;
		NLMISC::CSString	_FileBody;
	};
	typedef NLMISC::CSmartPtr<CMsgRSDownload> TMsgRSDownloadPtr;


	//-----------------------------------------------------------------------------
	// class CMsgRSUpdate
	//-----------------------------------------------------------------------------

	class CMsgRSUpdate: public NLMISC::CRefCount
	{
	public:
		static const char* getName() 
		{
			return "RS_UPDATE"; 
		}

		CMsgRSUpdate()
		{
		}
		
		CMsgRSUpdate(GUSNET::TRawMsgBodyPtr msgBody)
		{
			msgBody->serial(*this);
		}

		void serial(NLMISC::IStream& stream)
		{
			stream.serial(_NewFiles);
			stream.serial(_ChangedFiles);
			stream.serialCont(_DeletedFiles);
		}

		void addNew(const NLMISC::CSString& fileName,uint32 timeStamp,uint32 size)
		{
			_NewFiles.addFile(fileName,timeStamp,size);
		}

		void addChange(const NLMISC::CSString& fileName,uint32 timeStamp,uint32 size)
		{
			_ChangedFiles.addFile(fileName,timeStamp,size);
		}

		void addDeleted(const NLMISC::CSString& fileName)
		{
			_DeletedFiles.push_back(fileName);
		}

		bool empty()
		{
			return _NewFiles.empty() && _ChangedFiles.empty() && _DeletedFiles.empty();
		}

		const CFileDescriptionContainer& getNewFiles()	const	
		{
			return _NewFiles; 
		}

		const CFileDescriptionContainer& getChangedFiles()	const	
		{
			return _ChangedFiles; 
		}

		const NLMISC::CVectorSString& getDeletedFiles()	const	
		{
			return _DeletedFiles; 
		}

	private:
		CFileDescriptionContainer	_NewFiles;
		CFileDescriptionContainer	_ChangedFiles;
		NLMISC::CVectorSString		_DeletedFiles;
	};
	typedef NLMISC::CSmartPtr<CMsgRSUpdate> TMsgRSUpdatePtr;


	//-----------------------------------------------------------------------------
	// class CMsgRSGenericReply
	//-----------------------------------------------------------------------------

	class CMsgRSGenericReply: public NLMISC::CRefCount
	{
	public:
		static const char* getName() 
		{
			return "RS_REPLY"; 
		}

		CMsgRSGenericReply()
		{
		}
		
		CMsgRSGenericReply(GUSNET::TRawMsgBodyPtr msgBody)
		{
			msgBody->serial(*this);
		}

		CMsgRSGenericReply(uint32 requestId,bool succesFlag,const NLMISC::CSString& explanation)
		{
			_RequestId=		requestId;
			_SuccesFlag=	succesFlag;
			_Explanation=	explanation;
		}

		void serial(NLMISC::IStream& stream)
		{
			stream.serial(_RequestId);
			stream.serial(_SuccesFlag);
			stream.serial(_Explanation);
		}

		const uint32 getRequestId()	const	
		{
			return _RequestId;
		}

		const bool getSuccesFlag()	const	
		{
			return _SuccesFlag;
		}

		const NLMISC::CSString& getExplanation()	const	
		{
			return _Explanation; 
		}

	private:
		uint32				_RequestId;
		bool				_SuccesFlag;
		NLMISC::CSString	_Explanation;
	};
	typedef NLMISC::CSmartPtr<CMsgRSGenericReply> TMsgRSReplyPtr;
}


//-----------------------------------------------------------------------------
#endif
