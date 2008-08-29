/** \file stat_db.cpp
 * 
 *
 * $Id: stat_db_tree_pd.cpp,v 1.2 2005/09/15 12:42:07 berenguier Exp $
 */


#include "stdpch.h"
#include "stat_db_tree_pd.h"


using namespace std;
using namespace NLMISC;


#define PERSISTENT_TOKEN_FAMILY RyzomTokenFamily


#define PERSISTENT_MACROS_AUTO_UNDEF

// ****************************************************************************
#define PERSISTENT_CLASS CStatDBValueLeafPD

#define PERSISTENT_DATA\
	PROP(string,Path)\
	PROP(sint32,Value)\

#pragma message( PERSISTENT_GENERATION_MESSAGE )
#include "game_share/persistent_data_template.h"

// ****************************************************************************
#define PERSISTENT_CLASS CStatDBTableLeafPD

#define PERSISTENT_DATA\
	PROP(string,Path)\
	PROP_MAP(CEntityId,sint32,PlayerValues)\
	PROP_MAP(EGSPD::TGuildId,sint32,GuildValues)\

#pragma message( PERSISTENT_GENERATION_MESSAGE )
#include "game_share/persistent_data_template.h"

// ****************************************************************************
#define PERSISTENT_CLASS CStatDBValueLeavesPD

#define PERSISTENT_DATA\
	STRUCT_VECT(ValueLeavesPD)\

#pragma message( PERSISTENT_GENERATION_MESSAGE )
#include "game_share/persistent_data_template.h"
