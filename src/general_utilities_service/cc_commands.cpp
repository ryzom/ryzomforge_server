/** \file cc_commands.cpp
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
#include "cc_contest_ctrl_script.h"


//-----------------------------------------------------------------------------
// Namespaces
//-----------------------------------------------------------------------------

using namespace std;
using namespace NLMISC;


//-----------------------------------------------------------------------------
// CContestCtrlScript Commands
//-----------------------------------------------------------------------------

NLMISC_CATEGORISED_COMMAND(ContestCtrl,ccAdvance,"adavnce the clock to the end of the current delay","")
{
	CNLSmartLogOverride logOverride(&log);

	if (args.size()!=0)
		return false;

	CContestCtrlScript::getInstance()->setDelay(0);

	return true;
}

NLMISC_CATEGORISED_COMMAND(ContestCtrl,ccDisplayState,"display the state of the contest control module","")
{
	CNLSmartLogOverride logOverride(&log);

	if (args.size()!=0)
		return false;

	CContestCtrlScript::getInstance()->display();

	return true;
}

NLMISC_CATEGORISED_COMMAND(ContestCtrl,ccLoad,"load a contest control script","<filename>")
{
	CNLSmartLogOverride logOverride(&log);

	CSString ccsFileName;
	switch (args.size())
	{
	case 0:
		ccsFileName.readFromFile("gus_cc_last_ccs.txt");
		break;

	case 1:
		ccsFileName= args[0];
		ccsFileName.writeToFile("gus_cc_last_ccs.txt");
		break;

	default:
		return false;
	}

	CContestCtrlScript::getInstance()->load(ccsFileName);

	return true;
}

NLMISC_CATEGORISED_COMMAND(ContestCtrl,ccQuit,"stop running the current contest control script","")
{
	CNLSmartLogOverride logOverride(&log);

	if (args.size()!=0)
		return false;

	CContestCtrlScript::getInstance()->stop();

	return true;
}

NLMISC_CATEGORISED_COMMAND(ContestCtrl,ccRun,"start running the current contest control script","")
{
	CNLSmartLogOverride logOverride(&log);

	if (args.size()!=0)
		return false;

	CContestCtrlScript::getInstance()->start();

	return true;
}

NLMISC_CATEGORISED_COMMAND(ContestCtrl,ccShow,"show the current contest control script","")
{
	CNLSmartLogOverride logOverride(&log);

	if (args.size()!=0)
		return false;

	CContestCtrlScript::getInstance()->list();

	return true;
}

NLMISC_CATEGORISED_COMMAND(ContestCtrl,ccWait,"modify duration of current pause","<time to wait in seconds>")
{
	CNLSmartLogOverride logOverride(&log);

	if (args.size()!=1)
		return false;

	sint32 time= atoi(args[0].c_str());
	if (time<=0)
		return false;

	CContestCtrlScript::getInstance()->setDelay(time*1000);

	return true;
}


//-----------------------------------------------------------------------------
