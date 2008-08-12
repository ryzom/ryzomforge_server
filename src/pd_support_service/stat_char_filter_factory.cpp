/** \file stats_char_filter_factory.cpp
 *
 * Part of STAT Module for GUS (general utilities service)
 *
 * $Id: stat_char_filter_factory.cpp,v 1.2 2007/05/09 15:33:12 boucher Exp $
 */


//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

#include "stat_char_filter_factory.h"


//-------------------------------------------------------------------------------------------------
// namespaces
//-------------------------------------------------------------------------------------------------

using namespace std;
using namespace NLMISC;


//-------------------------------------------------------------------------------------------------
// methods CCharFilterFactory
//-------------------------------------------------------------------------------------------------

CCharFilterFactory* CCharFilterFactory::getInstance()
{
	static CCharFilterFactory* ptr=NULL;
	if (ptr==NULL)
		ptr=new CCharFilterFactory;
	return ptr;
}

void CCharFilterFactory::registerFilter(NLMISC::CSmartPtr<ICharFilterBuilder> filter)
{
	// ensure that we don't have a name conflict with an existing info extractor
	for (uint32 i=0;i<_Filters.size();++i)
	{
		nlassert(filter->getName()!=_Filters[i]->getName());
	}

	// add the new info extractor
	_Filters.push_back(filter);
}

void CCharFilterFactory::displayFilterList(NLMISC::CLog* log)
{
	uint32 longestName=4;

	// iterate over the filters to determine the length of the longest name
	for (uint32 i=0;i<_Filters.size();++i)
	{
		std::string s= _Filters[i]->getName();
		if (s.size()>longestName)
			longestName=s.size();
	}

	// iterate over the filters displaying names and description
	for (uint32 i=0;i<_Filters.size();++i)
	{
		log->displayNL("%-*s  %s",longestName,_Filters[i]->getName(),_Filters[i]->getDescription());
	}
}

uint32 CCharFilterFactory::getFilterBuilderCount()
{
	return _Filters.size();
}

ICharFilterBuilder* CCharFilterFactory::getFilterBuilder(uint32 idx)
{
	nlassert(idx<_Filters.size());
	return _Filters[idx];
}

ICharFilter* CCharFilterFactory::build(const NLMISC::CSString& cmdLine)
{
	// split the command line into a command and a command tail (or arg set)
	CSString cmdTail=cmdLine;
	CSString cmd=cmdTail.firstWord(true).strip();

	for (uint32 i=0;i<_Filters.size();++i)
	{
		if (cmd==_Filters[i]->getName())
		{
			nlinfo("Adding filter: %s",cmdLine.c_str());
			return _Filters[i]->build(cmdTail);
		}
	}

	nlwarning("Unknown filter '%s' in line: %s",cmd.c_str(),cmdLine.c_str());
	return NULL;
}
