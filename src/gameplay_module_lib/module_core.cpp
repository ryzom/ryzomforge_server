/** \file module_core.cpp
 * <File description>
 *
 * $Id: module_core.cpp,v 1.4 2004/08/12 09:25:53 lecroart Exp $
 */

#include "module_core.h"
#include "module.h"
#include "module_parent.h"

//----------------------------------------------------------------------------
IModuleCore::~IModuleCore()
{
	MODULE_INFO( "Module core destructor : inform all referencing module and delete the contained module parent" );
	const uint size = _ModulesReferencingMe.size();
	for ( uint i = 0; i < size; i++ )
	{
		if ( _ModulesReferencingMe[i] )
			_ModulesReferencingMe[i]->onReferencedDestruction();
	}
	delete _ModulesCont;
}
//----------------------------------------------------------------------------
IModuleCore::IModuleCore()
{
	_ModulesCont = new CModuleParent(this);
}

//----------------------------------------------------------------------------
void IModuleCore::addReferencingModule(IModule * module)
{
	MODULE_INFO( "Module core : simply adding a referencing module" );
	MODULE_AST( module );
#ifdef RY_MODULE_DEBUG
	NLMISC::CRefPtr<IModule> ref(module);
	std::vector< NLMISC::CRefPtr<IModule> >::iterator it( std::find( _ModulesReferencingMe.begin(), _ModulesReferencingMe.end(), ref ) );
	if ( it != _ModulesReferencingMe.end() )
		nlerror("a referencing module was added twice");
#endif
	_ModulesReferencingMe.push_back( module );
}

//----------------------------------------------------------------------------
void IModuleCore::removeReferencingModule(IModule * module)
{
	MODULE_INFO( "Module core : simply removeing a referencing module without deleting it" );
	MODULE_AST( module );
	NLMISC::CRefPtr<IModule> ref(module);
	std::vector< NLMISC::CRefPtr<IModule> >::iterator it( std::find( _ModulesReferencingMe.begin(), _ModulesReferencingMe.end(), ref ) );
	if ( it == _ModulesReferencingMe.end() )
	{
		nlwarning("<MODULE> cant find referencing module");
		return;
	}
	_ModulesReferencingMe.erase(it);
}
