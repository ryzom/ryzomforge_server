/** \file gus_module_factory.cpp
 *
 * $id$
 *
 */

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "game_share/utils.h"

#include "gus_module_factory.h"


//-----------------------------------------------------------------------------
// namespaces
//-----------------------------------------------------------------------------

using namespace std;
using namespace NLMISC;


//-----------------------------------------------------------------------------
// GUS namespace
//-----------------------------------------------------------------------------

namespace GUS
{
	//-----------------------------------------------------------------------------
	// methods CModuleFactory
	//-----------------------------------------------------------------------------

	CModuleFactory::CModuleFactory()
	{
	}

	CModuleFactory* CModuleFactory::getInstance()
	{
		static CModuleFactory* ptr=NULL;
		if (ptr==NULL)
			ptr= new CModuleFactory;
		return ptr;
	}

	void CModuleFactory::registerModuleBuilder(TModuleBuilderPtr moduleBuilderPtr)
	{
		// make sure we nevre register 2 module builders with the same name
		for (uint32 i=0;i<_ModuleBuilders.size();++i)
		{
			nlassert(_ModuleBuilders[i]->getName()!=moduleBuilderPtr->getName());
		}

		// add this module builder to the list...
		_ModuleBuilders.push_back(moduleBuilderPtr);
	}

	CSmartPtr<IModule> CModuleFactory::buildNewModule(const CSString& name,const CSString& rawArgs)
	{
		// look for a module name that matches the supplied name
		for (uint32 i=0;i<_ModuleBuilders.size();++i)
		{
			if(_ModuleBuilders[i]->getName()==name)
			{
				// we found a module builder with given name so have it build the new module
				return _ModuleBuilders[i]->buildNewModule(rawArgs);
			}
		}

		// if we're here the name wasn't matched
		BOMB("Failed to instantiate module due to unrecognised name: "+name+" ("+rawArgs+")",return NULL);
	}

	void CModuleFactory::display()
	{
		if (_ModuleBuilders.empty())
		{
			nlinfo("No module types registered");
			return;
		}

		// calculate length of longest module name & parameter block
		uint32 maxNameLen= 0;
		uint32 maxArgsLen= 0;
		for (uint32 i=0;i<_ModuleBuilders.size();++i)
		{
			maxNameLen= std::max(maxNameLen,(uint32)(_ModuleBuilders[i]->getName().size()));
			maxArgsLen= std::max(maxArgsLen,(uint32)(_ModuleBuilders[i]->getArgs().size()));
		}

		// display the module list
		InfoLog->displayNL("Registered module types:");
		for (uint32 i=0;i<_ModuleBuilders.size();++i)
		{
			InfoLog->displayNL("\t%-*s %-*s %s",
				maxNameLen,	_ModuleBuilders[i]->getName().c_str(),
				maxArgsLen,	_ModuleBuilders[i]->getArgs().c_str(),
							_ModuleBuilders[i]->getDescription().c_str());
		}
	}
}
