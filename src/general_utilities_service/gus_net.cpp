/** \file gus_net.cpp
 *
 * $id$
 *
 */

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

// local
#include "gus_net.h"
#include "gus_net_implementation.h"


//-----------------------------------------------------------------------------
// GUSNET namespace
//-----------------------------------------------------------------------------

namespace GUSNET
{
	//-----------------------------------------------------------------------------
	// methods CModuleMessage
	//-----------------------------------------------------------------------------

	CModuleMessage::CModuleMessage()
	{
		_SenderId= InvalidRemoteModuleId;
	}

	const NLMISC::CSString& CModuleMessage::getMessageName() const
	{
		return _MsgName;
	}

	void CModuleMessage::setMessageName(const NLMISC::CSString& name)
	{
		_MsgName= name;
	}

	uint32 CModuleMessage::getSenderId() const
	{
		return _SenderId;
	}

	void CModuleMessage::setSenderId(uint32 id)
	{
		_SenderId= id;
	}

	TRawMsgBodyPtr CModuleMessage::getMsgBody() const
	{
		return _Body;
	}

	void CModuleMessage::setMsgBody(TRawMsgBodyPtr body)
	{
		_Body= body;
	}

	const TModuleIdVector& CModuleMessage::getDestinationModuleIds() const
	{
		return _DestinationModuleIds;
	}

	void CModuleMessage::setDestinationModuleId(uint32 remoteId)
	{
		_DestinationModuleIds.clear();
		_DestinationModuleIds.push_back(remoteId);
	}

	void CModuleMessage::setDestinationModuleIds(const TModuleIdVector& remoteIds)
	{
		_DestinationModuleIds= remoteIds;
	}

	void CModuleMessage::serial(NLMISC::IStream& stream)
	{
		stream.serial(_MsgName);
		stream.serial(_SenderId);
		stream.serialCont(_DestinationModuleIds);
		if (_Body==NULL)
		{
			_Body= new CRawMsgBody;
		}
		if (_Body->isReading()!=stream.isReading())
		{
			_Body->invert();
		}
		if (stream.isReading())
		{
			_Body->clear();
		}
		stream.serialMemStream(*_Body);
	}


	//-----------------------------------------------------------------------------
	// methods CGusNet
	//-----------------------------------------------------------------------------

	// get hold of the singleton instance
	CGusNet* CGusNet::getInstance()
	{
		return CGusNetImplementation::getInstance();
	}
}
