/** \file guild_officer_module.cpp
 * <File description>
 *
 * $Id: guild_officer_module.cpp,v 1.7 2006/10/31 16:09:06 blanchard Exp $
 */

#include "stdpch.h"
#include "player_manager/character.h"
#include "guild_officer_module.h"
#include "guild_member.h"

NL_INSTANCE_COUNTER_IMPL(CGuildOfficerModule);

//----------------------------------------------------------------------------
bool CGuildOfficerModule::canAffectGrade(EGSPD::CGuildGrade::TGuildGrade grade)const
{
	return ( grade == EGSPD::CGuildGrade::Member );
}

//----------------------------------------------------------------------------
bool CGuildOfficerModule::canInvite()const
{
	CGuild * guild = MODULE_CAST<CGuild*>( _GuildMemberCore->getGuild() );
	MODULE_AST( guild );
	return !(guild->isProxy());
}
