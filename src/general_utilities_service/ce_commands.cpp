/** \file ce_commands.cpp
 *
 * $id$
 *
 */

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

//nel
#include "nel/misc/command.h"

// game share
#include "game_share/utils.h"

// local
#include "gus_net_types.h"
#include "ce_contest_executor.h"


//-----------------------------------------------------------------------------
// Namespaces
//-----------------------------------------------------------------------------

using namespace std;
using namespace NLMISC;
using namespace GUSNET;
using namespace GUS;


//-----------------------------------------------------------------------------
// CContestExecutor Commands
//-----------------------------------------------------------------------------

NLMISC_CATEGORISED_COMMAND(ContestExecutor,ceAnswer,"submit an answer","<player_id> <answer>")
{
	CNLSmartLogOverride logOverride(&log);

	if (args.size()!=2)
		return false;

	CContestExecutor::getInstance()->submitAnswer(TDataSetRow(), args[0], ucstring(args[1]));

	return true;
}

NLMISC_CATEGORISED_COMMAND(ContestExecutor,ceChatTexts,"load the file of static chat messages","<file name>")
{
	CNLSmartLogOverride logOverride(&log);

	if (args.size()!=1)
		return false;

	if (CContestExecutor::getInstance()->readChatTextFile(args[0]))
	{
		log.displayNL("Chat text file '%s' loaded", args[0].c_str());
	}
	else
	{
		log.displayNL("FAILED to load file '%s'", args[0].c_str());
	}

	return true;
}

NLMISC_CATEGORISED_COMMAND(ContestExecutor,ceDisplayState,"display the state of the contest executor module","")
{
	CNLSmartLogOverride logOverride(&log);

	if (args.size()!=0)
		return false;

	CContestExecutor::getInstance()->display();

	return true;
}


//-----------------------------------------------------------------------------
