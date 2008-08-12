/** \file mission_solo.h
 * <File description>
 *
 * $Id: mission_solo.h,v 1.7 2005/08/31 12:56:25 besson Exp $
 */

#ifndef RY_MISSION_SOLO_H
#define RY_MISSION_SOLO_H

#include "egs_pd.h"

/**
 * <Class description>
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CMissionSolo : public EGSPD::CMissionSoloPD
{
	NL_INSTANCE_COUNTER_DECL(CMissionSolo);
public:

	CMissionSolo() : _Chained(false) { }

	/// set the mission taker
	inline void setTaker( const TDataSetRow & userRow );
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
	TDataSetRow _Taker;

	bool _Chained;

};

//----------------------------------------------------------------------------
inline void CMissionSolo::setTaker( const TDataSetRow & userRow )
{
	_Taker = userRow;
}

#endif // RY_MISSION_SOLO_H

/* End of mission_solo.h */
