/** \file mod_forage_success_effect.cpp
 * <File description>
 *
 * $Id: mod_forage_success_effect.cpp,v 1.2 2007/06/12 12:45:07 coutelas Exp $
 */



#include "stdpch.h"
// net
#include "nel/net/message.h"
//
#include "mod_forage_success_effect.h"
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
bool CModForageSuccessEffect::update(CTimerEvent * event, bool applyEffect)
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
	
	player->forageSuccessModifier( ECOSYSTEM::stringToEcosystem(_Ecosystem), (sint32)(_Modifier1 + _Modifier2) );
		
	return false;
} // update //

//--------------------------------------------------------------
//		removed
//--------------------------------------------------------------
void CModForageSuccessEffect::removed()
{
	// reset modifier to it's old value
	CCharacter *player = PlayerManager.getChar(_TargetRowId);
	if (!player)
	{
		nlwarning("Cannot find target entity %s", _TargetRowId.toString().c_str());
		return;
	}
	
	player->forageSuccessModifier( ECOSYSTEM::stringToEcosystem(_Ecosystem), 0 );
}


//--------------------------------------------------------------
//		activate
//--------------------------------------------------------------
void CModForageSuccessEffect::activate()
{
	CCharacter *actor = PlayerManager.getChar(_CreatorEntityId);
	if (!actor)
	{
		nlwarning("<CModForageSuccessEffect::activate> Cannot find actor entity or not a player");
		return;
	}

	ECOSYSTEM::EECosystem eco = ECOSYSTEM::stringToEcosystem(_Ecosystem);
	EFFECT_FAMILIES::TEffectFamily effectFamily = EFFECT_FAMILIES::Unknown;

	CModForageSuccessEffect *effect = new CModForageSuccessEffect(actor->getEntityRowId(), 
		getEndDate()+CTickEventHandler::getGameCycle(),
		_Family,
		_Ecosystem,
		_Modifier1,
		_Modifier2);
	
	if (!effect)
	{
		nlwarning("<CModForageSuccessEffect::activate> Failed to allocate new CModForageSuccessEffect");
		return;
	}
	actor->addSabrinaEffect(effect);
}


//-----------------------------------------------------------------------------
// Persistent data for CModForageSuccessEffect
//-----------------------------------------------------------------------------

#define PERSISTENT_TOKEN_FAMILY RyzomTokenFamily
#define PERSISTENT_CLASS CModForageSuccessEffect

#define PERSISTENT_DATA\
	STRUCT2(STimedEffect,					CSTimedEffect::store(pdr),						CSTimedEffect::apply(pdr))\
	PROP2(_CreatorEntityId,		CEntityId,	TheDataset.getEntityId(getCreatorRowId()),		_CreatorEntityId = val)\
	PROP2(_TargetDisableTime,	TGameCycle,	_TargetDisableTime>CTickEventHandler::getGameCycle()?_TargetDisableTime-CTickEventHandler::getGameCycle():0,	_TargetDisableTime=val)\
	PROP(std::string,_Ecosystem)\
	PROP(float,_Modifier1)\
	PROP(float,_Modifier2)\

#pragma message( PERSISTENT_GENERATION_MESSAGE )
#include "game_share/persistent_data_template.h"

