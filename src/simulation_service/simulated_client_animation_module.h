#ifndef R2_CLIENT_ANIMATION_MODULE_H
#define R2_CLIENT_ANIMATION_MODULE_H

#include "nel/misc/types_nl.h"
#include "nel/net/module.h"

#include "r2_share/r2_share_itf.h"
namespace R2
{
	class CObject;

	class CSimClientAnimationModule : public NLNET::CModuleBase
	{
	public:
		CSimClientAnimationModule() { _ServerAnimationProxy = NULL; }

		void init(NLNET::IModuleSocket* clientGW);	//, CDynamicMapClient* client);

		virtual void requestTpPosition(float x, float y);
		virtual void requestDespawnEntity(const std::string& npcRtId);
		virtual void requestDespawnGrp(const std::string& groupRtId);
		void onServiceUp(const std::string &serviceName, uint16 serviceId) { }
		void onServiceDown(const std::string &serviceName, uint16 serviceId) {}

		void onModuleUp(NLNET::IModuleProxy *moduleProxy);
		void onModuleDown(NLNET::IModuleProxy *moduleProxy);
		void onModuleUpdate() {}

		void onApplicationExit() {}
		
		void onProcessModuleMessage(NLNET::IModuleProxy *senderModuleProxy, const NLNET::CMessage &message);
		void onModuleSecurityChange(NLNET::IModuleProxy *moduleProxy);
		void onModuleSocketEvent(NLNET::IModuleSocket *moduleSocket, TModuleSocketEvent eventType) {}

		virtual void requestTalkAs(const std::string& npcname);
		virtual void requestStopTalkAs();
		virtual void requestStringTable();
		virtual void requestSetStringValue(std::string& id,std::string& value );
		virtual void requestStringValue(std::string& localId );
		virtual void requestIdList();
		bool requestSetPioneerRight(const TPioneerRight& right);
		// start an act (if an act is running start stop the previous one)
		void requestStartAct(uint32 actId);
		void requestSetWeather(uint16 weatherValue);
		void requestStopAct();

		bool isImmediateDispatchingSupported() const { return false; }

	private:		
		NLNET::TModuleProxyPtr _ServerAnimationProxy;
	};

} // namespace R2

#endif //R2_CLIENT_ANIMATION_MODULE_H
