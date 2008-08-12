/** \file module_parent.h
 * Wrapper for a container of modules owned by a core. DO NOT INCLUDE THIS FILE INCLUDE "gameplay_module.h"
 *
 * $Id: module_parent.h,v 1.5 2006/01/10 17:38:58 boucher Exp $
 */

#ifndef RY_MODULE_PARENT_H
#define RY_MODULE_PARENT_H

#include "nel/misc/types_nl.h"
#include "nel/misc/smart_ptr.h"

#include "module_core.h"
#include "module_utils.h"

class ::IModuleCore;
class ::IModule;

/**
 * A module parent is a class encapsulating the modules contained in a module core
 * It mainly provides accessors to the modules
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CModuleParent : public NLMISC::CRefCount
{
public:
	/// ctor : a valid module core must be passed
	CModuleParent(::IModuleCore * owner)
		:_Owner(owner)
	{
		MODULE_AST(owner);
	};
	/// dtor : inform the modules that they must delete themselves
	~CModuleParent();
	
	/// returns the core owning of the modules
	::IModuleCore* getOwner()const{ return _Owner; }
	
	/// get a module of the specified type WARNING : the module must be unique
	template <class ModuleClass> 
	bool getModule( ModuleClass* & module )const
	{
		module = NULL;
		const uint size = _Modules.size();
		for (uint i = 0;i < size; i++ )
		{	
			ModuleClass * moduleChecked = dynamic_cast<ModuleClass*>( (::IModule*)_Modules[i] );
			if ( moduleChecked )
			{
				module = moduleChecked;
				// additional checks to ensure module uniqueness
#ifdef RY_MODULE_DEBUG
				for (uint j = i + 1; j < size; j++ )
				{
					ModuleClass * moduleTest = dynamic_cast<ModuleClass*>( (::IModule*)_Modules[j] );
					if ( moduleTest )
						nlerror("you required a unique module but there is more than 1!!!!");
				}
#endif
				return module != NULL ;
			}
		}
		return false;
	}
	/// get all the module of the specified type
	// I would have coded getModules( std::vector<ModuleClass> & modules ) but VC6 has an internal compiler error
	template <class ModuleClassVector, class ModuleClass>
	void getModules( ModuleClassVector &  modules,ModuleClass * dummy )const
	{
		const uint size = _Modules.size();
		for (uint i = 0;i < size; i++ )
		{	
			ModuleClass * module = dynamic_cast<ModuleClass*>( (::IModule*)_Modules[i]);
			if ( module )
				modules.push_back(module);
		}
	}
	
	/// remove a child module. Called by a module to remove itself from the parent
	void removeChildModule(::IModule* module);
	/// add a new module to this container. Called by a module to register itself in the parent
	void addChildModule(::IModule* module);
private:
	/// core owning this structure
	NLMISC::CRefPtr< ::IModuleCore>			_Owner;
	/// children modules
	std::vector< NLMISC::CRefPtr< ::IModule> >	_Modules;
};

//#include "module.h"
//#include "module_utils.h"
//#include "module_parent_inline.h"


#endif // RY_MODULE_PARENT_H

/* End of module_parent.h */
