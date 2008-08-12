/** \file macro_manager.h
 * <File description>
 *
 * $Id: macro_manager.h,v 1.6 2006/01/10 17:38:49 boucher Exp $
 */




#ifndef GD_MACRO_MANAGER_H
#define GD_MACRO_MANAGER_H


// Nel Misc
#include "nel/misc/types_nl.h"
#include "nel/misc/command.h"

namespace AGS_TEST
{

/**
 * Singleton, for managing the macros in a scene
 * \author Sadge
 * \author Nevrax France
 * \date 2002
 */
class CMacroManager
{
public:
	// initialisation and housekeeping for the singleton
	static void init();
	static void release();

	// methods dealing with macro recording
	static void recordMacro(const std::string &name);
	static void record(NLMISC::ICommand *command,const std::vector<std::string> &args);
	static void stopRecord()	{ _recording=false; }
	static bool recording()		{ return _recording; }

	// executing a macro
	static void execute(const std::string &name, NLMISC::CLog &log);

	// display functions
	static void listMacros(NLMISC::CLog *log = NLMISC::InfoLog);
	static void displayMacro(const std::string &name,NLMISC::CLog *log = NLMISC::InfoLog);

private:
	class CMacro
	{
	public:
		std::string _name;
		typedef struct
		{
			NLMISC::ICommand *_command;
			std::vector<std::string> _args;
		} TMacroCommand;
		std::vector<TMacroCommand> _commands;

		void record(NLMISC::ICommand *command,const std::vector<std::string> &args)
		{
			TMacroCommand newCommand;
			newCommand._command=command;
			newCommand._args=args;
			_commands.push_back(newCommand);
		}
		void execute(NLMISC::CLog &log)
		{
			std::vector<TMacroCommand>::iterator it;
			for(it=_commands.begin();it!=_commands.end();++it)
				it->_command->execute(it->_args, log, true);
		}
	};

	// forbid instantiation
	CMacroManager();
	static std::vector<CMacro> _macros;
	static bool _recording;

};


#define COMMAND_MACRO_RECORD_TEST\
	if (CMacroManager::recording()) {CMacroManager::record(this,args); return true;}


} // end of namespace AGS_TEST

#endif // GD_MACRO_MANAGER_H
/* End of macro_manager.h */
