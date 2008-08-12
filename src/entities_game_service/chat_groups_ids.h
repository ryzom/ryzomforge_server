/** \file chat_groups_ids.h
 * <File description>
 *
 * $Id: chat_groups_ids.h,v 1.6 2004/12/09 14:17:27 besson Exp $
 */



#ifndef RY_EGS_CHAT_GROUP_IDS_H
#define RY_EGS_CHAT_GROUP_IDS_H

#include "nel/misc/progress_callback.h"
#include "game_share/chat_group.h"

namespace CHAT_GROUPS_IDS
{

static const uint32 TeamBase = 0x0000001;
static const uint32 GuildBase = 0x10000000;
static const uint32 RegionBase = 0x20000000;


inline TGroupId getGuildChatGroupId( const EGSPD::TGuildId & guildId )
{
	NLMISC::CEntityId eId;
	eId.setShortId( guildId + GuildBase );
	eId.setType( RYZOMID::chatGroup );
	return eId;
}

inline TGroupId getTeamChatGroupId( uint32 teamId )
{
	return NLMISC::CEntityId( RYZOMID::chatGroup, teamId + TeamBase );
}

inline TGroupId getRegionChatGroupId( uint32 regionId )
{
	return NLMISC::CEntityId( RYZOMID::chatGroup, regionId + RegionBase );
}

}

#endif // RY_EGS_CHAT_GROUP_IDS_H

/* End of chat_groups_ids.h */
