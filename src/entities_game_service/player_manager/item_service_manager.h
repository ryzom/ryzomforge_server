/** \file item_service_manager.h
 *
 * $Id: item_service_manager.h,v 1.2 2005/02/08 17:06:31 guignot Exp $
 */



#ifndef RY_ITEM_SERVICE_MANAGER_H
#define RY_ITEM_SERVICE_MANAGER_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "game_share/item_service_type.h"

//-----------------------------------------------------------------------------

class CCharacter;
class CStaticItem;
class IItemServiceProvider;

/**
 * This class provides services associated to items (aka "item services")
 * \author Sébastien Guignot
 * \author Nevrax France
 * \date 2005
 */
class CItemServiceManager
{
public:
	/// get the singleton instance
	static CItemServiceManager * getInstance()
	{
		if (_Instance == NULL)
		{
			_Instance = new CItemServiceManager();
		}
		return _Instance;
	}

	/// register a service provider in the manager
	void registerServiceProvider(ITEM_SERVICE_TYPE::TItemServiceType serviceType, IItemServiceProvider * serviceProvider);

	/// returns true if the service associated with the item is available for the client
	bool serviceIsAvailable(const CStaticItem * form, CCharacter * client);

	/// returns the base price of the service associated with the item for the client
	uint32 getServicePrice(const CStaticItem * form, CCharacter * client);

	/// provide service associated with the item to the client, returns false if service is not available
	bool provideService(const CStaticItem * form, CCharacter * client);

	/// init persistent services of the client (it must be called each time the client reconnects)
	void initPersistentServices(CCharacter * client);

	/// remove a persistent service of the given type from the client
	/// \return the removed persistent service form or NULL if client has no persistent service of the given type
	const CStaticItem * removePersistentService(ITEM_SERVICE_TYPE::TItemServiceType serviceType, CCharacter * client);

private:
	/// private ctor
	CItemServiceManager();

	/// singleton instance
	static CItemServiceManager * _Instance;

	/// service providers
	std::vector<IItemServiceProvider *> _ServiceProviders;
};


#endif // RY_ITEM_SERVICE_MANAGER_H

/* End of item_service_manager.h */
