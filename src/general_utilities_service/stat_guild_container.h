/** \file stat_guild_container.h
 *
 * Part of STAT Module for GUS (general utilities service)
 *
 * $Id: stat_guild_container.h,v 1.1 2005/04/25 23:57:36 miller Exp $
 */

#ifndef STAT_GUILD_CONTAINER_H
#define STAT_GUILD_CONTAINER_H

//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

#include "nel/misc/smart_ptr.h"
#include "nel/misc/sstring.h"
#include "game_share/persistent_data_tree.h"


//-------------------------------------------------------------------------------------------------
// class CStatGuildContainer
//-------------------------------------------------------------------------------------------------

class CStatGuildContainer: public NLMISC::CRefCount
{
public:
	CStatGuildContainer();
	~CStatGuildContainer();

public:
	// interface for the guild scan job to use
	void startScan();
	void addGuildFile(const NLMISC::CSString& fileName, CPersistentDataRecord& fileContent);
	void endScan();

	// handy introspection routines
	void display(NLMISC::CLog* log=NLMISC::InfoLog);

	// write a table (line per guild member), columns: file name, guild name, guild id, rank, entry date, account, slot 
	void writeMemberListFile(const NLMISC::CSString& path);

	// write a table (line per item in guild inventory), columns: file name, guild name, guild id, slot, <item stats>
	void writeInventoryFile(const NLMISC::CSString& path);

	// write a table (line per guild), columns for all basic properties of the guild
	void writeMiscDataFile(const NLMISC::CSString& path);

private:
	// the data representation for a guild file
	struct CGuildFile
	{
		NLMISC::CSString FileName;
		CPersistentDataTree FileContent;
	};

	typedef std::vector<CGuildFile> TGuildFiles;
	TGuildFiles _GuildFiles;

	bool _InProgress;
};


//-------------------------------------------------------------------------------------------------
#endif
