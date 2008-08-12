#ifndef GUILD_INTERFACE_H
#define GUILD_INTERFACE_H

#include "nel/misc/entity_id.h"

class CGuild;
namespace EGSPD
{
	class CGuildPD;
}

class IGuild
{
public:

	static IGuild *getGuildInterface(CGuild *guild);
	static IGuild *getGuildInterface(EGSPD::CGuildPD *guildPd);

	uint32			getIdWrap();
	void			setNameWrap(const ucstring &name);
	const ucstring	&getNameWrap();

	bool			isProxyWrap();
	virtual void	removeMember(const NLMISC::CEntityId &id) =0;


	void			updateMembersStringIds();
};

#endif //GUILD_INTERFACE_H

