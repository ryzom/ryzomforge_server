/** \file stat_db_tree_pd.h
 * 
 *
 * $Id: stat_db_tree_pd.h,v 1.1 2005/08/04 18:27:14 guignot Exp $
 */



#ifndef RY_STAT_DB_TREE_PD_H
#define RY_STAT_DB_TREE_PD_H

#include "nel/misc/entity_id.h"

#include "stat_db_common.h"
#include "game_share/persistent_data.h"


struct CStatDBValueLeafPD
{
	DECLARE_PERSISTENCE_METHODS

	CStatDBValueLeafPD() : Value(0) {}

	std::string Path;
	sint32		Value;
};

struct CStatDBTableLeafPD
{
	DECLARE_PERSISTENCE_METHODS

	std::string							Path;
	std::map<NLMISC::CEntityId,sint32>	PlayerValues;
	std::map<EGSPD::TGuildId,sint32>	GuildValues;
};

struct CStatDBValueLeavesPD
{
	DECLARE_PERSISTENCE_METHODS

	std::vector<CStatDBValueLeafPD>		ValueLeavesPD;
};


#endif // RY_STAT_DB_TREE_PD_H
