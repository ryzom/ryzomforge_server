/** \file fe_stat.cpp
 * <File description>
 *
 * $Id: fe_stat.cpp,v 1.7 2005/01/14 09:56:09 boucher Exp $
 */



#include "stdpch.h"

#include "fe_stat.h"

// Fix the stupid Visual 6 Warning
void foo_fe_stat_cpp() {};

#ifdef MEASURE_FRONTEND_TABLES

#include <nel/misc/debug.h>
#include "game_share/tick_event_handler.h"
//#include <sstream>

using namespace std;
using namespace NLMISC;


/*
 * setGameTick
 */
void		TEventPerSeenEntityCounterFrame::setGameTick()
{
	Tick = CTickEventHandler::getGameCycle();
}


/*
 * display
 */
void		TEventPerSeenEntityCounterFrame::display( bool withvalue )
{
	//std::stringstream ss;
	string str;
	//ss << (int)Tick;
	str += NLMISC::toString(Tick);
	sint i;
	for ( i=0; i!=250; ++i )
	{
		//ss << "\t" << SeenEntities[i];
		str += "\t" + NLMISC::toString(SeenEntities[i]);
	}
	if( withvalue )
	{
		//ss << "\t" << Value;
		str += "\t" + NLMISC::toString(Value);
	}
	InfoLog->displayRawNL( "%s", str.c_str() );
}


/*
 * displayAll (static)
 */
void		TEventPerSeenEntityCounterFrame::displayAll( const char *name, std::vector<TEventPerSeenEntityCounterFrame>& vect, bool withvalue )
{
	InfoLog->displayRawNL( "%s:", name );
	std::vector<TEventPerSeenEntityCounterFrame>::iterator icv;
	for ( icv=vect.begin(); icv!=vect.end(); ++icv )
	{
		(*icv).display( withvalue );
	}
	vect.clear();
}

TEventPerSeenEntityCounterFrame					PropRecvrCntFrame1, PropRecvrCntFrame2,
												DistCntFrame,
												DeltaCntFrame,
												PrioCntFrame,
												PosSentCntFrame;

std::vector<TEventPerSeenEntityCounterFrame>	PropRecvrCntClt1,
												DistCntClt1,
												DeltaCntClt1,
												PrioCntClt1,
												PosSentCntClt1;


#endif
