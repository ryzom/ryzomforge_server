/** \file common_pd.h
 * 
 * $Id: common_pd.h,v 1.13 2006/05/31 12:12:36 boucher Exp $
 */


#ifndef COMMON_PD_H
#define COMMON_PD_H

#include <nel/misc/types_nl.h>
#include <nel/misc/debug.h>
#include <nel/misc/common.h>
#include <vector>
#include <map>

// User #includes

namespace EGSPD
{
	
//
// Forward declarations
//



//
// Typedefs & Enums
//

/** TCharacterId
 * defined at entities_game_service\pd_scripts\egs_pd.pds:9
 */
typedef NLMISC::CEntityId TCharacterId;


/** TGuildId
 * defined at entities_game_service\pd_scripts\egs_pd.pds:10
 */
typedef uint32 TGuildId;


	
} // End of EGSPD


//
// Inline implementations
//

#include "common_pd_inline.h"

#endif
