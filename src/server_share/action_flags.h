/** \file action_flags.h
 *
 * $Id: action_flags.h,v 1.5 2004/08/11 09:10:14 ledorze Exp $
 */



#ifndef RY_ACTION_FLAGS_H
#define RY_ACTION_FLAGS_H

#include "nel/misc/types_nl.h"

namespace RYZOMACTIONFLAGS
{
	enum TActionFlag
	{
		InWater = 1<<1,
		Attacks = 1<<0,
		Undefined = 1<<16,
	};

	/**
	 * get the action flag size as a string
	 * \param size the TActionFlag size
	 * \return the string associated to this TActionFlag
	 */
	const std::string &toString(TActionFlag flag);

	/**
	 * convert a string to an action flag
	 * \param str the string to convert
	 * \return the action flag associated to the string, Undefined if unknown
	 */
	TActionFlag toActionFlag(const std::string str);

};	// RYZOMACTIONFLAGS

#endif //RY_ACTION_FLAGS_H

/* End of action_flags.h */
