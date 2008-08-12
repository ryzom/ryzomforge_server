/** \file utils.h
 *
 * $Id: utils.h,v 1.2 2007/05/09 15:33:12 boucher Exp $
 */


#ifndef PDSS_UTILS_H
#define PDSS_UTILS_H


//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

#include "nel/misc/sstring.h"


//-------------------------------------------------------------------------------------------------
// Handy utilities
//-------------------------------------------------------------------------------------------------

NLMISC::CSString buildDateString(uint32 timeValue);
NLMISC::CSString buildDowTimeString(uint32 timeValue);
NLMISC::CSString buildDurationString(uint32 timeValue);

NLMISC::CSString lookupSessionName(uint32 shardId);
uint32 lookupSessionId(const NLMISC::CSString& sessionName);


#endif // PDSS_UTILS_H
