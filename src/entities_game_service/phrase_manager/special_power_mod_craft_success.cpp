/** \file special_power_mod_craft_success.cpp
 * <File description>
 *
 * $Id: special_power_mod_craft_success.cpp,v 1.2 2007/06/12 12:45:07 coutelas Exp $
 */




#include "stdpch.h"
// net
#include "nel/net/message.h"
// misc
#include "nel/misc/bit_mem_stream.h"
//
#include "server_share/msg_ai_service.h"
//
#include "special_power_mod_craft_success.h"
#include "phrase_manager/phrase_utilities_functions.h"
#include "special_power_phrase.h"
#include "player_manager/player_manager.h"
#include "player_manager/character.h"
#include "player_manager/player.h"
#include "mod_craft_success_effect.h"


using namespace std;
using namespace NLMISC;
using namespace NLNET;

extern CPlayerManager PlayerManager;


//--------------------------------------------------------------
//					apply()  
//--------------------------------------------------------------
void CSpecialPowerModCraftSuccess::apply()
{
	if (!_Phrase)
		return;

	CCharacter *actor = PlayerManager.getChar(_ActorRowId);
	if (!actor)
	{
		nlwarning("<CSpecialPowerModCraftSuccess::apply> Cannot find actor entity or not a player");
		return;
	}

	// disable power
	actor->forbidPower(_PowerType, _Phrase->getConsumableFamilyId(), CTickEventHandler::getGameCycle() + _DisablePowerTime);

	const TGameCycle endDate = _Duration + CTickEventHandler::getGameCycle();
	
	// create effect and apply it on target
	CModCraftSuccessEffect *effect = new CModCraftSuccessEffect(_ActorRowId, 
													endDate, 
													EFFECT_FAMILIES::PowerModCraftSkill,
													_Modifier1,
													_Modifier2);
	if (!effect)
	{
		nlwarning("<CSpecialPowerModCraftSuccess::apply> Failed to allocate new CModCraftSuccessEffect");
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
