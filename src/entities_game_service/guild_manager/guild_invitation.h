/** \file guild_invitation.h
 * <File description>
 *
 * $Id: guild_invitation.h,v 1.5 2005/06/23 18:10:49 boucher Exp $
 */

#ifndef RY_GUILD_INVITATION_H
#define RY_GUILD_INVITATION_H

#include "../../gameplay_module_lib/gameplay_module_lib.h"

class CGuild;

/**
 * a player invited another one to join its guild
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CGuildInvitation : public IModuleCore
{
	NL_INSTANCE_COUNTER_DECL(CGuildInvitation);
public:
	/// ctor
	inline CGuildInvitation(CGuild* guild, const TDataSetRow & invitor);
	/// get the guild concerned
	inline CGuild * getGuild()const;
	/// get the invitor
	inline const TDataSetRow & getInvitor()const;
private:
	/// guild concerned
	NLMISC::CRefPtr<CGuild>			_Guild;
	/// row of the player who invited
	TDataSetRow						_Invitor;
	
};

//----------------------------------------------------------------------------
inline CGuildInvitation::CGuildInvitation(CGuild* guild, const TDataSetRow & invitor)
:IModuleCore(),_Guild(guild),_Invitor(invitor)
{
	nlassert(guild);
}

//----------------------------------------------------------------------------
inline CGuild * CGuildInvitation::getGuild()const
{
	return _Guild;
}

//----------------------------------------------------------------------------
inline const TDataSetRow & CGuildInvitation::getInvitor()const
{
	return _Invitor;
}
#endif // RY_GUILD_INVITATION_H

/* End of guild_invitation.h */
