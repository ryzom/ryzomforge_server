/** \file keyword.cpp
 *
 * $Id: keyword.cpp,v 1.7 2004/03/01 19:19:20 lecroart Exp $
 */



#include "stdpch.h"
#include "keyword.h"

//---------------------------------------------------------------------------------
// CKeywordSet
//---------------------------------------------------------------------------------

void CKeywordSet::clear()
{
	_words.clear();
}

void CKeywordSet::addKeywords(const std::string &keywords)
{
	// chunkify the input string into white-space separated words
	std::string word, s=keywords;
	while (AI_SHARE::stringToWordAndTail(s,word,s))
	{
		if (_words.size()<32)
			_words.push_back(word);
		else
			nlwarning("Too many keywords for keyword set (limit to 32) - ignoring keyword: '%s'",word.c_str());
	}
}

bool CKeywordSet::stringToMask(std::string s, CKeywordMask &result) const
{
	bool ret = true;
	std::string word;
	while (AI_SHARE::stringToWordAndTail(s,word,s))
	{
		//look for the keyword in the word list
	  uint i;
		for (i=0;i<_words.size();++i)
			if (NLMISC::nlstricmp(word,_words[i])==0)
			{
				result._mask|=(1<<i);
				break;
			}
		if (i==_words.size())
		{
			nlwarning("Unknown keyword: '%s' in mask description: '%s'",word.c_str(),s.c_str());
			ret = false;
		}
	}
	return ret;
}

bool CKeywordSet::stringToFilter(std::string s, CKeywordFilter &result) const
{
//	CKeywordFilter result;
	bool ret = true;
	CKeywordMask *mask=&result._includeAny;
	std::string word;
	while (AI_SHARE::stringToWordAndTail(s,word,s))
	{
		if (word=="+" || word=="-")
		{
			// this is a + or - without ajoining word
			mask=(word[0]=='+')? &result._includeAll: &result._notInclude;
		}
		else
		{
			if (word[0]=='+' || word[0]=='-') 
			{
				// this is the case of the '+' or '-' immediately followed by the keyword
				mask=(word[0]=='+')? &result._includeAll: &result._notInclude;
				// prune the first character from the word so that we can drop through to common code
				word=word.substr(1);
			}

			//look for the keyword in the word list
			uint i;
			for (i=0;i<_words.size();++i)
				if (NLMISC::nlstricmp(word,_words[i])==0)
				{
					mask->_mask|=(1<<i);
					break;
				}
			if (i==_words.size())
			{
				nlwarning("Unknown keyword: '%s'",word.c_str());
				ret = false;
			}

			// reset the type for the next keyword
			mask=&result._includeAny;
		}
	}
	return ret;
}

std::string CKeywordSet::maskToString(CKeywordMask mask)	const
{
	std::string result;
	for (uint i=0;i<_words.size();++i)
		if (mask._mask&(1<<i))
			result+=_words[i]+' ';
	return result;
}

std::string CKeywordSet::filterToString(CKeywordFilter filter) const
{
	std::string result;
	for (uint i=0;i<_words.size();++i)
	  {
		if (filter._includeAll._mask&(1<<i))			result+=std::string("+")+_words[i]+' ';
		else if (filter._notInclude._mask&(1<<i))		result+=std::string("-")+_words[i]+' ';
		if (filter._notInclude._mask&(1<<i))			result+=_words[i]+' ';
	  }
	return result;
}

std::string CKeywordSet::toString()
{
	std::string s;
	for (uint i=0;i<_words.size();++i)
		s+=_words[i]+' ';
	return s;
}
 
//---------------------------------------------------------------------------------
