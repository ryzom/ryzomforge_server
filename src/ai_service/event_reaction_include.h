/** \file event_reaction.h
 *
 * $Id: event_reaction_include.h,v 1.1 2005/06/28 17:16:27 cado Exp $
 */




#ifndef RYAI_EVENT_REACTION_INCLUDE_H
#define RYAI_EVENT_REACTION_INCLUDE_H

/*#include "ai_mgr.h"
#include "ai.h"
#include "event_reaction.h"
#include "ai_grp.h"
#include "ais_actions.h"	//	for CWorkPtr::instance()
#include "continent.h"*/

template <class TState>
bool	CAIEventReaction::testCompatibility(CStateInstance	*const	stateInstance, const	TState	*const	state) const
{
	if	(!stateInstance)
		return false;

	const	uint32	grpAlias=stateInstance->aliasTreeOwner()->getAlias();
	const	uint32	stateAlias=state->getAlias();

	// if group list is empty and filters are clear then accept all groups
	bool grpOK=(_groups.empty() && _groupFilter.isEmpty());
	
	// as long as group not flagged OK - test the list of named groups to see if we match
	for (uint i=0;!grpOK && i<_groups.size();++i)
		grpOK=(grpAlias==_groups[i]);

	// if all else fails try the keyword test 
	if (!grpOK && !(!_groupFilter.isEmpty() && _groupFilter.test(stateInstance->getPersistentStateInstance()->getKeywords())))
		return false;

	// if state list is empty and filters are clear then accept all states
	bool stateOK=(_states.empty() && _stateFilter.isEmpty());
	
	// as long as state not flagged OK - test the list of named states to see if we match
	for (uint j=0;!stateOK && j<_states.size();++j)
		stateOK=(stateAlias==_states[j]);
	
	// if all else fails try the keyword test 
	return (stateOK || (!_stateFilter.isEmpty() && _stateFilter.test(state->getKeywords())));

}

#endif
