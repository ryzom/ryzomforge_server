/** \file damage_shield_effect.cpp
 * <File description>
 *
 * $Id: damage_shield_effect.cpp,v 1.6 2005/02/22 10:22:29 besson Exp $
 */



#include "stdpch.h"
// net
#include "nel/net/message.h"
//
#include "damage_shield_effect.h"
#include "phrase_manager/phrase_utilities_functions.h"

#include "entity_manager/entity_base.h"
#include "player_manager/character.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

extern CPlayerManager PlayerManager;

//--------------------------------------------------------------
//		CDamageShieldEffect::removed()
//--------------------------------------------------------------
void CDamageShieldEffect::removed()
{
	sendEffectEndMessages();
} // removed //

