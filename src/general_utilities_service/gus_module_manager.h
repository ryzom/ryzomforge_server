/** \file gus_module_manager.h
 *
 * $id$
 *
 */

#ifndef GUS_MODULE_MANAGER_H
#define GUS_MODULE_MANAGER_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "nel/misc/types_nl.h"
#include "nel/misc/sstring.h"
#include "nel/misc/smart_ptr.h"

#include "gus_module.h"
#include "gus_net_connection.h"


//-----------------------------------------------------------------------------
// GUS namespace
//-----------------------------------------------------------------------------

namespace GUS
{
	//-----------------------------------------------------------------------------
	// class CModuleManager
	//-----------------------------------------------------------------------------

	class CModuleManager
	{
	public:
		// get the singleton instance
		static CModuleManager* getInstance();

	public:
		// add a new module - returns id on success or ~0u on failure
		virtual uint32 addModule(const NLMISC::CSString& name,const NLMISC::CSString& rawArgs)=0;

		// remove a module
		virtual void removeModule(uint32 moduleId)=0;

		// display the set of active modules
		virtual void displayModules() const=0;

		// retrieve a module's unique id
		virtual uint32 getModuleId(const IModule* module) const=0;

		// lookup the module belonging to a given unique id
		virtual TModulePtr lookupModuleById(uint32 id) const=0;

		// get a vector of pointers to the active modules
		typedef std::vector<TModulePtr> TModuleVector;
		virtual void getModules(TModuleVector& result) const=0;
	};
}


//-----------------------------------------------------------------------------
#endif
