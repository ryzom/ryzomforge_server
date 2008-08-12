/** \file time_interface.cpp
 *
 * $Id: time_interface.cpp,v 1.26 2005/04/26 12:37:02 brigand Exp $
 */



#include "stdpch.h"
#include "time_interface.h"
#include "game_share/tick_event_handler.h"
#include "ai.h"
#include "ai_instance.h"
#include "ai_mgr.h"

using namespace NLNET;
using namespace NLMISC;
using namespace std;

CTimeDateSeasonManager	CTimeInterface::_TimeDateSeason;
bool					CTimeInterface::_isDay;
CRyzomTime				CTimeInterface::_DebugTime;
