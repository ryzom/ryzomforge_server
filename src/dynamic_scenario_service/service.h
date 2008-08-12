/** \file service.h
 *
 * $id$
 *
 */

#ifndef R2_SERVICE_H
#define R2_SERVICE_H

#include "nel/misc/types_nl.h"
#include "nel/net/service.h"
#include "game_share/dyn_chat.h"


namespace NLNET
{
	class IModuleSocket;
}
namespace NLMISC
{
	class CConfigFile;
	struct CEntityId;
}
namespace R2
{
class CDynamicMapService;

class CDynamicScenarioService : public NLNET::IService
{

public:
	//CDynamicScenarioService();
	//~CDynamicScenarioService();
	// Initialisation of service
	void init ();

	// Update net processing 
	bool update ();

	// Update service processing
	static void serviceUpdate();

	// Release the service
	void release ();

	void addTestClient(const std::string & clientId);

	void removeTestClient(const std::string & clientId);

	void listTestClient() const;

	void runTestClientLuaScript(const std::string & clientId, const std::string & cmd);
	

	static R2::CDynamicScenarioService & instance()  { return (CDynamicScenarioService&)*IService::getInstance(); }

	R2::CDynamicMapService & getDynamicMapService() const { return *_Dms; }
	
	void forwardToStringManagerModule (NLNET::CMessage &msgin);
	

	void forwardIncarnChat(TChanID id,TDataSetRow senderId,ucstring sentence);
	

private:
	R2::CDynamicMapService* _Dms;


};	
} //namespace R2

#endif //R2_SERVICE_H

