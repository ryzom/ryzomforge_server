/** \file guild_member.h
 * <File description>
 *
 * $Id: guild_member.h,v 1.10 2006/07/12 14:37:34 boucher Exp $
 */

#ifndef RY_GUILD_MEMBER_H
#define RY_GUILD_MEMBER_H

#include "egs_pd.h"
#include "../../gameplay_module_lib/gameplay_module_lib.h"

/**
 * A guild member core class. This is persistant data (except InfoVersion related data)
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CGuildMember : public IModuleCore, public EGSPD::CGuildMemberPD
{
	NL_INSTANCE_COUNTER_DECL(CGuildMember);
public:

	/// set the index of the member in the guild
	inline void setMemberIndex(uint16 idx );
	/// get the index of the member in the guild 
	inline uint16 getMemberIndex()const;
	/// set the grade of the member
	inline void setMemberGrade( EGSPD::CGuildGrade::TGuildGrade grade );
	/// return the dynamic (ingame id of the member )
	NLMISC::CEntityId getIngameEId() const
	{
		if ( _IngameEId == NLMISC::CEntityId::Unknown )
			return getId();
		return _IngameEId;
	}
	/// set the dynamic (ingame id of the member )
	void setDynamicId(uint8 id) 
	{
		_IngameEId = getId();
		_IngameEId.setDynamicId( id );
	}

private:
	/// index of the player in the guild ( in fact, it is its database entry )
	uint16				_MemberIndex;
	/// dynamic (ingame) id of the member ( frontend id is setup )
	NLMISC::CEntityId	_IngameEId;
};


#include "guild_manager/guild.h"
#include "egs_utils.h"

//----------------------------------------------------------------------------
inline void CGuildMember::setMemberIndex(uint16 idx )
{
	_MemberIndex = idx;
}

//----------------------------------------------------------------------------
inline uint16 CGuildMember::getMemberIndex()const
{
	return _MemberIndex;
}

//----------------------------------------------------------------------------
inline void CGuildMember::setMemberGrade( EGSPD::CGuildGrade::TGuildGrade grade )
{
	setGrade( grade );
	CGuild * guild = EGS_PD_CAST<CGuild*> ( _Guild );
	EGS_PD_AST(guild);
	guild->setMemberClientDB( this );
}

#endif // RY_GUILD_MEMBER_H

/* End of guild_member.h */
