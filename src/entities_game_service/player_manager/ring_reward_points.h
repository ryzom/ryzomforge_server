/* \file ring_reward_points.h
 *
 * $Id: ring_reward_points.h,v 1.3 2006/10/31 16:09:07 blanchard Exp $
 */


#ifndef RING_REWARD_POINTS_H
#define RING_REWARD_POINTS_H

//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

// NeL Misc
#include "nel/misc/time_nl.h"

#include "game_share/r2_share_itf.h"


//-------------------------------------------------------------------------------------------------
// forward decalarations
//-------------------------------------------------------------------------------------------------

class CRingRewardPointsImpl;
class CCharacter;


//-------------------------------------------------------------------------------------------------
// class CRingRewardPoints
//-------------------------------------------------------------------------------------------------

/**
 *	CRingRewardPoints
 * \author Sadge
 * \author Nevrax France
 * \date 2006
 */

class CRingRewardPoints
{
public:
	// define the level ranges (as used everywhere else in Ryzom)
//	enum TLevel
//	{
//		LEVEL_A,	//   0 -  20
//		LEVEL_B,	//  21 -  50
//		LEVEL_C,	//  51 - 100
//		LEVEL_D,	// 101 - 150
//		LEVEL_E,	// 151 - 200
//		LEVEL_F,	// 201 - 250
//		NUM_LEVELS,
//		INVALID_LEVEL= NUM_LEVELS
//	};

	enum TGenerateRewardResult
	{
		/// ok, reward generated (one or more item gained)
		grr_ok,	
		/// ok, but rare item where generated !
		grr_ok_rare,
		/// not enough place to hold all possible reward (perhaps no item where gained at all)
		grr_no_place,
		/// not enough points to gain one item 
		grr_no_points,
		/// no reward because of invalid context (e.g edit session)
		grr_invalid,
	};

	// default ctor
	CRingRewardPoints(CCharacter* theCharacter);

	// dtor
	~CRingRewardPoints();

	// methods called from CCharacter::store() to save ring reward point data in player save files
	void store(CPersistentDataRecord &pdr) const;

	// methods called from CCharacter::apply() to load ring reward point data from player save files
	void apply(CPersistentDataRecord &pdr);

	// Initialize the client/server database with current rrp
	void initDb();

	// initalise the scenario level (to be called on connection of player to a scenario)
	void setScenarioLevel(R2::TSessionLevel scenarioLevel);

	// method called whenever XP would normally be added to the player (called instead of 
	// standard XP treatment if IsRingShard is true)
	void addXp(R2::TSessionLevel xpLevel, uint32 xpValue);

	// method called when a player clicks on a reward generator - if they have accumulated
	// sufficient reward points of the given level and they have room in their inventory
	// then a reward is generated and given to them and the method returns TRUE.
	// otherwise the method returns FALSE.
	TGenerateRewardResult generateReward(R2::TSessionLevel rewardLevel);


private:
	// a pointer to the object used to implement the ring reward points functionaliity
	CRingRewardPointsImpl* _Implementation;
};


#endif // RING_REWARD_POINTS_H
