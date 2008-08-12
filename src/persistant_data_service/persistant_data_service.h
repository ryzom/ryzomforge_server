/** \file persistant_data_service.h
 * <File description>
 *
 * $Id: persistant_data_service.h,v 1.2 2004/03/02 13:22:56 legros Exp $
 */

#ifndef NL_PERSISTANT_DATA_SERVICE_H
#define NL_PERSISTANT_DATA_SERVICE_H

#include "nel/misc/types_nl.h"
#include "nel/net/service.h"


/**
 * Persistant Data Service Class
 * \author Benjamin Legros
 * \author Nevrax France
 * \date 2004
 */
class CPersistantDataService : public NLNET::IService
{
public:

	/// Constructor
	CPersistantDataService();



	/// Initialization
	virtual void	init();

	/// Release
	virtual void	release();

	/// Update
	virtual bool	update();

};


#endif // NL_PERSISTANT_DATA_SERVICE_H

/* End of persistant_data_service.h */
