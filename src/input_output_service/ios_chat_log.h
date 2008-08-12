/** \file ios_chat_log.h
 * 
 * $Id: ios_chat_log.h,v 1.4 2007/05/22 13:42:54 boucher Exp $
 */

#error
#ifndef IOS_CHAT_LOG_H
#define IOS_CHAT_LOG_H

#include <nel/misc/types_nl.h>
#include <nel/misc/debug.h>
#include <nel/misc/common.h>
#include <nel/misc/entity_id.h>
#include <nel/misc/sheet_id.h>
#include <vector>
#include <map>
#include <pd_lib/pd_lib.h>
#include <game_share/persistent_data.h>

// User #includes

namespace IOSPD
{
	
//
// Forward declarations
//



//
// Typedefs & Enums
//

void							createTeam(NLMISC::CEntityId team);

void							deleteTeam(NLMISC::CEntityId team);

void							playerJoinsTeam(NLMISC::CEntityId player, NLMISC::CEntityId team);

void							playerLeavesTeam(NLMISC::CEntityId player, NLMISC::CEntityId team);

	
} // End of IOSPD

#endif
