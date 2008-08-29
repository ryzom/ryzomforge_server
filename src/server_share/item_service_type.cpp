/** \file item_service_type.cpp
 * 
 * $Id: item_service_type.cpp,v 1.1 2005/02/07 15:52:30 guignot Exp $
 */

#include "stdpch.h"

#include "nel/misc/string_conversion.h"
#include "item_service_type.h"

using namespace std;
using namespace NLMISC;

namespace ITEM_SERVICE_TYPE
{

	NL_BEGIN_STRING_CONVERSION_TABLE (TItemServiceType)
		NL_STRING_CONVERSION_TABLE_ENTRY(StableFeedAnimal1)
		NL_STRING_CONVERSION_TABLE_ENTRY(StableFeedAnimal2)
		NL_STRING_CONVERSION_TABLE_ENTRY(StableFeedAnimal3)
		NL_STRING_CONVERSION_TABLE_ENTRY(StableFeedAnimal4)
		NL_STRING_CONVERSION_TABLE_ENTRY(StableFeedAllAnimals)
		NL_STRING_CONVERSION_TABLE_ENTRY(SpeedUpDPLoss)
	NL_END_STRING_CONVERSION_TABLE(TItemServiceType, ItemServiceTypeConversion, Unknown)

	TItemServiceType fromString(const std::string & str)
	{
		return ItemServiceTypeConversion.fromString(str);
	}

	const std::string & toString(TItemServiceType itemServiceType)
	{
		return ItemServiceTypeConversion.toString(itemServiceType);
	}

} // namespace ITEM_SERVICE_TYPE
