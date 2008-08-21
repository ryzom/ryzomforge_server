/** \file guild_invitation_module.cpp
 * <File description>
 *
 * $Id: guild_invitation_module.cpp,v 1.11 2006/09/14 17:04:21 cado Exp $
 */

#include "stdpch.h"

#include "player_manager/character.h"
#include "player_manager/player_manager.h"

#include "guild_invitation_module.h"
#include "guild_manager.h"
#include "guild_member_module.h"
#include "guild_member.h"
#include "guild.h"
#include "egs_utils.h"

NL_INSTANCE_COUNTER_IMPL(CGuildInvitation);
NL_INSTANCE_COUNTER_IMPL(CGuildInvitationModule);

//----------------------------------------------------------------------------
void CGuildInvitationModule::refuse()
{
	MODULE_AST(_Invitation);
	nlassert( _Invitation->getGuild() );
	CGuildCharProxy proxy;
	getProxy( proxy );
	proxy.cancelAFK();

	SM_STATIC_PARAMS_1(params,STRING_MANAGER::player);
	params[0].setEIdAIAlias( proxy.getId(), CAIAliasTranslator::getInstance()->getAIAlias( proxy.getId()) );

	CCharacter::sendDynamicSystemMessage( _Invitation->getInvitor(), "GUILD_REFUSE_JOIN", params);
	CGuildManager::getInstance()->removeInvitation(_Invitation);
}

//----------------------------------------------------------------------------
void CGuildInvitationModule::accept()
{
	MODULE_AST(_Invitation);
	nlassert( _Invitation->getGuild() );
	CGuild * guild = EGS_PD_CAST< CGuild* > ( _Invitation->getGuild() );
	EGS_PD_AST(guild);

	CGuildCharProxy proxy;
	getProxy( proxy );
	proxy.cancelAFK();

	CGuildMemberModule * oldModule;
	proxy.getModule( oldModule );
	if ( oldModule )
	{
		nlwarning("<GUILD> user %s is already member of a guild",proxy.getId().toString().c_str() );
		return;
	}

	/// check if there is room in the guild
	if (  guild->getMemberCount() >= GuildMaxMemberCount )
	{
		SM_STATIC_PARAMS_1(params,STRING_MANAGER::integer);
		params[0].Int = GuildMaxMemberCount;
		proxy.sendSystemMessage("GUILD_MAX_MEMBER_COUNT_INVITE",params);
		return;		
	}
	// send message to the guild
	SM_STATIC_PARAMS_1(params2,STRING_MANAGER::player);	
	params2[0].setEIdAIAlias( proxy.getId(), CAIAliasTranslator::getInstance()->getAIAlias( proxy.getId()) );
	_Invitation->getGuild()->sendMessageToGuildMembers("GUILD_JOIN", params2);

	proxy.setGuildId(guild->getId());

	// inform user
	SM_STATIC_PARAMS_1(params1,STRING_MANAGER::string_id);
	params1[0].StringId = _Invitation->getGuild()->getNameId();
	proxy.sendSystemMessage("GUILD_YOU_JOIN",params1);

	// ask the client to open it's guild interface
	PlayerManager.sendImpulseToClient( proxy.getId(),"GUILD:OPEN_GUILD_WINDOW" );

	// create a new member core
	CGuildMember * memberCore = _Invitation->getGuild()->newMember( proxy.getId() );
	nlassert( memberCore );

// All the following already done by newMember()
	// retrieve the member module for the new member
//	CGuildMemberModule *module = NULL;
//	memberCore->getReferencingModule(module);
//	nlassert(memberCore != NULL);
//	memberCore = new CGuildMemberModule( proxy, memberCore );
//	memberCore->setMemberGrade( EGSPD::CGuildGrade::Member );
//	guild->setMemberOnline( memberCore, proxy.getId().getDynamicId() );

	//remove invitation
	CGuildManager::getInstance()->removeInvitation(_Invitation);
}

//----------------------------------------------------------------------------
void CGuildInvitationModule::onParentDestructionHandler()
{
	MODULE_AST(_Invitation);
	CGuildManager::getInstance()->removeInvitation(_Invitation);
}
