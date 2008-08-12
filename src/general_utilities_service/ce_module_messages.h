/** \file ce_module_messages.h
 *
 * $id$
 *
 */

#ifndef CE_MODULE_MESSAGES_H
#define CE_MODULE_MESSAGES_H


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "gus_net_types.h"


//-----------------------------------------------------------------------------
// class CMsgCERegister
//-----------------------------------------------------------------------------

class CMsgCERegister: public NLMISC::CRefCount
{
public:
	static const char* getName() { return "CE_REGISTER"; }

	CMsgCERegister()
	{
	}

	CMsgCERegister(GUSNET::TRawMsgBodyPtr msgBody)
	{
		msgBody->serial(*this);
	}

	CMsgCERegister(const NLMISC::CSString& txt)
	{
		_Txt= txt;
	}

	void serial(NLMISC::IStream& stream)
	{
		stream.serial(_Txt);
	}

	const NLMISC::CSString& getTxt()		{ return _Txt; }

private:
	NLMISC::CSString _Txt;
};
typedef NLMISC::CSmartPtr<CMsgCERegister> TMsgCERegisterPtr;


//-----------------------------------------------------------------------------
// class CMsgCEWinner
//-----------------------------------------------------------------------------

class CMsgCEWinner
{
public:
	static const char* getName() { return "CE_WINNER"; }

	CMsgCEWinner()
	{
	}

	CMsgCEWinner(GUSNET::TRawMsgBodyPtr msgBody)
	{
		msgBody->serial(*this);
	}

	CMsgCEWinner(const NLMISC::CSString& winnerName)
	{
		_WinnerName= winnerName;
	}

	void serial(NLMISC::IStream& stream)
	{
		stream.serial(_WinnerName);
	}

	const NLMISC::CSString& getWinnerName()		{ return _WinnerName; }

private:
	NLMISC::CSString _WinnerName;
};
typedef NLMISC::CSmartPtr<CMsgCEWinner> TMsgCEWinnerPtr;


//-----------------------------------------------------------------------------
#endif
