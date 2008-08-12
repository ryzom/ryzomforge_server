/** \file state_profil.h
 *
 * $Id: state_profil.cpp,v 1.9 2005/07/26 14:37:53 vuarand Exp $
 */



#include "stdpch.h"
#include "state_profil.h"
#include "ai_bot_npc.h"
#include "ai_grp_npc.h"


std::string	CAIStateProfile::getIndexString	()	const
{
	return	getOwner()->getIndexString()+NLMISC::toString(":%u", getChildIndex());
}


void CAIStateProfile::grpKeywordFilterAdd(const std::string &keyword)
{
	CKeywordFilter filter;

	if (!CAIKeywords::groupFilter(keyword, filter))
	{
		nlwarning("There are some keyword error in '%s'", getAliasNode()->fullName().c_str());
	}

	_grpKeywordFilter+=filter;
}


bool CAIStateProfile::testCompatibility(const CGroupNpc &grp) const
{
	const std::string &groupName	=	grp.getName();	
	bool grpOK = _namedGrps.empty() && _grpKeywordFilter.isEmpty();

	// as long as group not flagged OK - test the list of named groups to see if we match
	for (uint i=0;!grpOK && i<_namedGrps.size();++i)
		grpOK = (groupName==_namedGrps[i]);

	// if all else fails try the keyword test 
	return	(	grpOK
			||	(	!_grpKeywordFilter.isEmpty()
				&& _grpKeywordFilter.test(grp.getKeywords())
				)
			);
}
