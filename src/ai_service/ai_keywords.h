/** \file ai_keywords.h
 *
 * $Id: ai_keywords.h,v 1.5 2004/05/17 14:32:40 ledorze Exp $
 */




#ifndef RYAI_KEYWORDS_H
#define RYAI_KEYWORDS_H

#include "keyword.h"

class CAIKeywords
{
public:
	static void init();
	static void updateKeywordsFromCfg();
	static void display();

	static bool botMask(const std::string &word, CKeywordMask &result)		{ return _botKeywords.stringToMask(word, result); }
	static bool groupMask(const std::string &word, CKeywordMask &result)	{ return _groupKeywords.stringToMask(word, result); }
	static bool stateMask(const std::string &word, CKeywordMask &result)	{ return _stateKeywords.stringToMask(word, result); }

	static bool botFilter(const std::string &word, CKeywordFilter &result)	{ return _botKeywords.stringToFilter(word, result); }
	static bool groupFilter(const std::string &word, CKeywordFilter &result)	{ return _groupKeywords.stringToFilter(word, result); }
	static bool stateFilter(const std::string &word, CKeywordFilter &result)	{ return _stateKeywords.stringToFilter(word, result); }

private:
	static CKeywordSet _botKeywords;
	static CKeywordSet _groupKeywords;
	static CKeywordSet _stateKeywords;

private:
	// this is a singleton so prohibit construction
	CAIKeywords();
};	

#endif
