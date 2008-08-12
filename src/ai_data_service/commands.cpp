/** \file commands.cpp
  

 	This file contains the list of command line commands for the ags_test service

 
 * $Id: commands.cpp,v 1.5 2007/03/09 09:56:41 boucher Exp $
 */




// Nel Misc
#include "nel/net/service.h"
#include "nel/misc/command.h"

// Game share
#include "game_share/macro_manager.h"

// locals
#include "ai_files.h"
#include "ai_manager.h"
#include "ai_service.h"

using namespace NLMISC;
using namespace NLNET;
using namespace std;


//-------------------------------------------------------------------------
// utility routines

static void argsToManagerVector(const vector<string> &args, vector<CAIManager *> &theManagers)
{
	if(args.size()==0)
	{
		for (uint i=0;i<CAIManager::numManagers();++i)
			theManagers.push_back(CAIManager::getManagerByIdx(i));
	}
	else
	{
		for (uint i=0;i<args.size();++i)
		{
			int id=CAIManager::nameToId(args[i]);
			if (i==-1)
				nlwarning("Can't find a manger record for: %s",args[i].c_str());
			else
				theManagers.push_back(CAIManager::getManagerById(id));
		}
	}
}

//-------------------------------------------------------------------------
// scanning the hard disk for interesting files, compiling
// where nessessary	and allerting ai_service(s) of data file changes

NLMISC_COMMAND(aiRescanDirectories,"Rescan disk file directories","")
{
	if(args.size()!=0) return false;
	COMMAND_MACRO_RECORD_TEST

	CAIFiles::scan();

	return true;
}

NLMISC_COMMAND(aiMake,"scan the hard disk for interesting files, recompile as necessary and allert services","")
{
	COMMAND_MACRO_RECORD_TEST

	// rescan the source and object directories for files
	CAIFiles::scan();

	// build the list of ai managers to act on
	vector<CAIManager *> theManagers;
	argsToManagerVector(args,theManagers);

	// do the work
	for (uint i=0;i<theManagers.size();++i)
	{
		if (theManagers[i]->needCompile())
		{
			//nlinfo("Compiling manager: %04d: %s",theManagers[i]->id(),theManagers[i]->name());
			theManagers[i]->compile();
		}
		else
			nlinfo("Manager is up to date: %04d: %s",theManagers[i]->id(),theManagers[i]->name().c_str());
	}

	return true;
}

NLMISC_COMMAND(aiClean,"delete all generated files on the hard disk (next 'make' will rebuild everything)","")
{
	COMMAND_MACRO_RECORD_TEST

	// rescan the source and object directories for files
	CAIFiles::scan();

	// build the list of ai managers to act on
	vector<CAIManager *> theManagers;
	argsToManagerVector(args,theManagers);

	// do the work
	for (uint i=0;i<theManagers.size();++i)
	{
		nlinfo("Cleaning: %04d: %s",theManagers[i]->id(),theManagers[i]->name().c_str());
		theManagers[i]->clean();
	}

	return true;
}

//-------------------------------------------------------------------------

NLMISC_COMMAND(aiDisplayServices,"list the ai services, their parameters and their lists of running managers","[<service id>[...]]")
{
	if(args.size()!=0) return false;
	COMMAND_MACRO_RECORD_TEST

	return true;
}

NLMISC_COMMAND(aiDisplayManagers,"Display the known ai manager list","[<manager name|id>[...]]")
{
	COMMAND_MACRO_RECORD_TEST

	// build the list of ai managers to act on
	vector<CAIManager *> theManagers;
	argsToManagerVector(args,theManagers);

	// do the work
	for (uint i=0;i<theManagers.size();++i)
		theManagers[i]->display();

	return true;
}

//-------------------------------------------------------------------------
NLMISC_COMMAND(aiOpenAllManagers,"Open all managers and automatically assign to ai services","")
{
	if(args.size()!=0) return false;
	COMMAND_MACRO_RECORD_TEST

	for (uint i=0;i<CAIManager::numManagers();++i)
		if (!CAIManager::getManagerByIdx(i)->isOpen())
			CAIManager::getManagerByIdx(i)->open();

	return true;
}

NLMISC_COMMAND(aiOpenManagers,"Open managers and automatically assign to ai services","<manager name|id>[...]")
{
	if(args.size()<1) return false;
	COMMAND_MACRO_RECORD_TEST

	for (uint i=0;i<args.size();++i)
	{
		int id=CAIManager::nameToId(args[i]);
		if (i==-1)
			nlwarning("Can't find a manger record for: %s",args[i].c_str());
		else
			CAIManager::getManagerById(id)->open();
	}

	return true;
}

NLMISC_COMMAND(aiAssignManagers,"Open managers and assign to specified ai service","<service><manager name|id>[...]")
{
	if(args.size()<2) return false;
	COMMAND_MACRO_RECORD_TEST

	// convert args[0] to service id and verify existance in services list
	NLNET::TServiceId service(atoi(args[0].c_str()));
	if (service.get()==0 && args[0]!="0")
	{
		nlwarning("Invalid service id: %s",args[0].c_str());
		return false;
	}

	// iterate through args assigning managers to service
	for (uint i=1;i<args.size();++i)
	{
		int id=CAIManager::nameToId(args[i]);
		if (i==-1)
			nlwarning("Can't find a manger record for: %s",args[i].c_str());
		else
			CAIManager::getManagerById(id)->assign(service);
	}

	return true;
}

NLMISC_COMMAND(aiReassignManagers,"Save & close managers on existing services and open on specified ai service","<service><manager name|id>[...]")
{
	if(args.size()<2) return false;
	COMMAND_MACRO_RECORD_TEST

	// convert args[0] to service id and verify existance in services list
	NLNET::TServiceId service(atoi(args[0].c_str()));
	if (service.get()==0 && args[0]!="0")
	{
		nlwarning("Invalid service id: %s",args[0].c_str());
		return false;
	}

	// iterate through args reassigning managers to service
	for (uint i=1;i<args.size();++i)
	{
		int id=CAIManager::nameToId(args[i]);
		if (i==-1)
			nlwarning("Can't find a manger record for: %s",args[i].c_str());
		else
			CAIManager::getManagerById(id)->reassign(service);
	}

	return true;
}

//-------------------------------------------------------------------------
NLMISC_COMMAND(aiCloseAllManagers,"Close all managers across all ai services on the shard","")
{
	if(args.size()!=0) return false;
	COMMAND_MACRO_RECORD_TEST

	for (uint i=0;i<CAIManager::numManagers();++i)
		if (CAIManager::getManagerByIdx(i)->isOpen())
			CAIManager::getManagerByIdx(i)->close();

	return true;
}

NLMISC_COMMAND(aiCloseManagers,"Close listed managers","<manager name|id>[...]")
{
	if(args.size()<1) return false;
	COMMAND_MACRO_RECORD_TEST

	for (uint i=0;i<args.size();++i)
	{
		int id=CAIManager::nameToId(args[i]);
		if (i==-1)
			nlwarning("Can't find a manger record for: %s",args[i].c_str());
		else
			CAIManager::getManagerById(id)->close();
	}

	return true;
}

//-------------------------------------------------------------------------
