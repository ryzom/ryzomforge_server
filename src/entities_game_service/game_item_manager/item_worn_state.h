/** \file item_worn_state.h
 * definition of item worn state
 *
 * $Id: item_worn_state.h,v 1.3 2004/12/08 13:26:48 besson Exp $
 */


#ifndef RYZOM_ITEM_WORN_STATE_H
#define RYZOM_ITEM_WORN_STATE_H

namespace ITEM_WORN_STATE
{
	enum TItemWornState
	{
		Unspoiled = 0,
		WornState1,
		WornState2,
		WornState3,
		WornState4,
		Worned,		
	};


	/**
	 * get item worn state corresponding to input string
	 * \param str the input string
	 * \return the TItemWornState associated to this string (nothing if the string cannot be interpreted)
	 */
	TItemWornState fromString(const std::string &str);

	/**
	 * get the protection type string corresponding to enum
	 * \param type the TProtectionType value
	 * \return type as a string (or nothing)
	 */
	const std::string& toString(TItemWornState state);

	/**
	 * get the chat message to send when an item changes it's state
	 * \param state the worn state of the item
	 */
	const std::string& getMessageForState(TItemWornState state);

}; // ITEM_WORN_STATE

#endif // RYZOM_ITEM_WORN_STATE_H
/* End of item_worn_state.h */
