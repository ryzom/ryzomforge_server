/** \file mod_magic_protection_effet.cpp
 * Magic protection modify effect
 *
 * $Id: mod_magic_protection_effet.cpp,v 1.2 2006/10/09 15:25:30 saffray Exp $
 */



#include "stdpch.h"
// net
#include "nel/net/message.h"
//
#include "mod_magic_protection_effet.h"
#include "player_manager/character.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"
#include "phrase_manager/phrase_utilities_functions.h"

#include <string>

using namespace std;
using namespace NLMISC;
using namespace NLNET;

extern CPlayerManager PlayerManager;

//--------------------------------------------------------------
bool CModMagicProtectionEffect::update(CTimerEvent * event, bool applyEffect)
{
	NL_ALLOC_CONTEXT(MMP_UPD);
	if (!TheDataset.isAccessible(_TargetRowId))
	{
		_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
		return true;
	}

	CCharacter *player = PlayerManager.getChar(_TargetRowId);
	if (!player)
	{
		_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
		return true;
	}
	player->setUnclampedMagicProtection( _AffectedProtection, player->getUnclampedMagicProtection(_AffectedProtection) + _Modifier1 + _Modifier2 );
	return false;
} // update //

//--------------------------------------------------------------
void CModMagicProtectionEffect::removed()
{
	// reset modifier to it's old value
	CCharacter *player = PlayerManager.getChar(_TargetRowId);
	if (!player)
	{
		nlwarning("Cannot find target entity %s", _TargetRowId.toString().c_str());
		return;
	}
	player->setUnclampedMagicProtection( _AffectedProtection, player->getUnclampedMagicProtection(_AffectedProtection) - _Modifier1 - _Modifier2 );
}

//--------------------------------------------------------------
void CModMagicProtectionEffect::activate()
{
	CCharacter *actor = PlayerManager.getChar(_CreatorEntityId);
	if (!actor)
	{
		nlwarning("<CSpecialPowerModMagicProtection::activate> Cannot find actor entity or not a player");
		return;
	}

	CModMagicProtectionEffect *effect = new CModMagicProtectionEffect(actor->getEntityRowId(), 
		getEndDate()+CTickEventHandler::getGameCycle(), 
		EFFECT_FAMILIES::PowerModMagicProtection,
		_AffectedProtection,
		(float)_Modifier1,
		(float)_Modifier2);

	if (!effect)
	{
		nlwarning("<CModMagicProtectionEffect::activate> Failed to allocate new CModMagicProtectionEffect");
		return;
	}
	actor->addSabrinaEffect(effect);
}

//-----------------------------------------------------------------------------
// Persistent data for CModMagicProtectionEffect
//-----------------------------------------------------------------------------

#define PERSISTENT_TOKEN_FAMILY RyzomTokenFamily
#define PERSISTENT_CLASS CModMagicProtectionEffect

#define PERSISTENT_DATA\
	STRUCT2(STimedEffect,					CSTimedEffect::store(pdr),						CSTimedEffect::apply(pdr))\
	PROP2(_CreatorEntityId,		CEntityId,	TheDataset.getEntityId(getCreatorRowId()),		_CreatorEntityId = val)\
	PROP2(_TargetDisableTime,	TGameCycle,	_TargetDisableTime>CTickEventHandler::getGameCycle()?_TargetDisableTime-CTickEventHandler::getGameCycle():0,	_TargetDisableTime=val)\
	PROP2(_AffectedProtection,	string,		PROTECTION_TYPE::toString(_AffectedProtection),	_AffectedProtection=PROTECTION_TYPE::fromString(val))\
	PROP(sint32,_Modifier1)\
	PROP(sint32,_Modifier2)\

#pragma message( PERSISTENT_GENERATION_MESSAGE )
#include "game_share/persistent_data_template.h"
