/** \file client_command_forwarder
 *	
 *
 * $Id: client_command_forwarder.cpp,v 1.3 2006/05/31 12:12:36 boucher Exp $
 */




#include "stdpch.h"

#include "nel/net/service.h"
#include "nel/net/module.h"
#include "nel/net/module_builder_parts.h"

#include "game_share/command_executor_itf.h"

#include "client_command_forwarder.h"



using namespace std;
using namespace NLMISC;
using namespace NLNET;
using namespace CMDEXE;



class CClientCommandForwader : public CEmptyModuleServiceBehav<CEmptyModuleCommBehav<CEmptySocketBehav <CModuleBase> > >,
	public IClientCommandForwader
{
	typedef map<std::string, TModuleProxyPtr>	TCommandExecutors;

	TCommandExecutors	_CommandExecutors;

public:

	void onModuleUp(IModuleProxy *module)
	{
		if (module->getModuleClassName() == "CommandExecutor")
		{
			TParsedCommandLine pcl;
			if (!pcl.parseParamList(module->getModuleManifest()))
				return;

			const TParsedCommandLine *serviceName = pcl.getParam("ServiceName");
			if (serviceName == NULL)
				return;

			_CommandExecutors[serviceName->ParamValue] = module;
		}
	}

	void onModuleDown(IModuleProxy *module)
	{
		if (module->getModuleClassName() == "CommandExecutor")
		{
			// remove it from the list
			TCommandExecutors::iterator first(_CommandExecutors.begin()), last(_CommandExecutors.end());
			for (; first != last; ++first)
			{
				if (first->second == module)
				{
					_CommandExecutors.erase(first);
					break;
				}
			}
		}

	}

	bool onProcessModuleMessage(IModuleProxy *sender, const CMessage &message)
	{
		nlwarning("CRingSessionManager : Unknown message '%s' received", message.getName().c_str());

		return false;
	}


	///////////////////////////////////////////////////////////////////////////////
	///////// IClientCommandForwader implementation  //////////////////////////////
	///////////////////////////////////////////////////////////////////////////////


	void sendCommand(const std::string &service, const std::string &commandName, const NLMISC::CEntityId &senderEId, bool haveTarget, const NLMISC::CEntityId &targetEId, const std::string &arg)
	{
		TCommandExecutors::iterator it(_CommandExecutors.find(service));

		if (it == _CommandExecutors.end())
			return;

		CCommandExecutorProxy cep(it->second);

		cep.sendCommand(this, commandName, senderEId, haveTarget, targetEId, arg);
	}

};

NLNET_REGISTER_MODULE_FACTORY(CClientCommandForwader, "ClientCommandForwader");

