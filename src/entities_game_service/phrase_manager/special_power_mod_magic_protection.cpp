/** \file special_power_mod_magic_protection.cpp
 * <File description>
 *
 * $Id: special_power_mod_magic_protection.cpp,v 1.2 2006/10/09 15:25:30 saffray Exp $
 */




#include "stdpch.h"
// net
#include "nel/net/message.h"
// misc
#include "nel/misc/bit_mem_stream.h"
//
#include "game_share/msg_ai_service.h"
//
#include "special_power_mod_magic_protection.h"
#include "phrase_manager/phrase_utilities_functions.h"
#include "special_power_phrase.h"
#include "player_manager/player_manager.h"
#include "player_manager/character.h"
#include "player_manager/player.h"
#include "mod_magic_protection_effet.h"


using namespace std;
using namespace NLMISC;
using namespace NLNET;

extern CPlayerManager PlayerManager;


//--------------------------------------------------------------
//					apply()  
//--------------------------------------------------------------
void CSpecialPowerModMagicProtection::apply()
{
	if (!_Phrase)
		return;

	CCharacter *actor = PlayerManager.getChar(_ActorRowId);
	if (!actor)
	{
		nlwarning("<CSpecialPowerModMagicProtection::apply> Cannot find actor entity or not a player");
		return;
	}

	// disable power
	actor->forbidPower(_PowerType, _Phrase->getConsumableFamilyId(), CTickEventHandler::getGameCycle() + _DisablePowerTime + _Duration);

	const TGameCycle endDate = _Duration + CTickEventHandler::getGameCycle();
	
	PROTECTION_TYPE::TProtectionType _AffectedProtectionType = PROTECTION_TYPE::fromString(_AffectedProtection);
	if(_AffectedProtectionType == PROTECTION_TYPE::None)
	{
		nlwarning("<CSpecialPowerModMagicProtection::apply> Cannot convert protection: <%s> to a knowned <PROTECTION_TYPE::TProtectionType>", _AffectedProtection.c_str());
		return;
	}

	// create effect and apply it on target
	CModMagicProtectionEffect *effect = new CModMagicProtectionEffect(_ActorRowId, 
													endDate, 
													EFFECT_FAMILIES::PowerModMagicProtection,
													_AffectedProtectionType,
													_Modifier1,
													_Modifier2);
	if (!effect)
	{
		nlwarning("<CSpecialPowerModMagicProtection::apply> Failed to allocate new CModMagicProtectionEffect");
		return;
	}

	actor->addSabrinaEffect(effect);

	// send messages
	SM_STATIC_PARAMS_1(params, STRING_MANAGER::power_type);
	// for actor
	if (actor->getId().getType() == RYZOMID::player)
	{
		params[0].Enum = _PowerType;
		PHRASE_UTILITIES::sendDynamicSystemMessage(_ActorRowId, "POWER_USE", params);
	}
} // apply //
