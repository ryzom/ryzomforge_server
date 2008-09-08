/** \file stdpch.h
 *
 *
 *	This is the ai_srevice executable's precopiled header controler file
 *
 *
 *
 *
 * $Id: stdpch.h,v 1.3 2004/03/01 19:22:18 lecroart Exp $
 */




//----------------------------------------------------------------
// external files
//----------------------------------------------------------------

// this is up top because it contains a certain number of #pragmas to
// control compiler warnings with stlport

#include "nel/misc/types_nl.h"


//----------------------------------------------------------------
// std libs

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


//----------------------------------------------------------------
// stl

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
//#include <sstream>
#include <exception>
#include <utility>
#include <deque>


//----------------------------------------------------------------
// nel

#include "nel/misc/common.h"
#include "nel/misc/debug.h"
#include "nel/misc/command.h"
#include "nel/misc/variable.h"
#include "nel/misc/sheet_id.h"
#include "nel/misc/entity_id.h"
#include "nel/misc/file.h"
#include "nel/misc/path.h"
#include "nel/misc/time_nl.h"
#include "nel/misc/random.h"
#include "nel/misc/smart_ptr.h"

#include "nel/misc/vector_2d.h"
#include "nel/misc/vectord.h"

//----------------------------------------------------------------
// nel net
#include "nel/net/message.h"
#include "nel/net/unified_network.h"
#include "nel/net/service.h"
#include "nel/net/callback_server.h"

//----------------------------------------------------------------
// game share

#include "game_share/ryzom_entity_id.h"
#include "game_share/mode_and_behaviour.h"
#include "game_share/player_visual_properties.h"
#include "server_share/ai_event.h"

