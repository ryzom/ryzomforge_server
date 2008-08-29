/** \file creature_size.cpp
 * 
 * $Id: creature_size.cpp,v 1.2 2004/03/01 19:21:52 lecroart Exp $
 */



#include "stdpch.h"

#include "nel/misc/debug.h"
#include "creature_size.h"

using namespace std;

namespace CREATURE_SIZE
{
	static map< string, ECreatureSize > StringToSizeMap;
	static map< ECreatureSize, string > SizeToStringMap;	

	static bool mapInitialized = false;
	const static string unknown_str = "UNKNOWN";


	//-----------------------------------------------
	// initMap :
	//-----------------------------------------------
	void initMap()
	{
		mapInitialized = true;

		StringToSizeMap.insert( make_pair( string("SMALL"), SMALL) );
		SizeToStringMap.insert( make_pair( SMALL, string("SMALL") ) );

		StringToSizeMap.insert( make_pair( string("HOMIN"), HOMIN) );
		SizeToStringMap.insert( make_pair( HOMIN, string("HOMIN") ) );

		StringToSizeMap.insert( make_pair( string("BIG"), BIG) );
		SizeToStringMap.insert( make_pair( BIG, string("BIG") ) );

	} // initMap //

	//-----------------------------------------------
	// stringToCreatureSize :
	//-----------------------------------------------
	ECreatureSize stringToCreatureSize(const string &str)
	{
		if ( !mapInitialized)
			initMap();

		map< string, ECreatureSize >::const_iterator it = StringToSizeMap.find( str );
		if (it != StringToSizeMap.end() )
		{
			return (*it).second;
		}
		else
		{
			return UNKNOWN;
		}
	} // stringToCreatureSize //


	//-----------------------------------------------
	// creatureSizeToString :
	//-----------------------------------------------
	const string &creatureSizeToString(ECreatureSize size)
	{
		if ( !mapInitialized)
			initMap();

		map< ECreatureSize, string >::const_iterator it = SizeToStringMap.find( size );
		if (it != SizeToStringMap.end() )
		{
			return (*it).second;
		}
		else
		{
			return unknown_str;
		}
	} // creatureSizeToString //

}; // CREATURE_SIZE
