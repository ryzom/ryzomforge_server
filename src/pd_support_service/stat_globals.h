/** \file stats_globals.h
 *
 * Part of STAT Module for GUS (general utilities service)
 *
 * $id$
 */

#ifndef STAT_GLOBALS_H
#define STAT_GLOBALS_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "nel/misc/types_nl.h"
#include "nel/misc/sstring.h"
#include "nel/misc/sheet_id.h"


//-----------------------------------------------------------------------------
// Methods
//-----------------------------------------------------------------------------

namespace STAT_GLOBALS
{
	NLMISC::CSString getInputFilePath(const NLMISC::CSString& path= NLMISC::CSString());
	NLMISC::CSString getScriptFilePath(const NLMISC::CSString& path= NLMISC::CSString());
	NLMISC::CSString getOutputFilePath(const NLMISC::CSString& path= NLMISC::CSString());

	void clearAccountNames();
	void clearAllCharacterNames();
	void clearCharacterNames(const NLMISC::CSString& shard);
	void clearSheetNames();

	void addAccountNameMapping(uint32 account,const NLMISC::CSString& name);
	void addCharacterNameMapping(const NLMISC::CSString& shard,uint32 account,uint32 slot,const NLMISC::CSString& name);
	void addSheetNameMapping(NLMISC::CSheetId sheetId,const NLMISC::CSString& name);

	const NLMISC::CSString& getAccountName(uint32 accountId);
	const NLMISC::CSString& getCharacterName(const NLMISC::CSString& shard,uint32 account,uint32 slot);
	const NLMISC::CSString& getSheetName(NLMISC::CSheetId sheetId);
}


//-----------------------------------------------------------------------------
#endif
