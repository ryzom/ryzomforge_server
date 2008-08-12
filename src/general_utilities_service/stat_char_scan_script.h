/** \file stats_char_scan_script.h
 *
 * Part of STAT Module for GUS (general utilities service)
 *
 * $Id: stat_char_scan_script.h,v 1.2 2007/05/09 15:33:10 boucher Exp $
 */

#ifndef STAT_CHAR_SCAN_SCRIPT_H
#define STAT_CHAR_SCAN_SCRIPT_H

//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

#include "nel/misc/smart_ptr.h"
#include "stat_character_scan_job.h"


//-------------------------------------------------------------------------------------------------
// forward class declarations
//-------------------------------------------------------------------------------------------------

class CCharScanScript;					// an object that represents a script (one or more cumulated files)
class CCharScanScriptFile;				// an object that represents a script file
class ICharScanScriptCommand;			// virtual base class for objects that represents commands that can be used in script files
class CCharScanScriptCommandRegistry;	// singleton registry for ICharScanScriptCommand objects
template <class C> class CCharScanScriptCommandRegisterer; // template class used to register script commands in the registry


//-------------------------------------------------------------------------------------------------
// class CCharScanScript
//-------------------------------------------------------------------------------------------------

class CCharScanScript: public NLMISC::CRefCount
{
public:
	// public interface
	CCharScanScript();
	bool addScriptFile(const std::string& fileName);
	bool applyToJob(CCharacterScanJob& job);

private:
	// prohibit implicit copy
	CCharScanScript(const CCharScanScript&);

private:
	// private data
	std::vector<CCharScanScriptFile> _ScriptFiles;
};


//-------------------------------------------------------------------------------------------------
// class CCharScanScriptFile
//-------------------------------------------------------------------------------------------------

class CCharScanScriptFile: public NLMISC::CRefCount
{
public:
	// public interface
	bool parseFile(const std::string& fileName,	CCharScanScript* container=NULL);
	bool applyToJob(CCharacterScanJob& job);

	const std::string& getFileName() const;
	const std::string& getDescription() const;
	std::string getOutputPath() const;

	bool writeToFile(const std::string& fileName);
	void display() const;
	bool deleteLine(uint32 idx);

public:
	// interface for script commands
	bool setOutputPath(const std::string& path);
	bool setOutputName(const std::string& fileNameRoot);
	bool addFilter(const std::string& rawArgs);
	bool addInfoExtractor(const std::string& rawArgs);
	bool addFileListBuilder(const std::string& rawArgs);
	bool addInclude(const std::string& include);

private:
	// private data
	std::string _FileName;
	std::string _OutputPath;
	std::string _OutputName;
	std::vector<std::string> _Filters;
	std::vector<std::string> _InfoExtractors;
	std::vector<std::string> _FileListBuilders;
	std::vector<std::string> _Includes;
};


//-------------------------------------------------------------------------------------------------
// class ICharScanScriptCommand
//-------------------------------------------------------------------------------------------------

class ICharScanScriptCommand: public NLMISC::CRefCount
{
public:
	virtual ~ICharScanScriptCommand() {}
	virtual const char* getName()=0;
	virtual const char* getSyntax()=0;
	virtual const char* getDescription()=0;
	virtual bool		execute(CCharScanScriptFile& scriptFile,const NLMISC::CVectorSString& args,const NLMISC::CSString& rawArgs,const NLMISC::CSString& rawCmdLine,CCharScanScript* container)=0;
};


//-------------------------------------------------------------------------------------------------
// class CCharScanScriptCommandRegistry
//-------------------------------------------------------------------------------------------------

class CCharScanScriptCommandRegistry
{
public:
	// accessor for the singleton instance
	static CCharScanScriptCommandRegistry* getInstance();

public:
	// register a script command
	void registerScriptCommand(NLMISC::CSmartPtr<ICharScanScriptCommand> scriptCommand);

	// display the set of script commands
	void displayScriptCommands(NLMISC::CLog* log=NLMISC::InfoLog);

	// execute a script command for a given script file object
	bool execute(CCharScanScriptFile& scriptFile,const NLMISC::CSString& commandLine,CCharScanScript* container);
				 
private:
	// this is a singleton so ctor is private
	CCharScanScriptCommandRegistry() {}

private:
	// singleton data
	typedef std::vector<NLMISC::CSmartPtr<ICharScanScriptCommand> > TScriptCommands;
	TScriptCommands _ScriptCommands;
};


//-------------------------------------------------------------------------------------------------
// class CCharScanScriptCommandRegisterer
//-------------------------------------------------------------------------------------------------

template <class C>
class CCharScanScriptCommandRegisterer
{
public:
	CCharScanScriptCommandRegisterer()
	{
		CCharScanScriptCommandRegistry::getInstance()->registerScriptCommand(new C);
	}
};


//-------------------------------------------------------------------------------------------------
// MACRO CHAR_SCAN_SCRIPT_COMMAND()
//-------------------------------------------------------------------------------------------------

#define CHAR_SCAN_SCRIPT_COMMAND(name,syntax,description)\
	class CCharScriptCommand_##name: public ICharScanScriptCommand\
{\
public:\
	virtual const char* getName()			{return #name;}\
	virtual const char* getSyntax()			{return syntax;}\
	virtual const char* getDescription()	{return description;}\
\
	virtual bool		execute(CCharScanScriptFile& scriptFile,const NLMISC::CVectorSString& args,const NLMISC::CSString& rawArgs,const NLMISC::CSString& rawCmdLine,CCharScanScript* container);\
};\
CCharScanScriptCommandRegisterer<CCharScriptCommand_##name> __Registerer_CCharScriptCommand_##name;\
bool CCharScriptCommand_##name::execute(CCharScanScriptFile& scriptFile,const NLMISC::CVectorSString& args,const NLMISC::CSString& rawArgs,const NLMISC::CSString& rawCmdLine,CCharScanScript* container)


//-------------------------------------------------------------------------------------------------
#endif
