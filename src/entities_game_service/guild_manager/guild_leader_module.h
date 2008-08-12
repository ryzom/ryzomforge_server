/** \file guild_leader_module.h
 * <File description>
 *
 * $Id: guild_leader_module.h,v 1.17 2005/10/25 16:24:22 guignot Exp $
 */

#ifndef RY_GUILD_LEADER_MODULE_H
#define RY_GUILD_LEADER_MODULE_H

#include "guild_high_officer_module.h"

/**
 * Guild leader gameplay module.  See CGuildMemberModule for cmethod comments
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CGuildLeaderModule : public  CGuildHighOfficerModule
{
	NL_INSTANCE_COUNTER_DECL(CGuildLeaderModule);
public:
	
	CGuildLeaderModule( CGuildCharProxy & proxy, CGuildMember* guildMember)
		:CGuildHighOfficerModule(proxy,guildMember){}	
	
	virtual void setLeader( uint16 index,uint8 session);
	virtual void quitGuild();
	virtual bool canAffectGrade(EGSPD::CGuildGrade::TGuildGrade)const;
	virtual bool canInvite()const;
};


#endif // RY_GUILD_LEADER_MODULE_H

/* End of guild_leader_module.h */
