/** \file cl_module_messages.h
 *
 * $id$
 *
 */

#ifndef CL_MODULE_MESSAGES_H
#define CL_MODULE_MESSAGES_H


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "gus_net_types.h"


//-----------------------------------------------------------------------------
// class IMsgCL
//-----------------------------------------------------------------------------

class IMsgCL: public NLMISC::CRefCount
{
public:
	virtual	~IMsgCL() {}

	virtual const char* getName() const=0;
	virtual void serial(NLMISC::IStream& stream)=0;
};
typedef NLMISC::CSmartPtr<IMsgCL> TMsgCL;


//-----------------------------------------------------------------------------
// class CMsgCLText
//-----------------------------------------------------------------------------

class CMsgCLText: public IMsgCL
{
public:
	const char* getName() const { return "CL_LOG"; }

	CMsgCLText()
	{
	}

	
	CMsgCLText(GUSNET::TRawMsgBodyPtr msgBody)
	{
		msgBody->serial(*this);
	}

	CMsgCLText(const NLMISC::CSString& lang,const NLMISC::CSString& speaker,const NLMISC::CSString& txt)
	{
		_Lang= lang;
		_Speaker= speaker;
		_Txt= txt;
	}

	void serial(NLMISC::IStream& stream)
	{
		stream.serial(_Lang);
		stream.serial(_Speaker);
		stream.serial(_Txt);
	}

	const NLMISC::CSString& getLang()		{ return _Lang; }
	const NLMISC::CSString& getSpeaker()	{ return _Speaker; }
	const NLMISC::CSString& getTxt()		{ return _Txt; }

private:
	NLMISC::CSString _Lang;
	NLMISC::CSString _Speaker;
	NLMISC::CSString _Txt;
};
typedef NLMISC::CSmartPtr<CMsgCLText> TMsgCLLog;


//-----------------------------------------------------------------------------
// class CMsgCLWinner
//-----------------------------------------------------------------------------

class CMsgCLWinner: public IMsgCL
{
public:
	const char* getName() const { return "CL_WINNER"; }

	CMsgCLWinner()
	{
	}
	
	CMsgCLWinner(GUSNET::TRawMsgBodyPtr msgBody)
	{
		msgBody->serial(*this);
	}

	CMsgCLWinner(const NLMISC::CSString& winner)
	{
		_Winner= winner;
	}

	void serial(NLMISC::IStream& stream)
	{
		stream.serial(_Winner);
	}

	const NLMISC::CSString& getWinner()		{ return _Winner; }

private:
	NLMISC::CSString _Winner;
};
typedef NLMISC::CSmartPtr<CMsgCLWinner> TMsgCLWinner;


//-----------------------------------------------------------------------------
// class CMsgCLEnd
//-----------------------------------------------------------------------------

class CMsgCLEnd: public IMsgCL
{
public:
	const char* getName() const { return "CL_END"; }

	CMsgCLEnd()
	{
	}

	CMsgCLEnd(GUSNET::TRawMsgBodyPtr msgBody)
	{
		msgBody->serial(*this);
	}

	void serial(NLMISC::IStream& stream)
	{
	}

private:
};
typedef NLMISC::CSmartPtr<CMsgCLEnd> TMsgCLEnd;


//-----------------------------------------------------------------------------
#endif
