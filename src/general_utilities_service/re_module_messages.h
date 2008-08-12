/** \file re_module_messages.h
 *
 * $id$
 *
 */

#ifndef RE_MODULE_MESSAGES_H
#define RE_MODULE_MESSAGES_H


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "nel/misc/sstring.h"
#include "gus_net_types.h"


//-----------------------------------------------------------------------------
// class CMsgRERequestFile
//-----------------------------------------------------------------------------

class CMsgRERequestFile
{
public:
	const char* getName() const { return "RE_REQUEST"; }

	CMsgRERequestFile()
	{
	}
	
	CMsgRERequestFile(GUSNET::TRawMsgBodyPtr msgBody)
	{
		msgBody->serial(*this);
	}

	CMsgRERequestFile(const NLMISC::CSString& fileName)
	{
		_FileName= fileName;
	}

	void serial(NLMISC::IStream& stream)
	{
		stream.serial(_FileName);
	}

	const NLMISC::CSString& getFileName() const { return _FileName; }

private:
	NLMISC::CSString _FileName;
};


//-----------------------------------------------------------------------------
// class CMsgREFileDataAck
//-----------------------------------------------------------------------------

class CMsgREFileDataAck
{
public:
	const char* getName() const { return "RE_DATA_ACK"; }

	CMsgREFileDataAck()
	{
	}
	
	CMsgREFileDataAck(GUSNET::TRawMsgBodyPtr msgBody)
	{
		msgBody->serial(*this);
	}

	CMsgREFileDataAck(const NLMISC::CSString& fileName,bool status)
	{
		_FileName= fileName;
		_Status= status;
	}

	void serial(NLMISC::IStream& stream)
	{
		stream.serial(_FileName);
		stream.serial(_Status);
	}

	const NLMISC::CSString& getFileName() const { return _FileName; }
	bool getStatus() const						{ return _Status; }

private:
	NLMISC::CSString _FileName;
	bool _Status;
};


//-----------------------------------------------------------------------------
// class CMsgREDuplicateModuleError
//-----------------------------------------------------------------------------

class CMsgREDuplicateModuleError
{
public:
	const char* getName() const { return "RE_ERR_DUPMOD"; }

	CMsgREDuplicateModuleError()
	{
	}
	
	CMsgREDuplicateModuleError(GUSNET::TRawMsgBodyPtr msgBody)
	{
	}

	void serial(NLMISC::IStream& stream)
	{
	}

private:
};


//-----------------------------------------------------------------------------
#endif
