/** \file special_power_speeding_up.cpp
 * <File description>
 *
 * $Id: special_power_speeding_up.cpp,v 1.11 2006/10/09 15:25:30 saffray Exp $
 */




#include "stdpch.h"
// net
#include "nel/net/message.h"
// misc
#include "nel/misc/bit_mem_stream.h"
//
#include "game_share/msg_ai_service.h"
//
#include "special_power_speeding_up.h"
#include "phrase_manager/phrase_utilities_functions.h"
#include "special_power_phrase.h"
#include "player_manager/player_manager.h"
#include "player_manager/character.h"
#include "player_manager/player.h"
#include "change_move_speed_effect.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

extern CPlayerManager PlayerManager;


//--------------------------------------------------------------
//					apply()  
//--------------------------------------------------------------
void CSpecialPowerSpeedingUp::apply()
{
	NL_ALLOC_CONTEXT(SPSUAPY);
	if (!_Phrase)
		return;

	CCharacter *actor = PlayerManager.getChar(_ActorRowId);
	if (!actor)
	{
		nlwarning("<CSpecialPowerSpeedingUp::apply> Cannot find actor entity or not a player");
		return;
	}

	// disable power
	actor->forbidPower(_PowerType, _Phrase->getConsumableFamilyId(), CTickEventHandler::getGameCycle() + _DisablePowerTime + _Duration);

	const TGameCycle endDate = _Duration + CTickEventHandler::getGameCycle();
	
	// create effect and apply it on target
	CChangeMoveSpeedEffect *effect = new CChangeMoveSpeedEffect(_ActorRowId, _ActorRowId, EFFECT_FAMILIES::PowerSpeedingUp, _SpeedMod,  endDate, actor);
	if (!effect)
	{
		nlwarning("<CSpecialPowerSpeedingUp::apply> Failed to allocate new CChangeMoveSpeedEffect");
		return;
	}

	actor->addSabrinaEffect(effect);

	// send messages
	SM_STATIC_PARAMS_1(params, STRING_MANAGER::power_type);
//	TVectorParamCheck params;
	// for actor
	if (actor->getId().getType() == RYZOMID::player)
	{
		params[0].Enum = _PowerType;
		PHRASE_UTILITIES::sendDynamicSystemMessage(_ActorRowId, "POWER_USE", params);
	}
} // apply //
