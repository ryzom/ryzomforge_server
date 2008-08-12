/** \file ec_faction_channel.h
 *
 * $id$
 *
 */

#ifndef EC_FACTION_CHANNEL_H
#define EC_FACTION_CHANNEL_H

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
	// class CFactionChannel
	//-----------------------------------------------------------------------------

	class CFactionChannel: public IChannel
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

		CFactionChannel(CEventChatModule* theModule,const NLMISC::CSString& name);


		//-----------------------------------------------------------------------------
		// interface for CFactionChannelContext to use

		bool setupParty(const NLMISC::CSString& ownerCharacterName,const NLMISC::CSString& title);
		void removeParty(const NLMISC::CSString& ownerCharacterName);

		uint32 getPartyCount() const;
		CPartyChannel* getParty(uint32 idx);


	private:
		//-----------------------------------------------------------------------------
		// private data

		CEventChatModule*	_TheModule;
		TChannelRank		_MinChatRank;
		typedef std::map<TCharacterId,TPartyChannelPtr>	TParties;
		TParties			_Parties;
		typedef std::vector<TCharacterId> TPartyIdx;
		TPartyIdx			_PartyIdx;
	};
}


//-----------------------------------------------------------------------------
#endif
