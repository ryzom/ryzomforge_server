/** \file history.cpp
 * <File description>
 *
 * $Id: history.cpp,v 1.7 2004/03/01 19:21:52 lecroart Exp $
 */



#include "stdpch.h"

#include "history.h"
#include "game_share/action.h"

using namespace std;
using namespace CLFECOMMON;

/*
 * Constructor
 */
CHistory::CHistory()
{
	_PacketHistory.setPropertyHistory(&_PropertyHistory);
}


void	CHistory::clear()
{
	_PacketHistory.clear();
	_PropertyHistory.clear();
}

void	CHistory::setMaximumClient(uint maxClient)
{
	_MaxClientId = maxClient-1;
	_PacketHistory.setMaximumClient(maxClient);
	_PropertyHistory.setMaximumClient(maxClient);
}

//
void	CHistory::addClient(TClientId clientId)
{
	_PacketHistory.addClient(clientId);
	_PropertyHistory.addClient(clientId);
}

void	CHistory::removeClient(TClientId clientId)
{
	_PacketHistory.removeClient(clientId);
	_PropertyHistory.removeClient(clientId);
}

void	CHistory::resetClient(TClientId clientId)
{
	_PacketHistory.resetClient(clientId);
	_PropertyHistory.resetClient(clientId);
}

//

bool	CHistory::addEntityToClient(TCLEntityId entityId, TClientId clientId)
{
	return _PropertyHistory.addEntityToClient(entityId, clientId);
}

void	CHistory::removeEntityOfClient(TCLEntityId entityId, TClientId clientId)
{
	_PropertyHistory.removeEntityOfClient(entityId, clientId);
}

//
/*
bool	CHistory::packDelta(TClientId clientId, CAction *action)
{
	return _ContinuousHistory.packDelta(clientId, *action, true);
}
*/
/*
void	CHistory::store(TClientId clientId, uint32 packetNumber, CAction *action)
{
	_PacketHistory.store(clientId, packetNumber, action);
	_ContinuousHistory.updateProperty(clientId, packetNumber, *action);
}
*/

void	CHistory::ack(TClientId clientId, uint32 packet, uint32 bits, uint ackBitWidth)
{
	_PacketHistory.ack(clientId, packet, bits, ackBitWidth);
}

void	CHistory::ack(TClientId clientId, uint32 packet, bool ackvalue)
{
	_PacketHistory.ack(clientId, packet, ackvalue);
}

//

/*
void	CHistory::setPropertyConversion(uint32 property, sint8 conversion) { _ContinuousHistory.setPropertyConversion(property, conversion); }
void	CHistory::setPropertyConversion(CPropertyTranslation *properties, sint numProperties) { _ContinuousHistory.setPropertyConversion(properties, numProperties); }
void	CHistory::setPositionPropertyId(uint32 id) { _ContinuousHistory.setPositionPropertyId(id); }
*/
//bool	CHistory::isContinuousProperty(uint32 property) { return _ContinuousHistory.isContinuousProperty(property); }
