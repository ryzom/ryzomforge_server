/** \file world_instances.h
 * Management of continent instance across the world and information
 * about theire repective ai service (if any)
 *
 * $Id: world_instances.h,v 1.12 2007/03/09 09:56:47 boucher Exp $
 */


#ifndef WORLD_INSTANCES
#define WORLD_INSTANCES

#include "server_share/msg_ai_service.h"
#include "game_share/misc_const.h"

/// Message from AIS to EGS to report available collision data
class CReportAICollisionAvailableMsgImp : public CReportAICollisionAvailableMsg
{
	// overload the callback
	virtual void callback (const std::string &name, NLNET::TServiceId id);
};

/// Message from AIS to EGS to report static continent instance
class CReportStaticAIInstanceMsgImp : public CReportStaticAIInstanceMsg
{
	// overload the callback
	virtual void callback (const std::string &name, NLNET::TServiceId id);
};

/// Message from AIS to EGS to report ai instance despawn
class CReportAIInstanceDespawnMsgImp : public CReportAIInstanceDespawnMsg
{
	// overload the callback
	virtual void callback (const std::string &name, NLNET::TServiceId id);
};


/* This class store instance informations as well as
 * AIS list with available collision information.
 * The AIS collision information is used to select the
 * AIS for spawning a new dynamic instance.
 */
class CWorldInstances
{
public:

	/// Interface for aiInstance ready callback
	struct IAIInstanceReady
	{
		virtual void onAiInstanceReady(const CReportStaticAIInstanceMsg &msg) = 0;
		virtual void onAiInstanceDown(const CReportStaticAIInstanceMsg &msg) {}; // not mandatory
	};

	/// Singleton access
	static CWorldInstances &instance();

	/// Register ai instance ready/down callback object (only one at a time)
	void registerAiInstanceReadyCallback(IAIInstanceReady *callback);

	/// Send the mirror transport class to the AIS that contains the AI instance (makes a warning if not found)
	void msgToAIInstance(uint32 instanceNumber, CMirrorTransportClass &msg);
	/// Send the message to the AIS that contains the AI instance (makes a warning if not found)
	void msgToAIInstance2(uint32 instanceNumber, NLNET::CMessage &msg);

	/// Return the AIS Id or 0 if no AIS is currently online (no warning if not found)
	NLNET::TServiceId getAISId(uint32 instanceNumber ) const;

	/// an ais as just disconnected.
	void aiDisconnection(NLNET::TServiceId aisId);

	/// Retrieve the AIS service ID for a given instance, return false if no instance match
	bool getAIServiceIdForInstance(uint32 instanceNumber, NLNET::TServiceId &AISId);

	/// Retrieve the instance name for a given AIS service ID
	bool getAIInstanceNameFromeServiceId(NLNET::TServiceId AISID, std::string & name);

private:
	// Private constructor, enforce singleton
	CWorldInstances();
	// singleton instance pointer
	static CWorldInstances	*_Instance;

	IAIInstanceReady		*_AIReadyCallback;

	struct TInstanceInfo
	{
		/// Unique instance number.
		uint32			InstanceNumber;
		/// Name of the continent for this instance.
		std::string		ContinentName;
		/// Service ID of the ais hosting this instance.
		NLNET::TServiceId	AISId;
	};

	struct TAISInfo
	{
		/// AIS service ID
		NLNET::TServiceId			AISId;
		/// Vector of available continent collision data.
		std::vector<std::string>	AvailableCollision;
	};


	typedef std::map<uint32, TInstanceInfo>	TInstanceInfoCont;
	/// Storage for instances info
	TInstanceInfoCont		_InstanceInfos;

	typedef std::map<NLNET::TServiceId, TAISInfo>	TAISInfoCont;
	/// Storage for ais info
	TAISInfoCont			_AISInfos;

	friend class CReportAICollisionAvailableMsgImp;
	friend class CReportStaticAIInstanceMsgImp;
	friend class CReportAIInstanceDespawnMsgImp;

	void reportAICollisionAvailable (const std::string &name, NLNET::TServiceId id, CReportAICollisionAvailableMsgImp &msg);
	void reportStaticAIInstance (const std::string &name, NLNET::TServiceId id, CReportStaticAIInstanceMsgImp &msg);
	void reportAIInstanceDespawn (const std::string &name, NLNET::TServiceId id, CReportAIInstanceDespawnMsgImp &msg);

};

#endif //WORLD_INSTANCES
