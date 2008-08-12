/** \file event_manager.h
 *
 * $Id: event_manager.h,v 1.23 2005/06/28 14:07:37 cado Exp $
 */

#ifndef RYAI_EVENT_MANAGER_H
#define RYAI_EVENT_MANAGER_H

#include "event_reaction.h"
#include "states.h"

//---------------------------------------------------------------------------------
// CAIEvent
//---------------------------------------------------------------------------------

class	CAIEvent : public NLMISC::CDbgRefCount<CAIEvent>
{
public:
	CAIEvent	() : _Name()
	{}

	virtual ~CAIEvent() {}


	// called when an event reaction is added during parse of a .primitive file
	// called by the event reaction object
	inline void addReaction( CAIEventReaction *reaction);

	// called when an event reaction is deleted due to a modification in a .primitive file
	inline	void removeReaction(CAIEventReaction *reaction);

	inline	void removeAllReaction	()
	{
		_Reactions.clear	();
	}
	
	void	setName(const std::string &name)
	{
		_Name=name;
	}

	const	std::string	&getName()	const
	{
		return	_Name;
	}

	typedef		std::vector<NLMISC::CDbgPtr<CAIEventReaction> >	TReactionList;

	const	TReactionList	&reactionList()	const
	{
		return	_Reactions;
	}
	
private:
	std::string		_Name;
	TReactionList	_Reactions;
};


//---------------------------------------------------------------------------------
// CAIEvent
//---------------------------------------------------------------------------------

inline void CAIEvent::addReaction	(CAIEventReaction	*reaction)
{

	if	(std::find_if(_Reactions.begin(), _Reactions.end(), std::bind2nd(std::equal_to<CAIEventReaction*>(),reaction))==_Reactions.end())
	{
		_Reactions.push_back(reaction);
	}
	else
	{
		nlwarning("BUG: Attempt to add the same reaction '%s' to event manager more than once",	reaction->getAliasNode()->fullName().c_str());
	}

}

inline	void CAIEvent::removeReaction(CAIEventReaction *reaction)
{

	TReactionList::iterator	it=std::find_if(_Reactions.begin(), _Reactions.end(), std::bind2nd(std::equal_to<CAIEventReaction*>(),reaction));
	if	(it==_Reactions.end())
	{
		nlwarning("BUG: Failed to remove event reaction from manager as object not found!!!");
	}
	else
	{
		*it=_Reactions.back();
		_Reactions.pop_back();
	}

	
//	for (uint i=0;i<_Reactions.size();++i)
//	{
//		if	(_Reactions[i].ptr()!=reaction)
//			continue;
//
//		_Reactions[i]=_Reactions[_Reactions.size()-1];
//		_Reactions.pop_back();
//		return;
//	}	
//	nlwarning("BUG: Failed to remove event reaction from manager as object not found!!!");
}


//---------------------------------------------------------------------------------
#endif
