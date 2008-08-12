/** \file module.h
 * base interface for gameplay module. DO NOT INCLUDE THIS FILE INCLUDE "gameplay_module.h"
 *
 * $Id: module.h,v 1.4 2005/06/28 14:08:55 cado Exp $
 */

#ifndef RY_MODULE_H
#define RY_MODULE_H

#include "nel/misc/types_nl.h"
#include "nel/misc/smart_ptr.h"
#include "module_utils.h"
#include "module_parent.h"

class IModuleCore;

/**
 * A gameplay module. Implements the actions done by an element of a system ( e.g. : a player ) on an element of another system ( e.g. : a guild )
 * A module is responsible of cleaning himself. 
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class IModule : public NLMISC::CRefCount
{
public:
	/// ctor. Is in charge of registering the module on the parent and referenced core
	IModule( CModuleParent* parent, IModuleCore* referencedCore);
	virtual ~IModule(){}
	/// callback called when parent is deleted. It calls the onParentDestructionHandler virtual method
	void onParentDestruction();
	/// reference is destroyed. It destroys this module and remove it from parent
	void onReferencedDestruction();
	/// retrieve a "proxy" on the parent owner ( e.g. : the player )
	template <class T>
	void getProxy(T & proxy)const
	{
		MODULE_AST( _Parent );
		MODULE_AST( _Parent->getOwner() );
		// build the proxy on the fly : it only contains a pointer
		proxy = T(_Parent->getOwner());
	}
	
protected:
	/// pointer on the container containing this module
	NLMISC::CRefPtr<CModuleParent>	_Parent;
	/// virtual handler that you have to implement in your module. 
	/// e.g. :in case of a pet module, destroy the pet. 
	/// e. g. : in case of a guild call CGuild::removeReferencingModule(this);
	virtual void onParentDestructionHandler() = 0;
};

//#include "module_parent.h"
//#include "module_core.h"
//#include "module_inline.h"

#endif // RY_MODULE_H

/* End of module.h */
