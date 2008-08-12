/** \file guild_invitation_module.h
 * <File description>
 *
 * $Id: guild_invitation_module.h,v 1.5 2005/06/23 18:10:49 boucher Exp $
 */

#ifndef RY_GUILD_INVITATION_MODULE_H
#define RY_GUILD_INVITATION_MODULE_H

#include "../../gameplay_module_lib/gameplay_module_lib.h"
#include "guild_invitation.h"
#include "guild_manager/guild_char_proxy.h"

/**
 * module implementing guild invitation
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CGuildInvitationModule : public IModule
{
	NL_INSTANCE_COUNTER_DECL(CGuildInvitationModule);
public:

	/// ctor
	CGuildInvitationModule( CGuildCharProxy& proxy, CGuildInvitation* invitation )
		:IModule(&(proxy.getModuleParent()),invitation),_Invitation(invitation)
	{
		nlassert( invitation );
	}
	/// user refuses an invitation
	void refuse();
	/// user accepts an invitation
	void accept();
private:
	/// handler called on parent ( player destruction )
	virtual void onParentDestructionHandler();
	/// "real" invitation object
	CGuildInvitation * _Invitation;
};


#endif // RY_GUILD_INVITATION_MODULE_H

/* End of guild_invitation_module.h */
