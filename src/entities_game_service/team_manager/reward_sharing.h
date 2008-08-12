/** \file reward_sharing.h
 * <File description>
 *
 * $Id: reward_sharing.h,v 1.7 2005/06/23 18:14:21 boucher Exp $
 */



#ifndef RY_REWARD_SHARING_H
#define RY_REWARD_SHARING_H


#include "game_item_manager/game_item.h"
#include "game_item_manager/game_item_manager.h"

#include "nel/misc/bit_set.h"


class CTeam;

/**
 * class used to represent a reward sharing session among players
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CRewardSharing
{
	NL_INSTANCE_COUNTER_DECL(CRewardSharing);
public:
	/// ctor
	CRewardSharing()
		:_Session(0){}
	
	/// dtor : destroy all remaining items
	~CRewardSharing()
	{
		for ( uint i = 0; i < _Rewards.size(); i++ )
		{
			if ( _Rewards[i].Item != NULL )
			{
				GameItemManager.destroyItem(_Rewards[i].Item);
			}
		}
	}

	/// add a new reward to this one
	void addReward( CRewardSharing * reward, CTeam * team );

	/// add an item to the reward share. Used to init the share only
	void addItem(CGameItemPtr item)
	{
		CReward reward;
		reward.Item = item;
		_Rewards.push_back(reward);
	}

	/// add a phrase to the share. Used to init the share only
	void addPhrase(const NLMISC::CSheetId & sheet)
	{
		CReward reward;
		reward.SheetId = sheet;
		_Rewards.push_back(reward);
	}

	/// reset candidates information
	void resetCandidates(CTeam * team);

	/// user select/unselect an item
	void userItemSelect(const TDataSetRow & userRow,uint32 itemPos, uint8 state);
	
	/// user validate / invalidate. return true if the reward was given
	bool userValidSelect(const TDataSetRow & userRow, uint8 state);

	/// set the user database with the share content
	void setUsersDb();

	/// give all items to the specified player
	void giveAllItems( const TDataSetRow & row);

	///\return the item in the specified slot, NULL if no item
	CGameItemPtr getItem(uint32 slot)
	{
		if ( slot >= _Rewards.size() )
		{
			nlwarning("<CRewardSharing getItem>Invalid slot %u : max = %u",slot,_Rewards.size());
			return NULL;
		}
		return _Rewards[slot].Item;
	}

private:
	/// a reward in the share (item/phrase)
	struct CReward
	{
		CGameItemPtr							Item;
		NLMISC::CSheetId						SheetId;
		std::vector< std::pair<uint8,float> >	Candidates;
	};

	struct CCandidate
	{
		CCandidate()
			:Validated(false),NbSelected(0){}
		bool		Validated;
		uint8		NbSelected;
		TDataSetRow	UserRow;
	};

	/// state counter : all request from a player must send the same value as this one, so we avoid desync between client and server state
	uint8							_Session;
	/// the rewards in the share
	std::vector<CReward>			_Rewards;
	/// states of the members ( number of item for which they applied and bool telling if the have validated
	std::vector< CCandidate >		_Candidates;
};


#endif // RY_REWARD_SHARING_H

/* End of reward_sharing.h */
