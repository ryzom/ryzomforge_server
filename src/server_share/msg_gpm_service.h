/** \file msg_gpm_service.h
 * Definition of all messages for back-end and client
 *
 * $Id: msg_gpm_service.h,v 1.5 2007/05/25 09:47:42 verquerre Exp $
 */




#ifndef RY_MSG_GPM_SERVICE_H
#define RY_MSG_GPM_SERVICE_H

#include "nel/misc/types_nl.h"
#include "nel/misc/time_nl.h"
#include "nel/misc/stream.h"
#include "nel/misc/sheet_id.h"
#include "nel/misc/entity_id.h"
#include "nel/net/unified_network.h"
#include "nel/net/transport_class.h"

#include "game_share/ryzom_entity_id.h"
#include "game_share/base_types.h"
#include "game_share/synchronised_message.h"


/****************************************************************\
 ****************************************************************
	  Messages definitions for GPM Service
 ****************************************************************
\****************************************************************/

class CEntitySheetId
{
public:
	NLMISC::CEntityId	EntityId;
	NLMISC::CSheetId	SheetId;
	CEntitySheetId() {}
	CEntitySheetId(NLMISC::CEntityId &eid, NLMISC::CSheetId &sheet) : EntityId(eid), SheetId(sheet) {}

	void	serial(NLMISC::IStream &f) { f.serial(EntityId, SheetId); }
};


class CGPMPlayerPrivilege : public CMirrorTransportClass
{
public:

	enum TType
	{
		Player = 0,	// basic player, no particular rights
		GM = 1,
		CS = 2
	};


	TDataSetRow			PlayerIndex;
	uint32				Type;

	virtual void description ()
	{
		className("CGPMPlayerPrivilege");
		property("PlayerIndex", PropDataSetRow, TDataSetRow(), PlayerIndex);
		property("Type", PropUInt32, (uint32)Player, Type);
	}

	virtual void callback (const std::string &name, NLNET::TServiceId id) {};
};


#endif // RY_MSG_GPM_SERVICE_H

/* End of msg_gpm_service.h */
