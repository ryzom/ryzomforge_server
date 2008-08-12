/** \file service.h
 *
 * $id$
 *
 */

#ifndef R2_DYNAMIC_SCENARIO_SERVICE_H
#define R2_DYNAMIC_SCENARIO_SERVICE_H

#include "nel/misc/types_nl.h"
#include "nel/net/service.h"
#include "game_share/dyn_chat.h"
#include "r2_modules/r2_session_backup_module.h"

namespace NLNET
{
	class IModuleSocket;
	class IModule;
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

	void setR2Sbm(NLNET::IModule* module) { _R2Sbm = module; }
	
	NLNET::IModule* getR2Sbm() const { return _R2Sbm; }
	
	bool getBsUp() const { return _BsUp; }
	void setBsUp(bool up){ _BsUp = up; }
	


private:
	enum  TMode {R2Sbm, Dss, DssWithNoSu};

private:
	TMode _Mode;
	R2::CDynamicMapService* _Dms; // Null if _Mode == RESbm
	NLNET::IModule* _R2Sbm;
	bool _BsUp;
	//	

};	
} //namespace R2

#endif //R2_DYNAMIC_SCENARIO_SERVICE_H

