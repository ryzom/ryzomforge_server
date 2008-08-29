/** \file command_executor.cpp
 *	
 *
 * $Id: command_executor.cpp,v 1.3 2006/05/31 12:12:36 boucher Exp $
 */



#include "stdpch.h"

#include "nel/net/module.h"
#include "nel/net/module_builder_parts.h"

#include "command_executor_itf.h"


using namespace std;
using namespace NLMISC;
using namespace NLNET;
using namespace CMDEXE;


void commandExecutor_forcelink()
{
}


class CCommandExecutor: public CEmptyModuleServiceBehav<CEmptyModuleCommBehav<CEmptySocketBehav <CModuleBase> > >,
	public CCommandExecutorSkel
{
public:

	CCommandExecutor()
	{
		CCommandExecutorSkel::init(this);
	}

//	bool onProcessModuleMessage(IModuleProxy *sender, const CMessage &message)
//	{
//		if (CCommandExecutorSkel::onDispatchMessage(sender, message))
//			return true;
//
//		nlwarning("CCommandExecutor : Unknown message '%s' received", message.getName().c_str());
//
//		return false;
//	}

	std::string buildModuleManifest() const
	{
		string ret("ServiceName=");
		ret += IService::getInstance()->getServiceShortName();

		return ret;
	}


	///////////////////////////////////////////////////////////////////////////////
	///////// CCommandExecutorSkel implementation  ////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	void sendCommand(NLNET::IModuleProxy *sender, const std::string &commandName, const NLMISC::CEntityId &senderEId, bool haveTarget, const NLMISC::CEntityId &targetEId, const std::string &arg)
	{
		// rebuild the command line
		string cmdLine = commandName+" "+senderEId.toString();
		if (haveTarget)
		{
			cmdLine += " "+targetEId.toString();
		}
		
		cmdLine += " " + arg;
		// execute the command
		NLMISC::CCommandRegistry::getInstance().execute(cmdLine, InfoLog());
 	}

};

NLNET_REGISTER_MODULE_FACTORY(CCommandExecutor, "CommandExecutor");


