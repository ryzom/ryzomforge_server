/** \file chat_client.cpp
 * This class keeps statistics about the strings used in the chat
 *
 * $Id: chat_stats.cpp,v 1.4 2004/07/30 15:33:53 boucher Exp $
 */


#include "stdpch.h"
#include "chat_stats.h"
#include "nel/misc/debug.h"

using namespace std;


//-----------------------------------------------
//	addOccurence :
//
//-----------------------------------------------
void CChatStats::addOccurence( const string& str )
{
	map<string,uint32>::iterator itOcc = _Occurences.find( str );
	if( itOcc != _Occurences.end() )
	{
		(*itOcc).second++;
	}
	else
	{
		nlwarning("<CChatStats::addOccurence> The string %s is unknown",str.c_str());
	}

} // addOccurence //

