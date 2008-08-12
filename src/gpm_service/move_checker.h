/** \file move_checker.h
 *
 * $Id: move_checker.h,v 1.2 2006/01/10 17:36:24 boucher Exp $
 */

#ifndef MOVE_CHECKER_H
#define MOVE_CHECKER_H

#include "nel/misc/types_nl.h"
#include "nel/misc/smart_ptr.h"

#include "game_share/base_types.h"


class CMoveChecker: public NLMISC::CRefCount
{
public:
	// inform the move checker that a player is being teleported - the move checker performs no test but
	// updates internal info on player position
	void teleport(TDataSetRow entityIndex, sint32 x, sint32 y, uint32 tick);

	// ensure that the move attempted by a player is legal
	// if the move is not valid then x, y and z are changed to make the move valid
	// return true if move is valid otherwise false
	bool checkMove(TDataSetRow entityIndex, sint32& x, sint32& y, uint32 tick);

	// remove a player from the checker (when they have deconnect)
	void remove(TDataSetRow entityIndex);

private:
	// private data

	struct SPosition
	{
		sint32 X, Y;
		uint32 Tick;

		SPosition(): X(0), Y(0), Tick(0)	{}
	};
	typedef std::map<TDataSetRow,SPosition> TPositions;
	TPositions _Positions;
};

#endif
