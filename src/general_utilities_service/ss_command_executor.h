/** \file ss_command_executor.h
 *
 * Part of SS (shqrd_script) Module for GUS (general utility service)
 *
 * $id$
 */


#ifndef SS_COMMAND_EXECUTOR_H
#define SS_COMMAND_EXECUTOR_H


//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

// nel
#include "nel/misc/sstring.h"


//-------------------------------------------------------------------------------------------------
// class CCommandExecutor
//-------------------------------------------------------------------------------------------------

class CCommandExecutor
{
private:
	// this is a singleton so make ctor private
	CCommandExecutor();

public:
	// singleton accessor
	static CCommandExecutor* getInstance();

public:
	// add a command to the command list
	void addCommand(NLMISC::CSString command);

	// display the list of pending commands
	void display() const;

	// execute the commands for the next tick
	void tickUpdate();

private:
	// private data
	typedef std::vector<NLMISC::CSString> TCommands;
	TCommands _Commands;
};


//-------------------------------------------------------------------------------------------------
#endif
