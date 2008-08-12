/** \file module.cpp
 * <File description>
 *
 * $Id: module.cpp,v 1.3 2004/09/07 16:54:09 distrib Exp $
 */

#include "module.h"
#include "module_core.h"
#include "module_parent.h"

//----------------------------------------------------------------------------
IModule::IModule( CModuleParent* parent, IModuleCore* referencedCore)
:_Parent(parent)
{
	MODULE_AST(parent);
	// we add the module to the parent as soon as it is created
	_Parent->addChildModule( this );
	// also add the module in the referenced core
	if(referencedCore)
	{
		MODULE_INFO( "building a module referencing a core" );
		referencedCore->addReferencingModule( this );
	}
	else
		MODULE_INFO( "building a module with no reference on a core" );
}

//----------------------------------------------------------------------------
void IModule::onParentDestruction()
{
	MODULE_INFO( "the parent of a module was destroyed, calling overriden handler" );
	// get a ref poniter on the module
	NLMISC::CRefPtr<IModule> ptr(this);
	// call the derived class handler
	onParentDestructionHandler();
	// if the operation did not delete the module, do it now
	if ( ptr )
	{
		MODULE_INFO( "The module deletes itself..." );
		delete ptr;
	}
	else
		MODULE_INFO( "the module was deleted by the overriden handler. We dont have to delete it" );
	
}

//----------------------------------------------------------------------------
void IModule::onReferencedDestruction()
{
	MODULE_INFO( "The module reference was deleted. Remove the module from the parent and delete it" );
	MODULE_AST( _Parent != NULL );
	// get a ref poniter on the module
	NLMISC::CRefPtr<IModule> ptr(this);
	// remove it from the parent
	_Parent->removeChildModule( this );
	// delete this module
	delete ptr;
}
