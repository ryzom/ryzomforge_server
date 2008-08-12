/** \file module_core.h
 * definition of the module core interface. DO NOT INCLUDE THIS FILE INCLUDE "gameplay_module.h"
 *
 * $Id: module_core.h,v 1.3 2006/01/10 17:38:58 boucher Exp $
 */

#ifndef RY_MODULE_CORE_H
#define RY_MODULE_CORE_H

#include "nel/misc/types_nl.h"
#include "nel/misc/smart_ptr.h"

class IModule;
class CModuleParent;


/**
 * A module Core class ( a character, a guild,... )
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class IModuleCore : public NLMISC::CRefCount
{
public:
	/// ctor : allocate the internal module parent structure
	IModuleCore();
	/// dtor : delete the module parent structure
	virtual ~IModuleCore();
	/// return the parent module
	CModuleParent & getModuleParent(){ return *_ModulesCont; }
	/// add a module referencing this corer class
	void addReferencingModule( ::IModule * module );
	/// remove a module referencing this corer class
	void removeReferencingModule( ::IModule * module );
	
	template <class ModuleClass> 
	bool getReferencingModule( ModuleClass* & module)const
	{
		module = NULL;
		const uint size = _ModulesReferencingMe.size();
		for (uint i = 0; i < size; i++ )
		{	
			ModuleClass * moduleChecked = dynamic_cast<ModuleClass*>( (::IModule*)_ModulesReferencingMe[i] );
			if ( moduleChecked )
			{
				module = moduleChecked;
				// additional checks to ensure module uniqueness
#ifdef RY_MODULE_DEBUG
				for (uint j = i + 1; j < size; j++ )
				{
					ModuleClass * moduleTest = dynamic_cast<ModuleClass*>( (::IModule*)_ModulesReferencingMe[j] );
					if ( moduleTest )
						nlerror("you required a unique referencing module but there is more than 1!!!!");
				}
#endif
				return true;
			}
		}
		return false;
	}

	/// get all the referencing module of the specified type
	// I would have coded getModules( std::vector<ModuleClass> & modules ) but VC6 has an internal compiler error
	template <class ModuleClassVector, class ModuleClass>
	void getReferencingModules( ModuleClassVector &  modules,ModuleClass * dummy )const
	{
		const uint size = _ModulesReferencingMe.size();
		for (uint i = 0;i < size; i++ )
		{	
			ModuleClass * module = dynamic_cast<ModuleClass*>( (::IModule*)_ModulesReferencingMe[i]);
			if ( module )
				modules.push_back(module);
		}
	}


	//std::vector< NLMISC::CRefPtr<IModule> > & getReferencingModules(){ return _ModulesReferencingMe; };
protected:
	/// the module parent of this core structure
	NLMISC::CRefPtr<CModuleParent>			_ModulesCont;
	/// the modules referencing this structure
	std::vector< NLMISC::CRefPtr< ::IModule> >	_ModulesReferencingMe;
};

//#include "module_parent.h"
//#include "module_core_inline.h"

#endif // RY_MODULE_CORE_H

/* End of module_core.h */
