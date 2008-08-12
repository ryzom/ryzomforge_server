/** \file stats_globals.cpp
 *
 * Part of STAT Module for GUS (general utilities service)
 *
 * $id$
 */

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "nel/misc/variable.h"
#include "nel/misc/path.h"
#include "nel/net/service.h"
#include "game_share/utils.h"

#include "stat_globals.h"


//-----------------------------------------------------------------------------
// Namespaces
//-----------------------------------------------------------------------------

using namespace std;
using namespace NLMISC;


//-----------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------

CVariable<string>	ScriptDirectory("Stats", "ScriptDirectory", "Directory containing script files", string("./"), 0, true);
CVariable<string>	OutputDirectory("Stats", "OutputDirectory", "Directory containing output files", string("./"), 0, true);
CVariable<string>	InputFileDirectory("Stats", "InputFileDirectory", "Directory we scan for files", string("./"), 0, true);

typedef map<uint32,CSString> TAccountNames;
typedef map<uint32,CSString> TPerShardCharacterNames;
typedef map<CSString,TPerShardCharacterNames> TCharacterNames;
typedef map<uint32,CSString> TSheetNames;

TAccountNames	AccountNames;
TCharacterNames	CharacterNames;
TSheetNames		SheetNames;


//-----------------------------------------------------------------------------
// Methods
//-----------------------------------------------------------------------------

namespace STAT_GLOBALS
{
	NLMISC::CSString getInputFilePath(const NLMISC::CSString& path)
	{
		NLMISC::CSString pathRoot= NLMISC::CPath::standardizePath(InputFileDirectory.get());
		return (path.left(pathRoot.size())==pathRoot)? path: pathRoot+path;
	}

	NLMISC::CSString getScriptFilePath(const NLMISC::CSString& path)
	{
		NLMISC::CSString pathRoot= NLMISC::CPath::standardizePath(ScriptDirectory.get());
		return (path.left(pathRoot.size())==pathRoot)? path: pathRoot+path;
	}

	NLMISC::CSString getOutputFilePath(const NLMISC::CSString& path)
	{
		NLMISC::CSString pathRoot= NLMISC::CPath::standardizePath(OutputDirectory.get());
		return (path.left(pathRoot.size())==pathRoot)? path: pathRoot+path;
	}


	//-----------------------------------------------------------------------------
	// Text related methods
	//-----------------------------------------------------------------------------

	void clearAccountNames()
	{
		AccountNames.clear();
	}

	void clearAllCharacterNames()
	{
		CharacterNames.clear();
	}

	void clearCharacterNames(const NLMISC::CSString& shard)
	{
		CharacterNames[shard].clear();
	}

	void clearSheetNames()
	{
		SheetNames.clear();
	}

	void addAccountNameMapping(uint32 account,const NLMISC::CSString& name)
	{
		CSString& mapEntry= AccountNames[account];

		if (!mapEntry.empty() && mapEntry!=name)
		{
			nlinfo("duplicate mapping for account %d : %s / %s",account,name.c_str(),mapEntry.c_str());
			mapEntry+=" / "+name;
		}
		else
			mapEntry= name;
	}

	void addCharacterNameMapping(const NLMISC::CSString& shard,uint32 account,uint32 slot,const NLMISC::CSString& name)
	{
		DROP_IF( (account*16+slot)/16!= account, "Ignoring invalid account name / slot pair and associated name: "+NLMISC::toString("%u %d ",account,slot)+name+" (on shard "+shard+")", return );
		CSString& mapEntry= CharacterNames[shard][account*16+slot];

		if (!mapEntry.empty() && mapEntry!=name)
		{
			nlinfo("duplicate mapping for account %d : %s / %s",account,name.c_str(),mapEntry.c_str());
			mapEntry+=" / "+name;
		}
		else
			mapEntry= name;
	}

	void addSheetNameMapping(NLMISC::CSheetId sheetId,const NLMISC::CSString& name)
	{
		CSString& mapEntry= SheetNames[sheetId.asInt()];

		if (!mapEntry.empty() && mapEntry!=name)
		{
			nlinfo("duplicate mapping for sheet %d (%s) : %s",sheetId.asInt(),sheetId.toString().c_str(),mapEntry.c_str());
			mapEntry+=" / "+name;
		}
		else
			mapEntry= name;
	}

	const NLMISC::CSString& getAccountName(uint32 accountId)
	{
		return AccountNames[accountId];
	}

	const NLMISC::CSString& getCharacterName(const NLMISC::CSString& shard,uint32 account,uint32 slot)
	{
		static NLMISC::CSString emptyReturnValue;
		DROP_IF( (account*16+slot)/16!= account, "getCharacterName() failed for invalid account name / slot pair: "+NLMISC::toString("%u %d ",account,slot)+" (on shard "+shard+")", return emptyReturnValue);
		return CharacterNames[shard][account*16+slot];
	}

	const NLMISC::CSString& getSheetName(NLMISC::CSheetId sheetId)
	{
		return SheetNames[sheetId.asInt()];
	}

}
