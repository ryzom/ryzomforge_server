/** \file ai_alias_description_node.cpp
 *
 * $Id: ai_alias_description_node.cpp,v 1.5 2004/07/30 15:33:53 boucher Exp $
 */



#include "stdpch.h"
//----------------------------------------------------------------------------

#include "ai_alias_description_node.h"

#include "nel/misc/common.h"
#include "nel/misc/command.h"

using namespace NLMISC;
//using namespace NLNET;
using namespace std;

std::vector<NLMISC::CSmartPtr<CAIAliasDescriptionNode> >	CAIAliasDescriptionNode::_aliasDescriptionList;

//---------------------------------------------------------------------------------------
// Stuff used for management of log messages

bool VerboseAliasDescriptionNodeLog=false;


//---------------------------------------------------------------------------------------
// Control over verbose nature of logging
//---------------------------------------------------------------------------------------

NLMISC_COMMAND(verboseAliasNodeTreeParserLog,"Turn on or off or check the state of verbose .primitive parser logging","")
{
	if(args.size()>1)
		return false;

	if(args.size()==1)
		StrToBool	(VerboseAliasDescriptionNodeLog, args[0]);

	nlinfo("verbose Logging is %s",VerboseAliasDescriptionNodeLog?"ON":"OFF");
	return true;
}

//---------------------------------------------------------------------------------------
