/** \file mission_guild.h
 * <File description>
 *
 * $Id: mission_guild.h,v 1.5 2005/08/31 12:56:25 besson Exp $
 */

#ifndef RY_MISSION_GUILD_H
#define RY_MISSION_GUILD_H

#include "egs_pd.h"

/**
 * <Class description>
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CMissionGuild : public EGSPD::CMissionGuildPD
{
	NL_INSTANCE_COUNTER_DECL(CMissionGuild);
public:

	CMissionGuild() : _Chained(false) { }

	/// override
	void updateUsersJournalEntry();
	/// override
	void clearUsersJournalEntry();
	/// override
	void setupEscort(const std::vector<TAIAlias> & aliases);
	/// override
	void getEntities(std::vector<TDataSetRow>& entities);
	/// override
	void stopChildren();
	/// override
	void onFailure(bool ignoreJumps,bool sendMessage = true);
	/// force mission success
	void forceSuccess();
	/// return the mission main character ( user, group leader,...)
	CCharacter* getMainEntity();
	/// during the execution of the mission does the compiler encounter a 'chain_mission' ?
	bool isChained() { return _Chained; }
	/// when executing a 'chain_mission' set this flag to let know that we have chained
	void setChained(bool b=true) { _Chained = b; }

private:
	uint32 _GuildId;
	bool _Chained;
};


#endif // RY_MISSION_GUILD_H

/* End of mission_guild.h */
