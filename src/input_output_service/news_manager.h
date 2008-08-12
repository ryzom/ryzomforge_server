/** \file news_manager.h
 * This class manages the news in the input service
 *
 * $Id: news_manager.h,v 1.4 2007/05/22 13:42:54 boucher Exp $
 */



#ifndef NEWS_MANAGER_H
#define NEWS_MANAGER_H


// misc
#include "nel/misc/types_nl.h"
#include "nel/misc/bit_mem_stream.h"

// game share
#include "game_share/ryzom_entity_id.h"
//#include "game_share/chat_static_database.h"
//#include "game_share/chat_dynamic_database.h"
#include "game_share/news_types.h"

// std
#include <map>
#include <string>


/**
 * CNewsManager
 * \author Vianney Lecroart
 * \author Nevrax France
 * \date 2002
 */
class CNewsManager 
{
public :

	/**
	 * Init the manager.
	 */
	static void init ();

	/// return a news of a given type
	static void getNews (NEWSTYPE::TNewsType type, NLMISC::CBitMemStream &bms);
};


#endif // NEWS_MANAGER_H

/* End of news_manager.h */
