/** \file far_position_stack.h
 * <File description>
 *
 * $Id: far_position_stack.h,v 1.3 2006/05/31 12:13:20 boucher Exp $
 */

/* Copyright, 2000-2006 Nevrax Ltd.
 *
 * This file is part of NEVRAX RYZOM.
 * NEVRAX RYZOM is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX RYZOM is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX RYZOM; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#ifndef NL_FAR_POSITION_STACK_H
#define NL_FAR_POSITION_STACK_H

#include "nel/misc/types_nl.h"
#include "game_share/far_position.h"
#include "game_share/persistent_data.h"
#include <vector>


/**
 * Stack of far positions
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2006
 */
class CFarPositionStack
{
public:

	DECLARE_PERSISTENCE_METHODS

	typedef CFarPosition T;

	/// Constructor
	CFarPositionStack() {}

	/// Return true if the stack is empty
	bool			empty() const { return _Vec.empty(); }

	/// Return the number of elements in the stack
	uint			size() const { return _Vec.size(); }

	/// Return the latest pushed position (no bound check)
	const T&		top() const { return _Vec.back(); }
	
	/// Push a position on top of the stack
	void			push( const T& pos ) { _Vec.push_back( pos ); }

	/// Pop (remove the top position) off the stack
	void			pop() { _Vec.pop_back(); }

	/// Return the latest push position (non const) (no bound check)
	T&				topToModify() { return _Vec.back(); }

	/// Return the specified position in the stack (no bound check)
	const T&		operator[](uint i) const { return _Vec[i]; }

	/// Replace a position in the stack (no bound check) (debug only)
	void			substFarPosition( uint index, const CFarPosition& newFarPos );

private:

	// Not a real stack because of the persistence methods
	std::vector<T>	_Vec;
};


#endif // NL_FAR_POSITION_STACK_H

/* End of far_position_stack.h */
