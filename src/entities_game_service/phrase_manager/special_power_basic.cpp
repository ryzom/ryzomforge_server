/** \file special_power_basic.cpp
 * <File description>
 *
 * $Id: special_power_basic.cpp,v 1.10 2006/10/09 15:25:30 saffray Exp $
 */




#include "stdpch.h"
// net
#include "nel/net/message.h"
// misc
#include "nel/misc/bit_mem_stream.h"
//
#include "server_share/msg_ai_service.h"
//
#include "special_power_basic.h"

#include "phrase_manager/phrase_utilities_functions.h"
#include "special_power_phrase.h"
#include "player_manager/player_manager.h"
#include "player_manager/character.h"
#include "player_manager/player.h"

#include "phrase_manager/effect_factory.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

extern CPlayerManager PlayerManager;


//--------------------------------------------------------------
//					apply()  
//--------------------------------------------------------------
void CSpecialPowerBasic::apply()
{
	if (!_Phrase)
		return;

	CCharacter *actor = PlayerManager.getChar(_ActorRowId);
	if (!actor)
	{
		nlwarning("<CSpecialPowerBasic::apply> Cannot find actor entity or not a player");
		return;
	}

	// disable power
	actor->forbidPower(_PowerType, _Phrase->getConsumableFamilyId(), CTickEventHandler::getGameCycle() + _DisablePowerTime + _Duration);

	// create effect and apply it on actor
	const TGameCycle endDate = _Duration + CTickEventHandler::getGameCycle();
	
	CSTimedEffect *effect = IEffectFactory::buildEffect(_EffectFamily);
	if (effect)
	{
		effect->setCreatorRowId(_ActorRowId);
		effect->setFamily(_EffectFamily);
		effect->setTargetRowId(_ActorRowId);
		effect->setParamValue(_ParamValue);
		effect->setEndDate(endDate);
		
		actor->addSabrinaEffect(effect);
	}
	else
		return;

	// send messages
//	TVectorParamCheck params;
	// for actor
	if (actor->getId().getType() == RYZOMID::player)
	{
		SM_STATIC_PARAMS_1(params, STRING_MANAGER::power_type);
		params[0].Enum = _PowerType;
		PHRASE_UTILITIES::sendDynamicSystemMessage(_ActorRowId, "POWER_USE", params);
	}

	// for spectators
//	{
//		vector<CEntityId> excluded;
//		excluded.push_back(actor->getId());
//
//		params.resize(2);
//		params[0].Type = STRING_MANAGER::entity;
//		params[0].EId = actor->getId();
//		params[1].Type = STRING_MANAGER::power_type;
//		params[1].Enum = _PowerType;
//		PHRASE_UTILITIES::sendDynamicGroupSystemMessage(_ActorRowId, excluded, "POWER_USE_SPECTATORS", params);
//	}
} // apply //
