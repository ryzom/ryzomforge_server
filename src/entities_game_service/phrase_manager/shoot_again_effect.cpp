/** \file shoot_again_effect.cpp
 * <File description>
 *
 * $Id: shoot_again_effect.cpp,v 1.1 2005/10/31 15:09:46 vuarand Exp $
 */



#include "stdpch.h"
// net
#include "nel/net/message.h"
//
#include "nel/misc/string_conversion.h"

#include "shoot_again_effect.h"
#include "phrase_manager/phrase_utilities_functions.h"

#include "entity_manager/entity_base.h"
#include "player_manager/character.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

extern CPlayerManager PlayerManager;


//----------------------------------------------------------------------------

bool CShootAgainEffect::update(CTimerEvent* event, bool applyEffect)
{
	
	// if needed check if caster is dead
	const CEntityBase *caster = CEntityBaseManager::getEntityBasePtr(_CreatorRowId);
	if ( !caster || caster->isDead())
	{
		_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
		return true;
	}
	
	CEntityBase	*targetEntity = CEntityBaseManager::getEntityBasePtr(_TargetRowId);
	if (targetEntity == NULL)
	{
		_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
		return true;
	}
	
	// set timer next event
	_UpdateTimer.setRemaining(/*_CycleLength*/20, event);
	
	return false;
}

//----------------------------------------------------------------------------

void CShootAgainEffect::removed()
{
	CEntityBase	*targetEntity = CEntityBaseManager::getEntityBasePtr(_TargetRowId);
	if (targetEntity == NULL)
	{
		return;
	}

	// if entity is dead, do not send messages
	if (targetEntity->isDead())
		return;

	DEBUGLOG("EFFECT: Shoot again effect ends on entity %s", targetEntity->getId().toString().c_str());
}

NLMISC::CSheetId CShootAgainEffect::getAssociatedSheetId() const
{
	return NLMISC::CSheetId("shoot_again.sbrick");
}
