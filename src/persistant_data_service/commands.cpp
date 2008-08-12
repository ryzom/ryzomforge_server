/** \file commands.cpp
 * <File description>
 *
 * $Id: commands.cpp,v 1.4 2004/05/05 14:41:05 legros Exp $
 */

#include <nel/misc/types_nl.h>
#include <nel/misc/command.h>
#include <nel/misc/variable.h>

#include <nel/misc/file.h>
#include <nel/misc/i_xml.h>

#include "pds_database.h"

#include "pd_lib/timestamp.h"

using namespace std;
using namespace NLMISC;



NLMISC_COMMAND(testStamp, "", "")
{
	if (args.size() != 1)
		return false;

	CTimestamp	stamp;

	stamp.fromString(args[0].c_str());

	return true;
}

