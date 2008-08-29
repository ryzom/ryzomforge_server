/** \file item_service_type.h
 *
 * $Id: item_service_type.h,v 1.1 2005/02/07 15:52:30 guignot Exp $
 */

#ifndef RY_ITEM_SERVICE_TYPE_H
#define RY_ITEM_SERVICE_TYPE_H

#include <string>

namespace ITEM_SERVICE_TYPE
{

	enum TItemServiceType
	{
		StableFeedAnimal1,
		StableFeedAnimal2,
		StableFeedAnimal3,
		StableFeedAnimal4,
		StableFeedAllAnimals,
		SpeedUpDPLoss,

		Unknown,
		NbItemServiceType = Unknown
	};

	TItemServiceType fromString(const std::string & str);
	const std::string & toString(TItemServiceType itemServiceType);

} // namespace ITEM_SERVICE_TYPE

#endif // RY_ITEM_SERVICE_TYPE_H
