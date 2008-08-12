/** \file mod_craft_success_effect.cpp
 * <File description>
 *
 * $Id: mod_craft_success_effect.cpp,v 1.2 2007/06/12 12:45:07 coutelas Exp $
 */



#include "stdpch.h"
// net
#include "nel/net/message.h"
//
#include "mod_craft_success_effect.h"
#include "player_manager/character.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"
#include "phrase_manager/phrase_utilities_functions.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

extern CPlayerManager PlayerManager;


//--------------------------------------------------------------
//		update
//--------------------------------------------------------------
bool CModCraftSuccessEffect::update(CTimerEvent * event, bool applyEffect)
{
	NL_ALLOC_CONTEXT(RAE_UPD);
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

	player->craftSuccessModifier( (sint32)(_Modifier1 + _Modifier2) );
	
	return false;
} // update //

//--------------------------------------------------------------
//		removed
//--------------------------------------------------------------
void CModCraftSuccessEffect::removed()
{
	// reset modifier to it's old value
	CCharacter *player = PlayerManager.getChar(_TargetRowId);
	if (!player)
	{
		nlwarning("Cannot find target entity %s", _TargetRowId.toString().c_str());
		return;
	}

	player->craftSuccessModifier( 0 );
}


//--------------------------------------------------------------
//		activate
//--------------------------------------------------------------
void CModCraftSuccessEffect::activate()
{
	CCharacter *actor = PlayerManager.getChar(_CreatorEntityId);
	if (!actor)
	{
		nlwarning("<CModCraftSuccessEffect::activate> Cannot find actor entity or not a player");
		return;
	}
	
	CModCraftSuccessEffect *effect = new CModCraftSuccessEffect(actor->getEntityRowId(), 
		getEndDate()+CTickEventHandler::getGameCycle(), 
		EFFECT_FAMILIES::PowerModCraftSkill,
		_Modifier1,
		_Modifier2);
	
	if (!effect)
	{
		nlwarning("<CModCraftSuccessEffect::activate> Failed to allocate new CModCraftSuccessEffect");
		return;
	}
	actor->addSabrinaEffect(effect);
}

//-----------------------------------------------------------------------------
// Persistent data for CModCraftSuccessEffect
//-----------------------------------------------------------------------------

#define PERSISTENT_TOKEN_FAMILY RyzomTokenFamily
#define PERSISTENT_CLASS CModCraftSuccessEffect

#define PERSISTENT_DATA\
	STRUCT2(STimedEffect,					CSTimedEffect::store(pdr),						CSTimedEffect::apply(pdr))\
	PROP2(_CreatorEntityId,		CEntityId,	TheDataset.getEntityId(getCreatorRowId()),		_CreatorEntityId = val)\
	PROP2(_TargetDisableTime,	TGameCycle,	_TargetDisableTime>CTickEventHandler::getGameCycle()?_TargetDisableTime-CTickEventHandler::getGameCycle():0,	_TargetDisableTime=val)\
	PROP(float,_Modifier1)\
	PROP(float,_Modifier2)\

#pragma message( PERSISTENT_GENERATION_MESSAGE )
#include "game_share/persistent_data_template.h"

