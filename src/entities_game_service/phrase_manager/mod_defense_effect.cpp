/** \file mod_defense_effect.cpp
 * <File description>
 *
 * $Id: mod_defense_effect.cpp,v 1.6 2007/06/12 12:45:07 coutelas Exp $
 */



#include "stdpch.h"
// net
#include "nel/net/message.h"
//
#include "mod_defense_effect.h"
#include "player_manager/character.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"
#include "phrase_manager/phrase_utilities_functions.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

extern CPlayerManager PlayerManager;


//--------------------------------------------------------------
//		CModDefenseEffect::update()
//--------------------------------------------------------------
bool CModDefenseEffect::update(CTimerEvent * event, bool applyEffect)
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
	
	switch( _Family )
	{
		case EFFECT_FAMILIES::PowerModDodgeSkill:
			player->incDodgeModifier( (sint32)(_Modifier1 + _Modifier2) );
			player->dodgeSuccessModifier( (sint32)(_Modifier1 + _Modifier2) );
			break;
		case EFFECT_FAMILIES::PowerModParrySkill:
			player->incParryModifier( (sint32)(_Modifier1 + _Modifier2) );
			player->parrySuccessModifier( (sint32)(_Modifier1 + _Modifier2) );
			break;
		case EFFECT_FAMILIES::PowerModDefenseSkill:
			player->incDodgeModifier( (sint32)(_Modifier1 + _Modifier2) );
			player->incParryModifier( (sint32)(_Modifier1 + _Modifier2) );
			player->dodgeSuccessModifier( (sint32)(_Modifier1 + _Modifier2) );
			player->parrySuccessModifier( (sint32)(_Modifier1 + _Modifier2) );
			break;
		default:
			break;
	}
	
	return false;
} // update //

//--------------------------------------------------------------
//		CModDefenseEffect::removed()
//--------------------------------------------------------------
void CModDefenseEffect::removed()
{
	// reset modifier to it's old value
	CCharacter *player = PlayerManager.getChar(_TargetRowId);
	if (!player)
	{
		nlwarning("Cannot find target entity %s", _TargetRowId.toString().c_str());
		return;
	}
	
	switch( _Family )
	{
		case EFFECT_FAMILIES::PowerModDodgeSkill:
			player->incDodgeModifier( -(sint32)(_Modifier1 + _Modifier2) );
			player->dodgeSuccessModifier( 0 );
			break;
		case EFFECT_FAMILIES::PowerModParrySkill:
			player->incParryModifier( -(sint32)(_Modifier1 + _Modifier2) );
			player->parrySuccessModifier( 0 );
			break;
		case EFFECT_FAMILIES::PowerModDefenseSkill:
			player->incDodgeModifier( -(sint32)(_Modifier1 + _Modifier2) );
			player->incParryModifier( -(sint32)(_Modifier1 + _Modifier2) );
			player->dodgeSuccessModifier( 0 );
			player->parrySuccessModifier( 0 );
			break;
		default:
			break;
	}
}


//--------------------------------------------------------------
//		activate
//--------------------------------------------------------------
void CModDefenseEffect::activate()
{
	CCharacter *actor = PlayerManager.getChar(_CreatorEntityId);
	if (!actor)
	{
		nlwarning("<CModDefenseEffect::activate> Cannot find actor entity or not a player");
		return;
	}
	
	CModDefenseEffect *effect = new CModDefenseEffect(actor->getEntityRowId(), 
		getEndDate()+CTickEventHandler::getGameCycle(), 
		_Family,
		_DefenseMode,
		_Modifier1,
		_Modifier2);
	
	if (!effect)
	{
		nlwarning("<CModDefenseEffect::activate> Failed to allocate new CModDefenseEffect");
		return;
	}
	actor->addSabrinaEffect(effect);
}

//-----------------------------------------------------------------------------
// Persistent data for CModDefenseEffect
//-----------------------------------------------------------------------------

#define PERSISTENT_TOKEN_FAMILY RyzomTokenFamily
#define PERSISTENT_CLASS CModDefenseEffect

#define PERSISTENT_DATA\
	STRUCT2(STimedEffect,					CSTimedEffect::store(pdr),						CSTimedEffect::apply(pdr))\
	PROP2(_CreatorEntityId,		CEntityId,	TheDataset.getEntityId(getCreatorRowId()),		_CreatorEntityId = val)\
	PROP2(_TargetDisableTime,	TGameCycle,	_TargetDisableTime>CTickEventHandler::getGameCycle()?_TargetDisableTime-CTickEventHandler::getGameCycle():0,	_TargetDisableTime=val)\
	PROP(std::string,_DefenseMode)\
	PROP(float,_Modifier1)\
	PROP(float,_Modifier2)\

#pragma message( PERSISTENT_GENERATION_MESSAGE )
#include "game_share/persistent_data_template.h"
