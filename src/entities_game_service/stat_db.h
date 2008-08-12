/** \file stat_db.h
 * 
 *
 * $Id: stat_db.h,v 1.15 2007/02/01 16:25:12 boucher Exp $
 */



#ifndef RY_STAT_DB_H
#define RY_STAT_DB_H

#include "nel/misc/static_map.h"
#include "game_share/stat_db_msg.h"
#include "game_share/stat_db_tree.h"
#include "game_share/stat_db_tree_pd.h"
#include "game_share/stat_db_tree_visitor.h"

class CFileDescription;

/**
 * This class collects leaves and furnishes their persistent data for backup
 * 
 * \author Sébastien 'kxu' Guignot
 * \author Nevrax France
 * \date 2005 July
 */
class CStatDBBackupLeafCollector : private CStatDBNodeVisitor
{
public:
	void loadLeaves(IStatDBNodePtr root);

	bool isEmpty() { return _ValueLeavesPD.ValueLeavesPD.empty() && _TableLeafPaths.empty(); }

	CStatDBValueLeavesPD & getValueLeavesPD() { return _ValueLeavesPD; }
	bool popTableLeafPD(CStatDBTableLeafPD & tableLeafPD);

private:
	void visitValueLeaf(CStatDBValueLeaf * valueLeaf, const std::string & path);
	void visitTableLeaf(CStatDBTableLeaf * tableLeaf, const std::string & path);

	void clearLeaves()
	{
		_ValueLeavesPD.ValueLeavesPD.clear();
		_TableLeafPaths.clear();
	}

private:
	IStatDBNodePtr				_Root;
	CStatDBValueLeavesPD		_ValueLeavesPD;
	std::vector<std::string>	_TableLeafPaths;
};

/**
 * This class collects all leaves and furnishes the message data for MFS init
 * 
 * \author Sébastien 'kxu' Guignot
 * \author Nevrax France
 * \date 2005 July
 */
class CStatDBMFSInitLeafCollector : private CStatDBNodeVisitor
{
public:
	void loadLeaves(IStatDBNodePtr root, CStatDBAllLeavesMsg & allLeavesMsg);

private:
	void visitValueLeaf(CStatDBValueLeaf * valueLeaf, const std::string & path);
	void visitTableLeaf(CStatDBTableLeaf * tableLeaf, const std::string & path);

private:
	CStatDBAllLeavesMsg * _AllLeavesMsg;
};

/**
 * This class displays a node of SDB
 * 
 * \author Sébastien 'kxu' Guignot
 * \author Nevrax France
 * \date 2005 July
 */
class CStatDBNodeDisplayer : private CStatDBNodeVisitor
{
public:
	struct CSettings
	{
		CSettings() { setDefaults(); }

		void setDefaults()
		{
			Recursive				= true;
			DisplayBranch			= true;
			DisplayValueLeaf		= true;
			DisplayValueLeafContent	= true;
			DisplayTableLeaf		= true;
			DisplayTableLeafContent	= true;
		}

		bool Recursive					: 1;
		bool DisplayBranch				: 1;
		bool DisplayValueLeaf			: 1;
		bool DisplayValueLeafContent	: 1;
		bool DisplayTableLeaf			: 1;
		bool DisplayTableLeafContent	: 1;
	};

public:
	CStatDBNodeDisplayer() : _Log(NULL) {}

	void setSettings(const CSettings & settings) { _Settings = settings; }
	const CSettings & getSettings() const { return _Settings; }

	void displayNode(IStatDBNodePtr node, const std::string & currentPath, NLMISC::CLog & log);

private:
	void visitBranch(CStatDBBranch * branch, const std::string & path);
	void visitValueLeaf(CStatDBValueLeaf * valueLeaf, const std::string & path);
	void visitTableLeaf(CStatDBTableLeaf * tableLeaf, const std::string & path);

	void displayOneNode(IStatDBNodePtr node, const std::string & currentPath);

private:
	NLMISC::CLog *	_Log;
	CSettings		_Settings;
};

/**
 * Database to store statistics
 *
 * \author Matthieu 'Trap' Besson
 * \author Nevrax France
 * \date 2005 July
 */
class CStatDB
{
public:
	/// get the singleton instance
	static CStatDB * getInstance()
	{
		if (_Instance == NULL)
			_Instance = new CStatDB;
		return _Instance;
	}

	/// load the database
	void load();

	/// value leave file callback from BS
	void  valueLeaveFileCallback(const CFileDescription& fileDescription, NLMISC::IStream& dataStream);
	/// table leaf file callback from BS
	void  tableLeaveFileCallback(const CFileDescription& fileDescription, NLMISC::IStream& dataStream);
	
	/// called each tick
	void tickUpdate();

	/// save all the database (called when EGS quits)
	void saveAll();

	/// create a value leaf
	bool createValue(const std::string & path, sint32 val);

	/// modify/read a value leaf
	bool valueSet(const std::string & path, sint32 val);
	bool valueAdd(const std::string & path, sint32 val);
	bool valueGet(const std::string & path, sint32 & val);

	/// create a table leaf
	bool createTable(const std::string & path);
	bool createTable(const std::string & path,
		const std::map<NLMISC::CEntityId,sint32> & playerValues,
		const std::map<EGSPD::TGuildId,sint32> & guildValues
		);

	/// modify/read a table leaf
	bool tablePlayerAdd(const std::string & path, NLMISC::CEntityId playerId, sint32 val);
	bool tableGuildAdd(const std::string & path, EGSPD::TGuildId guildId, sint32 val);
	bool tablePlayerSet(const std::string & path, NLMISC::CEntityId playerId, sint32 val);
	bool tableGuildSet(const std::string & path, EGSPD::TGuildId guildId, sint32 val);
	bool tablePlayerGet(const std::string & path, NLMISC::CEntityId playerId, sint32& val);
	bool tableGuildGet(const std::string & path, EGSPD::TGuildId guildId, sint32& val);

	/// remove a node
	/// \param path : path of the node to remove
	/// \param keepBackupOfFiles : set if a copy of deleted save files is kept
	bool removeNode(const std::string & path, bool keepBackupOfFiles = true);

	/// remove a player from the whole database
	void removePlayer(NLMISC::CEntityId playerId);
	/// remove a guild from the whole database
	void removeGuild(EGSPD::TGuildId guildId);

	/// display nodes in log
	bool displayNodes(const std::string & pathPattern, NLMISC::CLog & log, const CStatDBNodeDisplayer::CSettings & settings);

	void cbMFServiceUp();
	void cbMFServiceDown();
	void cbGuildsLoaded();

private:
	/// private ctor
	CStatDB();

	bool canInitMFS() const;
	void initMFS();

	void saveValueLeaves(const CStatDBValueLeavesPD & valueLeavesPD);
	void saveTableLeaf(const CStatDBTableLeafPD & tableLeafPD);

private:
	/// singleton instance
	static CStatDB * _Instance;

	/// root node
	IStatDBNodePtr				_Root;

	/// the collector of data to backup
	CStatDBBackupLeafCollector	_BackupLeafCollector;

	/// this removes players and guilds if asked by removePlayer() and removeGuild() methods
	CStatDBEntitiesRemoval		_EntitiesRemoval;

	bool	_SDBIsLoaded;
	bool	_GuildsAreLoaded;
	bool	_MFSIsUp;
	bool	_MFSIsInitialized;
};


#endif // RY_STAT_DB_H

