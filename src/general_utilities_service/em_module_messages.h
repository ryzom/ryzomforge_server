/** \file em_module_messages.h
 *
 * $id$
 *
 */

#ifndef EM_MODULE_MESSAGES_H
#define EM_MODULE_MESSAGES_H


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "nel/misc/md5.h"
#include "game_share/file_description_container.h"
#include "gus_net_types.h"


//-----------------------------------------------------------------------------
// class CMsgEMLoginReply
//-----------------------------------------------------------------------------

class CMsgEMLoginReply: public NLMISC::CRefCount
{
public:
	static const char* getName() 
	{
		return "EM_LOGIN_REPLY"; 
	}

	CMsgEMLoginReply()
	{
	}

	CMsgEMLoginReply(GUSNET::TRawMsgBodyPtr msgBody)
	{
		msgBody->serial(*this);
	}

	CMsgEMLoginReply(bool accepted, const NLMISC::CSString& resultTxt)
	{
		_Accepted=		accepted;
		_ResultTxt=		resultTxt;
	}

	void serial(NLMISC::IStream& stream)
	{
		stream.serial(_Accepted);
		stream.serial(_ResultTxt);
	}

	bool isAccepted()	const						
	{
		return _Accepted; 
	}

	const NLMISC::CSString& getResultTxt()	const	
	{
		return _ResultTxt; 
	}

private:
	bool				_Accepted;
	NLMISC::CSString	_ResultTxt;
};
typedef NLMISC::CSmartPtr<CMsgEMLoginReply> TMsgEMLoginReplyPtr;


//-----------------------------------------------------------------------------
// class CMsgEMUploadReply
//-----------------------------------------------------------------------------

class CMsgEMUploadReply: public NLMISC::CRefCount
{
public:
	static const char* getName() 
	{
		return "EM_UPLOAD_REPLY"; 
	}

	CMsgEMUploadReply()
	{
	}

	CMsgEMUploadReply(GUSNET::TRawMsgBodyPtr msgBody)
	{
		msgBody->serial(*this);
	}

	CMsgEMUploadReply(bool accepted, const NLMISC::CSString& resultTxt)
	{
		_Accepted=		accepted;
		_ResultTxt=		resultTxt;
	}

	void serial(NLMISC::IStream& stream)
	{
		stream.serial(_Accepted);
		stream.serial(_ResultTxt);
	}

	bool isAccepted()	const						
	{
		return _Accepted; 
	}

	const NLMISC::CSString& getResultTxt()	const	
	{
		return _ResultTxt; 
	}

private:
	bool				_Accepted;
	NLMISC::CSString	_ResultTxt;
};
typedef NLMISC::CSmartPtr<CMsgEMUploadReply> TMsgEMUploadReplyPtr;


////-----------------------------------------------------------------------------
//// class CMsgEMRestartShardReply
////-----------------------------------------------------------------------------
//
//class CMsgEMRestartShardReply: public NLMISC::CRefCount
//{
//public:
//	static const char* getName() 
//	{
//		return "EM_RESTART_SHARD_REPLY"; 
//	}
//
//	CMsgEMRestartShardReply()
//	{
//	}
//	
//	CMsgEMRestartShardReply(GUSNET::TRawMsgBodyPtr msgBody)
//	{
//		msgBody->serial(*this);
//	}
//
//	CMsgEMRestartShardReply(const NLMISC::CSString& resultTxt)
//	{
//		_ResultTxt=		resultTxt;
//	}
//
//	void serial(NLMISC::IStream& stream)
//	{
//		stream.serial(_ResultTxt);
//	}
//
//	const NLMISC::CSString& getResultTxt()	const	
//	{
//		return _ResultTxt; 
//	}
//
//private:
//	NLMISC::CSString	_ResultTxt;
//};
//typedef NLMISC::CSmartPtr<CMsgEMRestartShardReply> TMsgEMRestartShardReplyPtr;


//-----------------------------------------------------------------------------
// class CMsgEMPeekReply
//-----------------------------------------------------------------------------

class CMsgEMPeekReply: public NLMISC::CRefCount
{
public:
	static const char* getName() 
	{
		return "EM_PEEK_REPLY"; 
	}

	CMsgEMPeekReply()
	{
	}
	
	CMsgEMPeekReply(GUSNET::TRawMsgBodyPtr msgBody)
	{
		msgBody->serial(*this);
	}

	CMsgEMPeekReply(const NLMISC::CSString& resultTxt,const CFileDescriptionContainer& fdc)
	{
		_ResultTxt=		resultTxt;
		_Fdc=			fdc;
	}

	void serial(NLMISC::IStream& stream)
	{
		stream.serial(_ResultTxt);
		stream.serial(_Fdc);
	}

	const NLMISC::CSString& getResultTxt()	const	
	{
		return _ResultTxt; 
	}

	const CFileDescriptionContainer& getFdc()	const	
	{
		return _Fdc; 
	}

private:
	NLMISC::CSString			_ResultTxt;
	CFileDescriptionContainer	_Fdc;
};
typedef NLMISC::CSmartPtr<CMsgEMPeekReply> TMsgEMPeekReplyPtr;


//-----------------------------------------------------------------------------
// class CMsgEMToolsUpdReply
//-----------------------------------------------------------------------------

class CMsgEMToolsUpdReply: public NLMISC::CRefCount
{
public:
	static const char* getName() 
	{
		return "EM_TOOLS_UPDATE_REPLY"; 
	}

	CMsgEMToolsUpdReply()
	{
	}
	
	CMsgEMToolsUpdReply(GUSNET::TRawMsgBodyPtr msgBody)
	{
		msgBody->serial(*this);
	}

	CMsgEMToolsUpdReply(const NLMISC::CSString& resultTxt)
	{
		_ResultTxt=		resultTxt;
	}

	void addFile(const std::string& fileName,const NLMISC::CHashKeyMD5& checkSum,uint32 fileSize)
	{
		_Files.resize(_Files.size()+1);
		_Files.back().FileName= fileName;
		_Files.back().CheckSum= checkSum;
		_Files.back().FileSize= fileSize;
	}

	void serial(NLMISC::IStream& stream)
	{
		stream.serial(_ResultTxt);
		stream.serialCont(_Files);
	}

	const NLMISC::CSString& getResultTxt()	const	
	{
		return _ResultTxt; 
	}

	uint32 getNumFiles() const
	{
		return _Files.size();
	}

	const NLMISC::CSString& getFileName(uint32 idx) const
	{
		nlassert(idx<_Files.size());
		return _Files[idx].FileName;
	}

	const NLMISC::CHashKeyMD5& getCheckSum(uint32 idx) const
	{
		nlassert(idx<_Files.size());
		return _Files[idx].CheckSum;
	}

	uint32 getFileSize(uint32 idx) const
	{
		nlassert(idx<_Files.size());
		return _Files[idx].FileSize;
	}

private:
	struct CFileInfo
	{
		NLMISC::CSString	FileName;
		NLMISC::CHashKeyMD5	CheckSum;
		uint32				FileSize;
		void serial(NLMISC::IStream& stream)
		{
			stream.serial(FileName);
			stream.serial(FileSize);
			std::string checkSumString= CheckSum.toString();
			stream.serial(checkSumString);
			CheckSum.fromString(checkSumString);
		}
	};
	typedef std::vector<CFileInfo> TFiles;
	TFiles						_Files;
	NLMISC::CSString			_ResultTxt;
};
typedef NLMISC::CSmartPtr<CMsgEMToolsUpdReply> TMsgEMToolsUpdReplyPtr;


//-----------------------------------------------------------------------------
// class CMsgEMToolsFileReply
//-----------------------------------------------------------------------------

class CMsgEMToolsFileReply: public NLMISC::CRefCount
{
public:
	static const char* getName() 
	{
		return "EM_TOOLS_FILE_REPLY"; 
	}

	CMsgEMToolsFileReply()
	{
	}
	
	CMsgEMToolsFileReply(GUSNET::TRawMsgBodyPtr msgBody)
	{
		msgBody->serial(*this);
	}

	CMsgEMToolsFileReply(const NLMISC::CSString& resultTxt,const NLMISC::CSString& fileName,const NLMISC::CSString& fileData)
	{
		_ResultTxt=		resultTxt;
		_FileName=		fileName;
		_FileData=		fileData;
	}

	void serial(NLMISC::IStream& stream)
	{
		stream.serial(_ResultTxt);
		stream.serial(_FileName);
		stream.serial(_FileData);
	}

	const NLMISC::CSString& getResultTxt()	const	
	{
		return _ResultTxt; 
	}

	const NLMISC::CSString& getFileName()	const	
	{
		return _FileName;
	}

	const NLMISC::CSString& getFileData()	const	
	{
		return _FileData;
	}

private:
	NLMISC::CSString			_ResultTxt;
	NLMISC::CSString			_FileName;
	NLMISC::CSString			_FileData;
};
typedef NLMISC::CSmartPtr<CMsgEMToolsFileReply> TMsgEMToolsFileReplyPtr;


//-----------------------------------------------------------------------------
#endif
