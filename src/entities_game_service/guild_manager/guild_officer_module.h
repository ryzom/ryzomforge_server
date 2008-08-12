/** \file guild_officer_module.h
 * <File description>
 *
 * $Id: guild_officer_module.h,v 1.5 2005/06/23 18:10:49 boucher Exp $
 */

#ifndef RY_GUILD_OFFICER_MODULE_H
#define RY_GUILD_OFFICER_MODULE_H

#include "guild_manager/guild_member_module.h"

/**
 * Guild officer gameplay module.  See CGuildMemberModule for cmethod comments
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CGuildOfficerModule: public  CGuildMemberModule
{
	NL_INSTANCE_COUNTER_DECL(CGuildOfficerModule);
public:

	CGuildOfficerModule( CGuildCharProxy & proxy, CGuildMember* guildMember)
		:CGuildMemberModule(proxy,guildMember){}	
	virtual bool canAffectGrade(EGSPD::CGuildGrade::TGuildGrade grade)const;
	virtual bool canInvite()const;
};
;


#endif // RY_GUILD_OFFICER_MODULE_H

/* End of guild_officer_module.h */
