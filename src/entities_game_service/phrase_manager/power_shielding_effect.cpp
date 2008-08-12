/** \file power_shielding_effect.cpp
 * <File description>
 *
 * $Id: power_shielding_effect.cpp,v 1.12 2006/10/09 15:25:30 saffray Exp $
 */



#include "stdpch.h"
// net
#include "nel/net/message.h"
//
#include "power_shielding_effect.h"
#include "player_manager/player.h"
#include "phrase_manager/phrase_utilities_functions.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

//--------------------------------------------------------------
//		CShieldingEffect::removed()
//--------------------------------------------------------------
void CShieldingEffect::removed()
{
	CEntityId creatorId;
	CEntityId targetId;	

	if (TheDataset.isAccessible(_CreatorRowId))
		creatorId = TheDataset.getEntityId(_CreatorRowId);

	if (TheDataset.isAccessible(_TargetRowId))
		targetId = TheDataset.getEntityId(_TargetRowId);

	// returns if target already dead
	CEntityBase *target = CEntityBaseManager::getEntityBasePtr(targetId);
	if (!target || target->isDead())
		return;
	
	// send messages
	SM_STATIC_PARAMS_1(params, STRING_MANAGER::power_type);
	params[0].Type = STRING_MANAGER::power_type;
	params[0].Enum = POWERS::Shielding;

	// for actor
	if (creatorId.getType() == RYZOMID::player)
	{		
		PHRASE_UTILITIES::sendDynamicSystemMessage(TheDataset.getDataSetRow(creatorId), "POWER_EFFECT_ENDS", params);
	}
	
	// for target
	if (targetId.getType() == RYZOMID::player)
	{
		PHRASE_UTILITIES::sendDynamicSystemMessage(TheDataset.getDataSetRow(targetId), "POWER_EFFECT_ENDS", params);
	}
	
	// for spectators : nothing to send (?)
/*	CEntityId senderId;
	if (creatorId.getType() == RYZOMID::player || creatorId.getType() == RYZOMID::npc)
	{
		senderId = creatorId;
	}
	else if (targetId.getType() == RYZOMID::player || targetId.getType() == RYZOMID::npc)
	{
		senderId = targetId;
	}
	
	if (senderId != CEntityId::Unknown)
	{
		vector<CEntityId> excluded;
		excluded.push_back(creatorId);
		excluded.push_back(targetId);
		PHRASE_UTILITIES::sendDynamicGroupSystemMessage(senderId, excluded, "POWER_EFFECT_ENDS", params);
	}
*/
} // removed //

//--------------------------------------------------------------
void CShieldingEffect::activate()
{
	CCharacter *actor = PlayerManager.getChar(_CreatorEntityId);
	if (!actor)
	{
		nlwarning("<CShieldingEffect::activate> Cannot find actor entity or not a player");
		return;
	}

	CCharacter *target = PlayerManager.getChar(_TargetEntityId);
	if (!target)
	{
		nlwarning("<CShieldingEffect::activate> Cannot find actor entity or not a player");
		return;
	}


	// create effect and apply it on target
	CShieldingEffect *effect = new CShieldingEffect(actor->getEntityRowId(), target->getEntityRowId(), getEndDate()+CTickEventHandler::getGameCycle(), 0/*power*/);
	if (!effect)
	{
		nlwarning("<CShieldingEffect::activate> Failed to allocate new CShieldingEffect");
		return;
	}
	
	effect->setNoShieldProtection( _NoShieldFactor, _NoShieldMaxProtection );
	effect->setBucklerProtection( _BucklerFactor, _BucklerMaxProtection );
	effect->setShieldProtection( _ShieldFactor, _ShieldMaxProtection );
	
	actor->addSabrinaEffect(effect);
}


//-----------------------------------------------------------------------------
// Persistent data for CModMagicProtectionEffect
//-----------------------------------------------------------------------------

#define PERSISTENT_TOKEN_FAMILY RyzomTokenFamily
#define PERSISTENT_CLASS CShieldingEffect

#define PERSISTENT_DATA\
	STRUCT2(STimedEffect,					CSTimedEffect::store(pdr),						CSTimedEffect::apply(pdr))\
	PROP2(_CreatorEntityId,		CEntityId,	TheDataset.getEntityId(getCreatorRowId()),		_CreatorEntityId = val)\
	PROP2(_TargetEntityId,		CEntityId,	TheDataset.getEntityId(getTargetRowId()),		_TargetEntityId = val)\
	PROP(float,_NoShieldFactor)\
	PROP(float,_BucklerFactor)\
	PROP(float,_ShieldFactor)\
	PROP(uint16,_NoShieldMaxProtection)\
	PROP(uint16,_BucklerMaxProtection)\
	PROP(uint16,_ShieldMaxProtection)\
	
#pragma message( PERSISTENT_GENERATION_MESSAGE )
#include "game_share/persistent_data_template.h"
