/** \file module_core_inline.h
 * <File description>
 *
 * $Id: module_core_inline.h,v 1.2 2004/08/04 16:39:40 weeklyserver Exp $
 */

/*
//----------------------------------------------------------------------------
inline IModuleCore::IModuleCore()
{
	_ModulesCont = new CModuleParent(this);
}

//----------------------------------------------------------------------------
inline void IModuleCore::addReferencingModule(IModule * module)
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
inline void IModuleCore::removeReferencingModule(IModule * module)
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
*/
