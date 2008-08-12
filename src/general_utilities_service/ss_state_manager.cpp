/** \file ss_state_manager.cpp
 *
 * Part of SS (shqrd_script) Module for GUS (general utility service)
 *
 * $id$
 */

//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

// game share
#include "game_share/utils.h"

// local
#include "ss_state_manager.h"
#include "ss_script_manager.h"


//-------------------------------------------------------------------------------------------------
// GLOBALS
//-------------------------------------------------------------------------------------------------

static const char* StateFileName="shard_script_active_states.txt";


//-------------------------------------------------------------------------------------------------
// methods CStateManager
//-------------------------------------------------------------------------------------------------

CStateManager::CStateManager() 
{
	// read the states from a file
	NLMISC::CSString stateTxt;
	if (NLMISC::CFile::fileExists(StateFileName))
	{
		stateTxt.readFromFile(StateFileName);
		stateTxt.splitLines(_States);
	}

	// display the loaded state list
	display();
}

CStateManager* CStateManager::getInstance()
{
	static CStateManager* ptr=NULL;
	if (ptr==NULL)
		ptr= new CStateManager;

	return ptr;
}

void CStateManager::clearValidStateList()
{
	_ValidStates.clear();
}

void CStateManager::addValidState(const NLMISC::CSString& stateName)
{
	if (stateName.countWords()!=1)
	{
		nlwarning("Invalid state name: %s",stateName.c_str());
		return;
	}
	_ValidStates.insert(stateName.strip());
}

void CStateManager::resetAll()
{
	_States.clear();
}

bool CStateManager::beginState(const NLMISC::CSString& stateName)
{
	// make sure the state is valid
	if (_ValidStates.find(stateName.strip())==_ValidStates.end())
	{
		nlwarning("Cannot start state as it is not in valid state list: %s",stateName.c_str());
		return false;
	}

	// make sure the state isn't already active
	for (uint32 i=0;i<_States.size();++i)
	{
		if (_States[i]==stateName)
		{
			nlwarning("Cannot start state as it is already active: %s",stateName.c_str());
			return false;
		}
	}

	// set the state as active
	_States.push_back(stateName);

	// write the states to a file
	NLMISC::CSString stateTxt;
	stateTxt.join(_States,"\n");
	stateTxt.writeToFile(StateFileName);

	// execute the begin_state script
	CScriptManager::getInstance()->runScript("begin_"+stateName);

	return true;
}

bool CStateManager::endState(const NLMISC::CSString& stateName)
{
	uint32 i;

	// make sure the state is already active
	for (i=0;i<_States.size();++i)
	{
		if (_States[i]==stateName)
		{
			break;
		}
	}
	if (i==_States.size())
	{
		nlwarning("Cannot end state as it is not already active: %s",stateName.c_str());
		return false;
	}

	// set the state as inactive
	_States.erase(_States.begin()+i);

	// write the states to a file
	NLMISC::CSString stateTxt;
	stateTxt.join(_States,"\n");
	stateTxt.writeToFile(StateFileName);

	// execute the end_state script
	CScriptManager::getInstance()->runScript("end_"+stateName);

	return true;
}

void CStateManager::serviceUp(const NLMISC::CSString& serviceName,NLNET::TServiceId serviceId)
{
	// for each active state
	for (uint32 i=0;i<_States.size();++i)
	{
		// if there's a script for this service then execute it
		CScriptManager::getInstance()->runScript("serviceUp_"+_States[i]+"_"+serviceName);
	}
}

void CStateManager::serviceDown(const NLMISC::CSString& serviceName,NLNET::TServiceId serviceId)
{
	// for each active state
	for (uint32 i=0;i<_States.size();++i)
	{
		// if there's a script for this service then execute it
		CScriptManager::getInstance()->runScript("serviceDown_"+_States[i]+"_"+serviceName);
	}
}


void CStateManager::display() const
{
	if (_States.empty())
	{
		nldebug("SS No active states");
		return;
	}

	nldebug("SS Active states:");

	for (uint32 i=0;i<_States.size();++i)
	{
		nldebug("SS \t%s",_States[i].c_str());
	}
}

