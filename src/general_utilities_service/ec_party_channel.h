/** \file ec_party_channel.h
 *
 * $id$
 *
 */

#ifndef EC_PARTY_CHANNEL_H
#define EC_PARTY_CHANNEL_H

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
	// class CPartyChannel
	//-----------------------------------------------------------------------------

	class CPartyChannel: public IChannel
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

		CPartyChannel(const NLMISC::CSString& chatChannelName,const NLMISC::CSString& title);


		//-----------------------------------------------------------------------------
		// interface for CPartyChannelContext to use

		TChannelRank getMinChatRank() const;
		void setMinChatRank(TChannelRank rank);


	private:
		//-----------------------------------------------------------------------------
		// private data

		TChannelRank		_MinChatRank;
	};
}


//-----------------------------------------------------------------------------
#endif
