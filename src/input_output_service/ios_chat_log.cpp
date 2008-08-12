/** \file ios_chat_log.cpp
 * 
 * $Id: ios_chat_log.cpp,v 1.3 2004/11/22 16:35:33 legros Exp $
 */


#include "stdpch.h"
#include "ios_pd.h"

namespace IOSPD
{
	
void							createTeam(NLMISC::CEntityId team)
{
	PDSLib.log(0);
	PDSLib.logPush(team);
}

void							deleteTeam(NLMISC::CEntityId team)
{
	PDSLib.log(1);
	PDSLib.logPush(team);
}

void							playerJoinsTeam(NLMISC::CEntityId player, NLMISC::CEntityId team)
{
	PDSLib.log(2);
	PDSLib.logPush(player);
	PDSLib.logPush(team);
}

void							playerLeavesTeam(NLMISC::CEntityId player, NLMISC::CEntityId team)
{
	PDSLib.log(3);
	PDSLib.logPush(player);
	PDSLib.logPush(team);
}

	
} // End of IOSPD
