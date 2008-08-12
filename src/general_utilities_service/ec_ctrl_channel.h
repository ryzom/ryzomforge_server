/** \file ec_ctrl_channel.h
 *
 * $id$
 *
 */

#ifndef EC_CTRL_CHANNEL_H
#define EC_CTRL_CHANNEL_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "ec_channel.h"


//-----------------------------------------------------------------------------
// EC namespace
//-----------------------------------------------------------------------------

namespace EC
{
	//-----------------------------------------------------------------------------
	// class CCtrlChannel
	//-----------------------------------------------------------------------------

	class CCtrlChannel: public IChannel
	{
	public:
		//-----------------------------------------------------------------------------
		// IChannel Specialisation

		virtual void cbAddUser(TChannelRank rank,const TCharacterId& id,GUS::TClientId clientId);
		virtual void cbRemoveUser(TChannelRank rank,const TCharacterId& id,GUS::TClientId clientId);
		virtual void cbChatText(TChannelRank rank,const TCharacterId& id,GUS::TClientId clientId,const NLMISC::CSString& txt);


	public:
		//-----------------------------------------------------------------------------
		// public interface

		CCtrlChannel(CEventChatModule* theModule);


	private:
		//-----------------------------------------------------------------------------
		// private data

		CEventChatModule*	_TheModule;
		TChannelRank		_MinChatRank;
	};
}


//-----------------------------------------------------------------------------
#endif
