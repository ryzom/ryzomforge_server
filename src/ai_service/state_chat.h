/** \file state_profil.h
 *
 * $Id: state_chat.h,v 1.11 2005/02/25 18:39:11 vuarand Exp $
 */




#ifndef RYAI_STATE_CHAT_H
#define RYAI_STATE_CHAT_H

#include "child_container.h"
#include "ai_keywords.h"
#include "npc_description_msg.h"

class CAIState;
class CBotNpc;

class CAIStateChat
	:public	CAliasChild<CAIState>
	,public	NLMISC::CRefCount
{
public:
	// ctor & dtor ------------------------------------------------------
	CAIStateChat(CAIState*	state,	CAIAliasDescriptionNode *aliasDescription): CAliasChild<CAIState>(state,aliasDescription)
	{}
	virtual ~CAIStateChat()
	{}

	virtual	std::string	getIndexString	()	const;

	// Keyword management ----------------------------------------------
	void	botKeywordFilterClear()							{ _botKeywordFilter.clear(); }
	void	botKeywordFilterAdd(const std::string &keyword);

	bool	botKeywordTest(CKeywordMask mask)			{ return _botKeywordFilter.test(mask); }

	// name management -------------------------------------------------
	void	botNameFilterClear()						{ _namedBots.clear(); }
	void	botNameFilterAdd(const std::string &name)	{ _namedBots.push_back(name); }						

	bool	botNameTest(const std::string &name) const
	{
		std::vector<std::string>::const_iterator it(std::find(_namedBots.begin(), _namedBots.end(), name));
		return it != _namedBots.end();
	}

	// compatibility test ----------------------------------------------
	bool	testCompatibility(const CBotNpc &bot) const;
	
	//	Chat management
	const	CNpcChatProfileImp	&getChat()	const
	{
		return	_chatProfile;
	}
	CNpcChatProfileImp	&chatProfile	()
	{
		return	_chatProfile;
	}
	
private:
	// protected data ---------------------------------------------------
	CKeywordFilter				_botKeywordFilter;		// keyword filter for identifying bot types to whom to apply profile
	std::vector<std::string>	_namedBots;	// list of named bots to whom this profile applies

	CNpcChatProfileImp			_chatProfile;			// the chat profile buffer
};

#endif
