/** \file module_parent_inline.h
 * <File description>
 *
 * $Id: module_parent_inline.h,v 1.4 2004/08/04 17:20:26 brigand Exp $
 */

/*
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
*/
