/** \file keyword_owner.h
 *
 * $Id: keyword_owner.h,v 1.6 2004/03/01 19:19:20 lecroart Exp $
 */



#ifndef RYAI_KEYWORD_OWNER_H
#define RYAI_KEYWORD_OWNER_H

#include "ai_keywords.h"

class	CKeyWordOwner
{
public:
	CKeyWordOwner()
	{
	}
	
	virtual ~CKeyWordOwner()
	{
	}
	// Keyword management ----------------------------------------------
	inline	void keywordsClear()
	{
		_keywords.clear();
	}

	inline	void keywordsAdd(CKeywordMask	mask)	//const std::string &keyword)
	{
		_keywords|=mask;
	}

	inline	const CKeywordMask &getKeywords() const
	{
		return _keywords;
	}
	
protected:
	CKeywordMask	_keywords;	// set of keywords that characterise the owner.
};


#endif
