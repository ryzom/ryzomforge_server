/** \file macro_manager.cpp
 * <File description>
 *
 * $Id: macro_manager.cpp,v 1.5 2004/03/01 19:18:37 lecroart Exp $
 */



// Nel Misc
// #include "nel/misc/command.h"
// #include "nel/misc/path.h"

// Game share
//#include "game_share/sid.h"

// Local headers
#include "macro_manager.h"

using namespace NLMISC;
//using namespace NLNET;
using namespace std;


namespace AGS_TEST
{

//------------------------------------------------------------------------
// static data for CMacroManager

std::vector<CMacroManager::CMacro> CMacroManager::_macros;
bool CMacroManager::_recording=false;


//------------------------------------------------------------------------
// basic functionality for CMacroManager singleton

void CMacroManager::init()
{
}

void CMacroManager::release()
{
	_macros.clear();
}


//---------------------------------------------------------------------------------

// display functions
void CMacroManager::listMacros(NLMISC::CLog *log)
{
	log->displayNL("Macro list:");
	std::vector<CMacro>::iterator it;
	for (it=_macros.begin(); it!=_macros.end(); ++it)
	{
		log->displayNL("\t%s",(*it)._name.c_str());
	}
}

void CMacroManager::displayMacro(const std::string &name, NLMISC::CLog *log)
{
	std::vector<CMacro>::iterator it;
	for (it=_macros.begin(); it!=_macros.end(); ++it)
	{
		if ((*it)._name==name)
		{
			log->displayNL("MACRO: %s",name.c_str());
			std::vector<CMacroManager::CMacro::TMacroCommand>::iterator mit;
			for(mit=(*it)._commands.begin();mit!=(*it)._commands.end();++mit)
			{
				std::string hold;
				std::vector<std::string>::iterator ait;
				for(ait=(*mit)._args.begin();ait!=(*mit)._args.end();++ait)
					hold=hold+std::string(" ")+(*ait);
				log->displayNL("\t\t%s",hold.c_str());
			}
		}
	}
}

//---------------------------------------------------------------------------------

void CMacroManager::recordMacro(const std::string &name)
{
	// if a macro already exists by this name then delete it
	std::vector<CMacro>::iterator it;
	for (it=_macros.begin(); it!=_macros.end(); ++it)
	{
		if ((*it)._name==name)
		{
			_macros.erase(it);
			break;
		}
	}

	// create the new macro record
	CMacroManager::CMacro newMacro;
	newMacro._name=name;
	_macros.push_back(newMacro);

	// setup the recording flag
	_recording=true;
}

void CMacroManager::record(NLMISC::ICommand *command,const std::vector<std::string> &args)
{
	_macros[_macros.size()-1].record(command,args);
}


//---------------------------------------------------------------------------------

void CMacroManager::execute(const std::string &name, NLMISC::CLog &log)
{
	std::vector<CMacro>::iterator it;
	for (it=_macros.begin(); it!=_macros.end(); ++it)
		if ((*it)._name==name)
		{
			nlinfo("Executing macro: %s",name.c_str());
			(*it).execute(log);
			return;
		}
}


} // end of namespace AGS_TEST
