/** \file gus_module_commands.cpp
 *
 * System commands for GUS (general utility service)
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
#include "gus_module_manager.h"
#include "gus_module_factory.h"


//-----------------------------------------------------------------------------
// Namespaces
//-----------------------------------------------------------------------------

using namespace std;
using namespace NLMISC;
using namespace GUS;


//-----------------------------------------------------------------------------
// CModuleManager Commands
//-----------------------------------------------------------------------------

NLMISC_CATEGORISED_COMMAND(GUS,modulesAdd,"add a module to the GUS service","<module_name>[<args>]")
{
	CNLSmartLogOverride logOverride(&log);

	if (args.size()<1)
		return false;

	NLMISC::CSString rawArgs= rawCommandString;
	rawArgs.strtok(" \t");
	NLMISC::CSString moduleType= rawArgs.strtok(" \t");
	CModuleManager::getInstance()->addModule(moduleType,rawArgs);

	return true;
}

NLMISC_CATEGORISED_COMMAND(GUS,modulesRemove,"remove a module from the GUS service","<module_id>")
{
	CNLSmartLogOverride logOverride(&log);

	if (args.size()<1)
		return false;

	NLMISC::CSString rawArgs= rawCommandString;
	rawArgs.strtok(" \t");
	uint32 moduleId= atoi(rawArgs.c_str());
	if (NLMISC::toString("%u",moduleId)==rawArgs)
	{
		// try to find the module by numeric id
		TModulePtr module= CModuleManager::getInstance()->lookupModuleById(moduleId);
		DROP_IF(module==NULL,"Module not found: "+rawArgs,return true);
		nlinfo("Removing module %3d: %s %s",moduleId,module->getName().c_str(),module->getParameters().c_str());
		CModuleManager::getInstance()->removeModule(moduleId);
		return true;
	}

	// try to find the module by name or name & params
	CModuleManager::TModuleVector modules;
	CModuleManager::getInstance()->getModules(modules);
	for (uint32 i=modules.size();i--;)
	{
		CSString moduleDescription= CSString()+modules[i]->getName()+" "+modules[i]->getParameters();
		if (rawArgs==moduleDescription.left(rawArgs.size()))
		{
			uint32 moduleId= CModuleManager::getInstance()->getModuleId(modules[i]);
			nlinfo("Removing module %3d: %s %s",moduleId,modules[i]->getName().c_str(),modules[i]->getParameters().c_str());
			CModuleManager::getInstance()->removeModule(moduleId);
			return true;
		}
	}

	return false;
}

NLMISC_CATEGORISED_COMMAND(GUS,modulesDisplay,"display the states of the currently active modules","[<id>]")
{
	CNLSmartLogOverride logOverride(&log);

	switch (args.size())
	{
	case 0:
		// display a list of active modules
		CModuleManager::getInstance()->displayModules();
		return true;

	case 1:
		{
			// treat the case where we have a numeric module ID
			uint32 moduleId= atoi(args[0].c_str());
			if (NLMISC::toString(moduleId)==args[0])
			{
				// try to find the module by numeric id
				TModulePtr theModule= CModuleManager::getInstance()->lookupModuleById(moduleId);
				DROP_IF(theModule==NULL,"Module not found: "+args[0],return true);
				theModule->displayModule();
				return true;
			}
		}
		break;
	}

	// get a list of active modules from the module manager
	CModuleManager::TModuleVector modules;
	CModuleManager::getInstance()->getModules(modules);

	NLMISC::CSString rawArgs= rawCommandString;
	rawArgs.strtok(" \t");

	// iterate over all modules looking for matches against our args
	bool found=false;
	for (uint32 i=modules.size();i--;)
	{
		CSString moduleDescription= CSString()+modules[i]->getName()+" "+modules[i]->getParameters();
		if (rawArgs==moduleDescription.left(rawArgs.size()))
		{
			// display a matching module's details
			modules[i]->displayModule();
			found=true;
		}
	}

	WARN_IF(!found,"Module not found: "+rawArgs);
	return true;
}


//-----------------------------------------------------------------------------
// CModuleFactory Commands
//-----------------------------------------------------------------------------

NLMISC_CATEGORISED_COMMAND(GUS,modulesListTypes,"display the list of valid module types","")
{
	CNLSmartLogOverride logOverride(&log);

	if (args.size()!=0)
		return false;

	CModuleFactory::getInstance()->display();

	return true;
}


//-----------------------------------------------------------------------------
