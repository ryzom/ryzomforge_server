/** \file stats_char_info_extractor_factory.cpp
 *
 * Part of STAT Module for GUS (general utilities service)
 *
 * $Id: stat_char_info_extractor_factory.cpp,v 1.1 2005/01/18 18:50:39 miller Exp $
 */


//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

#include "stat_char_info_extractor_factory.h"


//-------------------------------------------------------------------------------------------------
// namespaces
//-------------------------------------------------------------------------------------------------

using namespace std;
using namespace NLMISC;


//-------------------------------------------------------------------------------------------------
// methods CCharInfoExtractorFactory
//-------------------------------------------------------------------------------------------------

CCharInfoExtractorFactory* CCharInfoExtractorFactory::getInstance()
{
	static CCharInfoExtractorFactory* ptr=NULL;
	if (ptr==NULL)
		ptr=new CCharInfoExtractorFactory;
	return ptr;
}

void CCharInfoExtractorFactory::registerInfoExtractor(NLMISC::CSmartPtr<ICharInfoExtractorBuilder> infoExtractor)
{
	// ensure that we don't have a name conflict with an existing info extractor
	for (uint32 i=0;i<_InfoExtractors.size();++i)
	{
		nlassert(infoExtractor->getName()!=_InfoExtractors[i]->getName());
	}

	// add the new info extractor
	_InfoExtractors.push_back(infoExtractor);
}

void CCharInfoExtractorFactory::displayInfoExtractorList(NLMISC::CLog* log)
{
	uint32 longestName=4;

	// iterate over the infoExtractors to determine the length of the longest name
	for (uint32 i=0;i<_InfoExtractors.size();++i)
	{
		std::string s= _InfoExtractors[i]->getName();
		if (s.size()>longestName)
			longestName=s.size();
	}

	// iterate over the infoExtractors displaying names and description
	for (uint32 i=0;i<_InfoExtractors.size();++i)
	{
		log->displayNL("%-*s  %s",longestName,_InfoExtractors[i]->getName(),_InfoExtractors[i]->getDescription());
	}
}

uint32 CCharInfoExtractorFactory::getInfoExtractorBuilderCount()
{
	return _InfoExtractors.size();
}

ICharInfoExtractorBuilder* CCharInfoExtractorFactory::getInfoExtractorBuilder(uint32 idx)
{
	nlassert(idx<_InfoExtractors.size());
	return _InfoExtractors[idx];
}

ICharInfoExtractor* CCharInfoExtractorFactory::build(const NLMISC::CSString& cmdLine)
{
	// split the command line into a command and a command tail (or arg set)
	CSString cmdTail=cmdLine;
	CSString cmd=cmdTail.firstWord(true).strip();

	for (uint32 i=0;i<_InfoExtractors.size();++i)
	{
		if (cmd==_InfoExtractors[i]->getName())
		{
			nlinfo("Adding info extractor: %s",cmdLine.c_str());
			return _InfoExtractors[i]->build(cmdTail);
		}
	}

	nlwarning("Unknown info extractor '%s' in line: %s",cmd.c_str(),cmdLine.c_str());
	return NULL;
}
