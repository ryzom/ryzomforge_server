/** \file module_parent.cpp
 * <File description>
 *
 * $Id: module_parent.cpp,v 1.5 2004/08/04 16:39:40 weeklyserver Exp $
 */

#include "module_core.h"
#include "module_parent.h"
#include "module.h"

//----------------------------------------------------------------------------
CModuleParent::~CModuleParent()
{
	MODULE_INFO( "Module parent destruction : calling the Ondestruction handler for all modules" );
	// as module could be removed from thi parent in IModule::onParentDestruction, we have do remove modules with this strange way
	std::vector< NLMISC::CRefPtr<IModule> > modules = _Modules;
	for (uint i = 0; i < modules.size(); i++ )
	{
		if ( modules[i] )
		{
			modules[i]->onParentDestruction();
		}
	}
}

//----------------------------------------------------------------------------
void CModuleParent::removeChildModule(IModule* module)
{
	MODULE_INFO( "Module parent : simply removing a child module" );
	MODULE_AST( module );
	MODULE_AST(_Owner);
	NLMISC::CRefPtr<IModule> ref(module);
	std::vector< NLMISC::CRefPtr<IModule> >::iterator it( std::find( _Modules.begin(), _Modules.end(), ref ) );
	if ( it == _Modules.end() )
	{
		nlwarning("<MODULE> cant find the module to remove");
		return;
	}
	_Modules.erase(it);
}

//----------------------------------------------------------------------------
void CModuleParent::addChildModule(IModule* module)
{
	MODULE_INFO( "Module parent : simply adding a child module" );
	MODULE_AST( module );
#ifdef RY_MODULE_DEBUG	
	NLMISC::CRefPtr<IModule> ref(module);
	std::vector< NLMISC::CRefPtr<IModule> >::iterator it( std::find( _Modules.begin(), _Modules.end(), ref ) );
	if ( it != _Modules.end() )
		nlerror("a module was added twice");
#endif
	_Modules.push_back(module);
}

