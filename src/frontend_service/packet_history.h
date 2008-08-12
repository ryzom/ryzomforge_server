/** \file packet_history.h
 * <File description>
 *
 * $Id: packet_history.h,v 1.9 2004/10/11 12:24:23 legros Exp $
 */



#ifndef NL_PACKET_HISTORY_H
#define NL_PACKET_HISTORY_H

#include <vector>
#include <deque>

#include "nel/misc/types_nl.h"
#include "fe_types.h"

class CPropertyHistory;

namespace CLFECOMMON
{
	class CAction;
}

// Make sure this is not define in final version
#undef TEST_LOST_PACKET


/**
 * <Class description>
 * \author Benjamin Legros
 * \author Nevrax France
 * \date 2001
 */
class CPacketHistory
{
private:
	class CMessageEntry
	{
	public:
		CLFECOMMON::TCLEntityId	EntityId;
		CLFECOMMON::TPropIndex	PropIndex;

		CMessageEntry() {}
		CMessageEntry(CLFECOMMON::TCLEntityId eid, CLFECOMMON::TPropIndex pi) : EntityId(eid), PropIndex(pi) {}
	};

	typedef std::vector<CMessageEntry> CPacket;

	class CPacketEntry
	{
	public:
		uint32					Number;
		CPacket					Packet;
	};

	typedef std::deque<CPacketEntry>	TPacketQueue;

	class CClientEntry
	{
	public:
		bool					EntryUsed;
		TPacketQueue			Queue;

		CClientEntry() : EntryUsed(false) {}
	};

	std::vector<CClientEntry>	_ClientsHistories;
	CPropertyHistory			*_PropertyHistory;

public:

	/// Constructor
	CPacketHistory();

	//
	void	clear();
	void	init(uint maxClient) { setMaximumClient(maxClient); clear(); }
	void	setMaximumClient(uint maxClient);

	//
	void	setPropertyHistory(CPropertyHistory *history) { _PropertyHistory = history; }

	//
	void	addClient(TClientId clientId);
	void	removeClient(TClientId clientId);
	void	resetClient(TClientId clientId);
	bool	isValidClient(TClientId clientId);

	//
	void	store(TClientId clientId, uint packetNumber, CLFECOMMON::CAction *action);
	void	storeDisassociation(TClientId clientId, CLFECOMMON::TCLEntityId slot, uint packetNumber );
		
	/// Ack a received packet (with full ack bit field
	void	ack(TClientId clientId, uint32 packet, uint32 bits, uint ackBitWidth = 8);

	/// Ack a single packet
	void	ack(TClientId clientId, uint32 packet, bool ackvalue);

#ifdef TEST_LOST_PACKET
public:
#else
private:
#endif
	//
	void	positiveAck(TClientId clientId, CLFECOMMON::TCLEntityId entityId, CLFECOMMON::TPropIndex propindex, uint32 packet);

	//
	void	negativeAck(TClientId clientId, CLFECOMMON::TCLEntityId entityId, CLFECOMMON::TPropIndex propindex, uint32 packet);
};




inline void	CPacketHistory::store(TClientId clientId, uint packetNumber, CLFECOMMON::CAction *action)
{
	// get the packet queue of the client
	TPacketQueue	&queue = _ClientsHistories[clientId].Queue;

	nlassert(queue.empty() || packetNumber >= queue.back().Number);

	if (queue.empty() || packetNumber>queue.back().Number)
	{
		queue.push_back(CPacketEntry());
		queue.back().Number = packetNumber;
	}

	queue.back().Packet.push_back(CMessageEntry(action->Slot, action->PropertyCode));
}


#endif // NL_PACKET_HISTORY_H

/* End of packet_history.h */
