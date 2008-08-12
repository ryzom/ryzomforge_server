/** \file mission_team.h
 * <File description>
 *
 * $Id: mission_team.h,v 1.5 2005/08/31 12:56:25 besson Exp $
 */

#ifndef RY_MISSION_TEAM_H
#define RY_MISSION_TEAM_H

#include "egs_pd.h"

/**
 * <Class description>
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CMissionTeam : public EGSPD::CMissionTeamPD
{
	NL_INSTANCE_COUNTER_DECL(CMissionTeam);
public:

	CMissionTeam() : _Chained(false) { }

	inline void setTeam( uint16 teamId );
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
	uint16 _TeamId;

	bool _Chained;
};

inline void CMissionTeam::setTeam( uint16 teamId )
{
	_TeamId = teamId;
}

#endif // RY_MISSION_TEAM_H

/* End of mission_team.h */
