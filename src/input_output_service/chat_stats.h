/** \file chat_stats.h
 * This class keeps statistics about the strings used in the chat
 *
 * $Id: chat_stats.h,v 1.3 2004/03/01 19:22:05 lecroart Exp $
 */



#ifndef CHAT_STATS_H
#define CHAT_STATS_H

// misc
#include "nel/misc/types_nl.h"

// std
#include <map>
#include <string>


 
/**
 * CChatStats
 * \author Stephane Coutelas
 * \author Nevrax France
 * \date 2002
 */
class CChatStats
{
public :
	
	/**
	 * Add an occurence of a string, create entry if this string is new
	 */
	void addOccurence( const std::string& str );

private :

	/// occurrences of the strings
	std::map<std::string,uint32> _Occurences;
	
};


#endif // CHAT_STATS_H

/* End of chat_stats.h */
