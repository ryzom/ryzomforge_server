/** \file id_impulsions.h
 * 
 *
 * $Id: id_impulsions.h,v 1.3 2007/03/09 09:56:52 boucher Exp $
 */



#ifndef ID_IMPULSIONS_H
#define ID_IMPULSIONS_H


// misc
#include "nel/misc/types_nl.h"
#include "nel/net/unified_network.h"

/*
 * Message received from identified clients, using CEntityId sender
 */
typedef void	(*TImpulsionIdCb)( const NLMISC::CEntityId& sender, NLMISC::CBitMemStream &bms, NLMISC::TGameCycle gamecycle, NLNET::TServiceId serviceId );

void	initImpulsionId();
void	routeImpulsionIdFromClient( NLMISC::CBitMemStream& bms, const NLMISC::CEntityId& sender, const NLMISC::TGameCycle& gamecycle );
void	routeImpulsionIdSlotFromClient( const uint32& targetLootHarvest, const TDataSetRow& targetIndex, const TDataSetRow& senderIndex, const NLMISC::TGameCycle& gamecycle );

#endif // ID_IMPULSIONS_H

/* End of id_impulsions.h */
