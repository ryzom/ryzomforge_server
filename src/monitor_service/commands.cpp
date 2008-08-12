/** \file commands.cpp
  

 	This file contains the list of command line commands for the ai_service service

 
 * $Id: commands.cpp,v 1.2 2004/03/01 19:22:18 lecroart Exp $
 */



#include "stdpch.h"

using namespace NLMISC;
using namespace NLNET;
using namespace std;

extern bool EmulateShard;

// ***************************************************************************

NLMISC_COMMAND(emulate,"Toggle emulate shard function","")
{
	EmulateShard ^= true;
	nlinfo ("Emulate shard mode %s", EmulateShard?"ON":"OFF");
	return true;
}
