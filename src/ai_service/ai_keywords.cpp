/** \file ai_keywords.cpp
 *
 * $Id: ai_keywords.cpp,v 1.6 2006/05/31 12:10:21 boucher Exp $
 */




#include "stdpch.h"
#include "ai_keywords.h"
#include "nel/net/service.h"

using namespace NLMISC;
using namespace NLNET;

// singleton data instantiation

CKeywordSet CAIKeywords::_botKeywords;
CKeywordSet CAIKeywords::_groupKeywords;
CKeywordSet CAIKeywords::_stateKeywords;

void CAIKeywords::init()
{
	updateKeywordsFromCfg();
}

static void loadKeywordsFromCfg(const char *varName,CKeywordSet &wordSet)
{
	// get hold of the config file variable
	CConfigFile::CVar *varPtr;
	varPtr=IService::getInstance()->ConfigFile.getVarPtr(std::string(varName));
	if	(!varPtr)
	{
		nlwarning("WARNING: Config file variable: %s not found",varName);
		return;
	}

	// add config file variable contents to keyword set
	for (uint32 i=0;i<varPtr->size();++i)
		wordSet.addKeywords(varPtr->asString(i));
}

void CAIKeywords::updateKeywordsFromCfg()
{
	loadKeywordsFromCfg("KeywordsGroupNpc",_groupKeywords);
	loadKeywordsFromCfg("KeywordsBotNpc",_botKeywords);
	loadKeywordsFromCfg("KeywordsStateNpc",_stateKeywords);
}

void CAIKeywords::display()
{
	nlinfo ("bot keywords: %s",_botKeywords.toString().c_str());
	nlinfo ("group keywords: %s",_groupKeywords.toString().c_str());
	nlinfo ("state keywords: %s",_stateKeywords.toString().c_str());
}

