/** \file target.h
 *
 * $Id: target.h,v 1.3 2004/03/01 19:21:54 lecroart Exp $
 */




#ifndef RY_TARGET_H
#define RY_TARGET_H

#include <string>

namespace TARGET
{

enum EAggro
{
	Friendly = 0,
	AlmostFriendly,
	Neutral,
	AlmostAggressive,
	Agressive,
	NUM_ENUM_AGGRO
};

enum EForceRatio
{
	ThreeLevelBelowOrLess = 0,
	TwoLevelBelow,
	OneLevelBelow,
	SameLevel,
	OneLevelAbove,
	TwoLevelAbove,
	ThreeLevelAboveOrMore,
	NUM_ENUM_FORCE_RATIO
};

	// Enum for the target's restrictions.
	enum TTargetRestriction
	{
		EveryBody = 0,
		SelfOnly,
		TargetRestrictionCount	
	};
	/**
	 * Get the Enum Value for a given target's restriction in string.
	 * \param str : the input string
	 * \return TTargetRestriction : the target's restriction value (for the enum).
	 */
	TTargetRestriction stringToTargetRestriction(const std::string &str);
	/**
	 * Get the string for a given target's restriction.
	 * \param targetRestriction : target's restriction
	 * \return string : the target's restriction as a string.
	 */
	const std::string & targetRestrictionToString(TTargetRestriction targetRestriction);


} // TARGET

#endif

