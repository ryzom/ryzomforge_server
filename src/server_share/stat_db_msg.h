/** \file stat_db_msg.h
 * 
 *
 * $Id: stat_db_msg.h,v 1.1 2005/08/04 18:27:13 guignot Exp $
 */



#ifndef RY_STAT_DB_MSG_H
#define RY_STAT_DB_MSG_H

#include "nel/misc/entity_id.h"
#include "nel/misc/stream.h"

#include "stat_db_common.h"


struct CStatDBValueLeafMsg
{
	void serial(NLMISC::IStream & f)
	{
		f.serial(Path);
		f.serial(Value);
	}

	CStatDBValueLeafMsg() : Value(0) {}

	std::string Path;
	sint32		Value;
};

struct CStatDBTableLeafMsg
{
	void serial(NLMISC::IStream & f)
	{
		f.serial(Path);
		f.serialCont(PlayerValues);
		f.serialCont(GuildValues);
	}

	std::string							Path;
	std::map<NLMISC::CEntityId,sint32>	PlayerValues;
	std::map<EGSPD::TGuildId,sint32>	GuildValues;
};

struct CStatDBNamesMsg
{
	void serial(NLMISC::IStream & f)
	{
		f.serialCont(PlayerNames);
		f.serialCont(GuildNames);
	}

	std::map<NLMISC::CEntityId,std::string>	PlayerNames;
	std::map<EGSPD::TGuildId,std::string>	GuildNames;
};

struct CStatDBAllLeavesMsg
{
	void serial(NLMISC::IStream & f)
	{
		f.serialCont(ValueLeavesMsg);
		f.serialCont(TableLeavesMsg);
		f.serial(NamesMsg);
	}

	std::vector<CStatDBValueLeafMsg>	ValueLeavesMsg;
	std::vector<CStatDBTableLeafMsg>	TableLeavesMsg;
	CStatDBNamesMsg						NamesMsg;
};


#endif // RY_STAT_DB_MSG_H
