/** \file commands.cpp
  

 	This file contains the list of command line commands for the ai_service service

 
 * $Id: ai_spawn_commands.cpp,v 1.13 2005/02/22 10:28:08 besson Exp $
 */


#include "stdpch.h"
// Nel Misc
#include "nel/misc/command.h"

#include "ai_spawn_commands.h"

// Fix the stupid Visual 6 Warning
void foo_ai_spawn_commands() {};


using namespace NLMISC;
using namespace std;


namespace AI_SHARE 
{

//-------------------------------------------------------------------------
// SPAWNING	COMMANDS

//NLMISC_COMMAND(spawnGrps,"spawn one of the versions of the group","<group id>")
//{
//	if(args.size() <1) return false;
//
//	for (uint i=0;i<args.size();++i)
//		CAISpawnCtrl::spawnGrp(args[i]);
//	
//	return true;
//}

//NLMISC_COMMAND(spawnMgrs,"spawn the population of one or more mgrs","[<mgr id>[...]]")
//{
//	if(args.size() <1) return false;
//
//	for (uint i=0;i<args.size();++i)
//		CAISpawnCtrl::spawnMgr(args[i]);
//	
//	return true;
//}

//NLMISC_COMMAND(spawnMaps,"spawn the population of one or more continents","[<continent name>[...]]")
//{
//	if(args.size() <1) return false;
//
//	for (uint i=0;i<args.size();++i)
//		CAISpawnCtrl::spawnMap(args[i]);
//	
//	return true;
//}

//NLMISC_COMMAND(spawnAll,"spawn the populations of all managers","")
//{
//	if(args.size() !=0) return false;
//	
//	CAISpawnCtrl::spawnAll();
//	
//	return true;
//}


//-------------------------------------------------------------------------
// DESPAWNING COMMANDS

//NLMISC_COMMAND(despawnGrps,"despawn populations of one or more groups","<group id> [<group id>[...]]")
//{
//	if(args.size() <1) return false;
//
//	for (uint i=0;i<args.size();++i)
//		CAISpawnCtrl::despawnGrp(args[i]);
//
//	return true;
//}
//
//NLMISC_COMMAND(despawnMgrs,"despawn the populations of one or more mgrs","[<mgr id>[...]]")
//{
//	if(args.size() <1) return false;
//
//	for (uint i=0;i<args.size();++i)
//		CAISpawnCtrl::despawnMgr(args[i]);
//	
//	return true;
//}
//
//NLMISC_COMMAND(despawnMaps,"despawn the population of one or more continents","[<continent id>[...]]")
//{
//	if(args.size() <1) return false;
//
//	for (uint i=0;i<args.size();++i)
//		CAISpawnCtrl::despawnMap(args[i]);
//	
//	return true;
//}
//
//NLMISC_COMMAND(despawnAll,"despawn the populations of all managers in service","")
//{
//	if(args.size() !=0) return false;
//
//	CAISpawnCtrl::despawnAll();
//
//	return true;
//}
//
// THIS LINE EXISTS TO MAKE SURE THE LINKER DOESN'T THROW OUT THIS MODULE AT LINK TIME!!!
bool LinkWithAiSpawnCommands=false;

} // end of namespace
