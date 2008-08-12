/** \file ios_pd.h
 * Initialisation of the IOSPD database, declarations
 * 
 * 
 * $Id: ios_pd.h,v 1.4 2007/05/22 13:42:54 boucher Exp $
 */
#error

#ifndef IOS_PD_H
#define IOS_PD_H

#include <nel/misc/types_nl.h>
#include <pd_lib/pd_lib.h>

namespace IOSPD
{
	

//
// Global Forward Declarations
//


//

/// \name Public API for IOSPD database
// @{

/**
 * Initialise the whole database engine.
 * Call this function at service init.
 */
void							init(uint32 overrideDbId);

/**
 * Tells if database engine is ready to work.
 * Engine may not be ready because PDS is down, not yet ready
 * or message queue to PDS is full.
 */
bool							ready();

/**
 * Update the database engine.
 * Call this method once per tick, only if engine is ready (see also ready() above).
 */
void							update();

/**
 * Logs chat sentence with sender and receipiants.
 */
void							logChat(const ucstring& sentence, const NLMISC::CEntityId& from, const std::vector<NLMISC::CEntityId>& to);

/**
 * Logs tell sentence with sender and single recipient (might be player or group).
 */
void							logTell(const ucstring& sentence, const NLMISC::CEntityId& from, const NLMISC::CEntityId& to);

/**
 * Release the whole database engine.
 * Call this function at service release.
 */
void							release();

// @}

extern RY_PDS::CPDSLib	PDSLib;
	
} // End of IOSPD

//
// Includes
//

#include "ios_chat_log.h"

#include "ios_chat_log_inline.h"

//


#include "ios_pd_inline.h"


#endif
