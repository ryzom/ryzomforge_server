/** \file cc_contest_ctrl_script.h
 *
 * $id$
 *
 */

#ifndef CC_CONTEST_CTRL_SCRIPT_H
#define CC_CONTEST_CTRL_SCRIPT_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "nel/misc/sstring.h"
#include "nel/misc/entity_id.h"


//-----------------------------------------------------------------------------
// class CContestCtrlScript
//-----------------------------------------------------------------------------

class CContestCtrlScript
{
public:
	// get hold of the singleton instance
	static CContestCtrlScript* getInstance();

public:
	// load the script file
	virtual void load(const NLMISC::CSString& fileName)=0;

	// start running the loaded script
	virtual void start()=0;

	// set the delay value for the current 'wait' or 'wait for answer' script line
	virtual void setDelay(uint32 duration)=0;

	// stop running the loaded script
	virtual void stop()=0;

	// list the currently loaded script
	virtual void list()=0;

	// display the current state of the ctrl script singleton
	virtual void display()=0;
};


//-----------------------------------------------------------------------------
#endif
