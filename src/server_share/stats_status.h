/** \file stats_status.h
 * definition of the different status for statistics (used for coding status of stats for client)
 *
 * $Id: stats_status.h,v 1.2 2004/03/01 19:21:54 lecroart Exp $
 */



#ifndef RY_STATS_STATUS_H
#define RY_STATS_STATUS_H

#include "nel/misc/types_nl.h"

namespace STATS_STATUS
{
	// Size
	enum EStatsStatus
	{
		NORMAL = 0,
		UNBUFFED,
		BUFFED,

		// the number of size existing
		NB_STATS_STAUS,
		UNKNOWN,
	};
}; // STATS_STATUS

#endif // RY_STATS_STATUS_H
/* End of file stats_status.h */
