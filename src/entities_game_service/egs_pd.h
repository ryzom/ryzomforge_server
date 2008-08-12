/** \file egs_pd.h
 * Initialisation of the EGSPD database, declarations
 * 
 * 
 * $Id: egs_pd.h,v 1.20 2007/05/09 15:33:06 boucher Exp $
 */


#ifndef EGS_PD_H
#define EGS_PD_H

#include <nel/misc/types_nl.h>
#include <pd_lib/pd_lib.h>

namespace EGSPD
{
	

//
// Global Forward Declarations
//

class CFameContainerEntryPD;
class CFameContainerPD;
class CGuildFameContainerPD;
class CGuildMemberPD;
class CGuildPD;
class CGuildContainerPD;
class CActiveStepStatePD;
class CActiveStepPD;
class CDoneStepPD;
class CMissionCompassPD;
class CMissionTeleportPD;
class CMissionInsidePlacePD;
class CMissionOutsidePlacePD;
class CHandledAIGroupPD;
class CMissionPD;
class CMissionGuildPD;
class CMissionTeamPD;
class CMissionSoloPD;
class CMissionContainerPD;

//

/// \name Public API for EGSPD database
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
	
} // End of EGSPD

//
// Includes
//

#include "common_pd.h"
#include "game_share/people_pd.h"
#include "game_share/sp_type.h"
#include "game_share/guild_grade.h"
#include "game_share/season.h"
#include "fame_pd.h"
#include "guild_member_pd.h"
#include "guild_pd.h"
#include "guild_container_pd.h"
#include "mission_pd.h"

#include "fame_pd_inline.h"
#include "guild_member_pd_inline.h"
#include "guild_pd_inline.h"
#include "guild_container_pd_inline.h"
#include "mission_pd_inline.h"

//


#include "egs_pd_inline.h"


#endif
