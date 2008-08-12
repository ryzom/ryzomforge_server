/** \file state_chat.h
 *
 * $Id: state_chat.cpp,v 1.9 2005/02/25 18:39:11 vuarand Exp $
 */



#include "stdpch.h"
#include "state_profil.h"
#include "ai_bot_npc.h"
#include "ai_grp_npc.h"

std::string	CAIStateChat::getIndexString	()	const
{
	return	getOwner()->getIndexString()+NLMISC::toString(":%u", getChildIndex());
}


void CAIStateChat::botKeywordFilterAdd(const std::string &keyword)
{ 
	CKeywordFilter filter;
	if (!CAIKeywords::botFilter(keyword, filter))
	{
		nlwarning("There are some keyword error in '%s'", getAliasNode()->fullName().c_str());
	}
	_botKeywordFilter+=filter;
} 


bool CAIStateChat::testCompatibility(const CBotNpc &bot) const
{
	const std::string &botName		=	bot.getName();

	uint i;
	bool botOK = _namedBots.empty() && _botKeywordFilter.isEmpty();
	// as long as bot not flagged OK - test the list of named bots to see if we match
//	std::vector<std::string>::iterator	it=find_if(_namedBots.begin(), _namedBots.end(), bind2nd(equal_to,botName));
//	botOK=it!=_namedBots.end();

	for (i=0;!botOK && i<_namedBots.size();++i)
		botOK = (botName==_namedBots[i]);

	// if all else fails try the keyword test 
	return (	botOK
			||	(	!_botKeywordFilter.isEmpty()
				&&	_botKeywordFilter.test(bot.getKeywords())
				)
			);
}
