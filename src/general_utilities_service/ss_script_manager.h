/** \file ss_script_manager.h
 *
 * Part of SS (shqrd_script) Module for GUS (general utility service)
 *
 * $id$
 */


#ifndef SS_SCRIPT_MANAGER_H
#define SS_SCRIPT_MANAGER_H

//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

// nel
#include "nel/misc/types_nl.h"

// local
#include "ss_script_manager.h"
#include "ss_command_executor.h"


//-------------------------------------------------------------------------------------------------
// class CScriptManager
//-------------------------------------------------------------------------------------------------

class CScriptManager
{
private:
	// this is a singleton so make ctor private
	CScriptManager();

public:
	// singleton accessor
	static CScriptManager* getInstance();

public:
	// clear the set of loaded scripts from RAM
	void clear();

	// read the named script file
	bool readScriptFile(const std::string& fileName);

	// display the contents of the script manager
	void display() const;

	// add a line to a named script
	void addScriptLine(const std::string& scriptName,const std::string& line);

	// run the named script (if it exists)
	void runScript(const std::string& scriptName,uint32 delay=0) const;

private:
	// private data
	typedef std::vector<NLMISC::CSString> TScriptLines;
	typedef std::map<NLMISC::CSString,TScriptLines> TScripts;

	TScripts _Scripts;
};


//-------------------------------------------------------------------------------------------------
#endif
