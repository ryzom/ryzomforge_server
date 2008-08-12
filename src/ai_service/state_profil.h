/** \file state_profil.h
 *
 * $Id: state_profil.h,v 1.17 2005/07/26 14:37:53 vuarand Exp $
 */




#ifndef RYAI_STATE_PROFILE_H
#define RYAI_STATE_PROFILE_H

#include "child_container.h"
#include "ai_keywords.h"
#include "npc_description_msg.h"
#include "profile_in_state.h"

class CAIState;
class CGroupNpc;

class CAIStateProfile : 
	public CAliasChild<CAIState>, 
	public NLMISC::CRefCount,
	public CProfileInState
{
public:
	typedef std::pair<std::string, std::string>		TProfileParameter;

	// ctor & dtor ------------------------------------------------------
	CAIStateProfile(CAIState* state, CAIAliasDescriptionNode *aliasDescription): CAliasChild<CAIState>(state,aliasDescription)
	{}
	virtual ~CAIStateProfile()
	{}

	virtual	std::string	getIndexString	()	const;

	// Keyword management ----------------------------------------------
	void	grpKeywordFilterClear()							{ _grpKeywordFilter.clear(); }
	void	grpKeywordFilterAdd(const std::string &keyword);

	bool	grpKeywordTest(CKeywordMask mask)			{ return _grpKeywordFilter.test(mask); }

	// name management -------------------------------------------------
	void	grpNameFilterClear()						{ _namedGrps.clear(); }
	void	grpNameFilterAdd(const std::string &name)	{ _namedGrps.push_back(name); }

	bool	grpNameTest(const std::string &name) const
	{
		std::vector<std::string>::const_iterator it(std::find(_namedGrps.begin(), _namedGrps.end(), name));
		return it != _namedGrps.end();
	}

	// compatibility test ----------------------------------------------
	bool testCompatibility(const CGroupNpc &bot) const;
	
protected:
	// protected data ---------------------------------------------------
	CKeywordFilter				_grpKeywordFilter;		// keyword filter for identifying grp types for bots to whom to apply profile
	std::vector<std::string>	_namedGrps;	// list of named grps to whom this profile applies
};

#endif
