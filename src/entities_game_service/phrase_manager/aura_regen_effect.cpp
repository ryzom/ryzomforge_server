/** \file aura_regen_effect.cpp
 * <File description>
 *
 * $Id: aura_regen_effect.cpp,v 1.17 2005/02/22 10:22:29 besson Exp $
 */



#include "stdpch.h"
// net
#include "nel/net/message.h"
//
#include "aura_regen_effect.h"
#include "player_manager/character.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"
#include "phrase_manager/phrase_utilities_functions.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

extern CPlayerManager PlayerManager;


//--------------------------------------------------------------
//		CRegenAuraEffect::update()
//--------------------------------------------------------------
bool CRegenAuraEffect::update(CTimerEvent * event, bool applyEffect)
{
	NL_ALLOC_CONTEXT(RAE_UPD);
	if (!TheDataset.isAccessible(_TargetRowId))
	{
		_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
		return true;
	}

#ifdef NL_DEBUG
	nlassert(_AffectedScore != SCORES::unknown);
#endif
	
	CCharacter *player = PlayerManager.getChar(_TargetRowId);
	if (!player)
	{
		_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
		return true;
	}
		
	player->getScores()._PhysicalScores[_AffectedScore].RegenerateModifier += _RegenModifier;
	
	// now only one update is needed, but the end methos must reset the modifier !
	// must update this every ticks NO !!!!
	//_UpdateTimer.setRemaining(1, event);

	return false;
} // update //

//--------------------------------------------------------------
//		CAuraRootEffect::removed()
//--------------------------------------------------------------
void CRegenAuraEffect::removed()
{
	// reset modifier to it's old value
	CCharacter *player = PlayerManager.getChar(_TargetRowId);
	if (!player)
	{
		nlwarning("Cannot find target entity %s", _TargetRowId.toString().c_str());
		return;
	}
	
	player->getScores()._PhysicalScores[_AffectedScore].RegenerateModifier -= _RegenModifier;

	// call base class method for aura removal management
	CAuraBaseEffect::removed();
}


CAuraEffectTFactory<CRegenAuraEffect> *CLifeAuraEffectFactoryInstance = new CAuraEffectTFactory<CRegenAuraEffect>(POWERS::LifeAura);
CAuraEffectTFactory<CRegenAuraEffect> *CStaminaAuraEffectFactoryInstance = new CAuraEffectTFactory<CRegenAuraEffect>(POWERS::StaminaAura);
CAuraEffectTFactory<CRegenAuraEffect> *CSapAuraEffectFactoryInstance = new CAuraEffectTFactory<CRegenAuraEffect>(POWERS::SapAura);
