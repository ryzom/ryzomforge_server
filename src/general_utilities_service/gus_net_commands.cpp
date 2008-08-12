/** \file gus_net_commands.cpp
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
#include "gus_net.h"


//-----------------------------------------------------------------------------
// Namespaces
//-----------------------------------------------------------------------------

using namespace std;
using namespace NLMISC;
using namespace GUSNET;
using namespace GUS;


//-----------------------------------------------------------------------------
// CGusNet Commands
//-----------------------------------------------------------------------------

NLMISC_CATEGORISED_COMMAND(GUSNET,gusnetDisplay,"display the net hubs, connections and remote modules","")
{
	CNLSmartLogOverride logOverride(&log);

	if (args.size()!=0)
		return false;

	CGusNet::getInstance()->display();

	return true;
}


//-----------------------------------------------------------------------------
