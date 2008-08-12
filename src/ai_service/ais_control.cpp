/** \file ais_control.cpp
 * <File description>
 *
 * $Id: ais_control.cpp,v 1.5 2006/12/06 17:22:05 boucher Exp $
 */

#include "stdpch.h"

#include "nel/net/service.h"
#include "nel/net/module.h"
#include "nel/net/module_builder_parts.h"

#include "r2_modules/r2_modules_itf.h"
#include "r2_share/r2_variables.h"

#include "ais_control.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;
using namespace R2;

class CAisControl : public CEmptyModuleServiceBehav<CEmptyModuleCommBehav<CEmptySocketBehav <CModuleBase> > >,
	public IAisControl,
	public CAisControlItfSkel
{

public:

	CAisControl()
	{
		CAisControlItfSkel::init(this);
	}

	void onModuleUp(IModuleProxy *module)
	{
		if (module->getModuleClassName() == "ServerAnimationModule")
		{
			WARN_IF(_ServerAnimationProxy != NULL, ("CAisControl::onModuleUp : receiving module for class AisSynchronisation as '%s', but already have one as '%s', replacing", module->getModuleName().c_str(), _ServerAnimationProxy->getModuleName().c_str()));
			_ServerAnimationProxy = module;
		}
		else if (module->getModuleClassName() == "CharacterControl")
		{
			WARN_IF(_CharacterControlProxy != NULL, ("CAisControl::onModuleUp : receiving module for class AisSynchronisation as '%s', but already have one as '%s', replacing", module->getModuleName().c_str(), _CharacterControlProxy->getModuleName().c_str()));
			_CharacterControlProxy = module;
		}
		
	}

	void onModuleDown(IModuleProxy *module)
	{
		if (module == _ServerAnimationProxy)
		{
			_ServerAnimationProxy = NULL;
		}
		else if (module == _CharacterControlProxy)
		{
			_CharacterControlProxy = NULL;
		}

	}

//	bool onProcessModuleMessage(IModuleProxy *sender, const CMessage &message)
//	{
//		if (CAisControlItfSkel::onDispatchMessage(sender, message))
//			return true;
//		
//		nlwarning("CAisControl : Unknown message '%s' received", message.getName().c_str());
//
//		return false;
//	}

	/*
	 * Sending messages to Server Animation
	 */


	// activate a scenario generated easter egg
	virtual void activateEasterEgg(uint32 easterEggId, TSessionId scenarioId, uint32 actId, const std::string & items, float x, float y, float z, float heading, const std::string& grpCtrl, const std::string& name, const std::string & clientSheet)
	{
		DROP_IF( !_ServerAnimationProxy, "ServerAnimation module not present", return );
		CServerAnimationItfProxy ServerAnimation( _ServerAnimationProxy );
		ServerAnimation.activateEasterEgg(this, easterEggId, scenarioId, actId, items, x, y, z, heading, grpCtrl, name, clientSheet);
	}
	
	// deactivate a scenario generated easter egg
	virtual void deactivateEasterEgg(uint32 easterEggId, TSessionId scenarioId, uint32 actId)
	{
		//DROP_IF( !_CharacterControlProxy, "CharacterControl module not present", return );
		//CharacterControlItfProxy CharacterControl( _CharacterControlProxy );
		//CharacterControl.deactivateEasterEgg(this, easterEggId, scenarioId);
		DROP_IF( !_ServerAnimationProxy, "ServerAnimation module not present", return );
		CServerAnimationItfProxy ServerAnimation( _ServerAnimationProxy );
		ServerAnimation.deactivateEasterEgg(this, easterEggId, scenarioId, actId);
	}

	virtual void dssMessage(TSessionId sessionId, const std::string& mode, const std::string& who, const std::string &msg) 
	{
		DROP_IF( !_ServerAnimationProxy, "ServerAnimation module not present", return );
		CServerAnimationItfProxy ServerAnimation( _ServerAnimationProxy );
		ServerAnimation.dssMessage(this, sessionId, mode, who, msg);
	}

	virtual void giveRewardMessage(TDataSetRow characterRowId, TDataSetRow creatureRowId,
								const std::string& rewardText,
								const std::string& rareRewardText,
								const std::string& inventoryFullText,
								const std::string& notEnoughPointsText)
	{
		DROP_IF( !_CharacterControlProxy, "_CharacterControlProxy module not present", return );
		CCharacterControlItfProxy  module( _CharacterControlProxy );
		module.giveRewardMessage(this, characterRowId, creatureRowId, 
			rewardText, rareRewardText, inventoryFullText, notEnoughPointsText);
	}

	virtual void teleportNearMessage(const NLMISC::CEntityId& entity, float x, float y, float z) 
	{

		DROP_IF( !_ServerAnimationProxy, "ServerAnimation module not present", return );
		CServerAnimationItfProxy serverAnimation( _ServerAnimationProxy );
		serverAnimation.teleportCharacter(this, entity, x, y, z);
	}

	virtual void reportNpcControl(const NLMISC::CEntityId& playerEntityId, const NLMISC::CEntityId& botEntityId)
	{
		DROP_IF( !_CharacterControlProxy, "_CharacterControlProxy module not present", return );
		CCharacterControlItfProxy  module( _CharacterControlProxy );
		module.reportNpcControl(this, playerEntityId, botEntityId);
	}

	virtual void reportStopNpcControl(const NLMISC::CEntityId& playerEntityId, const NLMISC::CEntityId& botEntityId)
	{
		DROP_IF( !_CharacterControlProxy, "_CharacterControlProxy module not present", return );
		CCharacterControlItfProxy  module( _CharacterControlProxy );
		module.reportStopNpcControl(this, playerEntityId, botEntityId);
	}

	virtual void setScenarioPoints(TSessionId sessionId, float scenarioPoints) 
	{
		DROP_IF( !_ServerAnimationProxy, "ServerAnimation module not present", return );
		CServerAnimationItfProxy ServerAnimation( _ServerAnimationProxy );
		ServerAnimation.setScenarioPoints(this, sessionId, scenarioPoints);
	}

	virtual void startScenarioTiming(TSessionId sessionId) 
	{
		DROP_IF( !_ServerAnimationProxy, "ServerAnimation module not present", return );
		CServerAnimationItfProxy ServerAnimation( _ServerAnimationProxy );
		ServerAnimation.startScenarioTiming(this, sessionId);
	}
 
	virtual void endScenarioTiming(TSessionId sessionId) 
	{
		DROP_IF( !_ServerAnimationProxy, "ServerAnimation module not present", return );
		CServerAnimationItfProxy ServerAnimation( _ServerAnimationProxy );
		ServerAnimation.endScenarioTiming(this, sessionId);
	}

private:

	// Proxy to the module to reach in the DSS
	TModuleProxyPtr			_ServerAnimationProxy;
	TModuleProxyPtr			_CharacterControlProxy;


};


NLNET_REGISTER_MODULE_FACTORY(CAisControl, "AisControl");

