/** \file stun_effect.cpp
 * <File description>
 *
 * $Id: stun_effect.cpp,v 1.12 2005/02/22 10:22:29 besson Exp $
 */



#include "stdpch.h"
// net
#include "nel/net/message.h"
//
#include "stun_effect.h"
#include "phrase_manager/phrase_utilities_functions.h"
#include "phrase_manager/effect_factory.h"
#include "entity_manager/entity_base.h"
#include "entity_manager/entity_manager.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

//--------------------------------------------------------------
//		CStunEffect::update()
//--------------------------------------------------------------
bool CStunEffect::update(CTimerEvent * event, bool applyEffect)
{
	CEntityBase *stunnedEntity = CEntityBaseManager::getEntityBasePtr(_TargetRowId);
	if (!stunnedEntity) 
	{
		nlwarning("EFFECT: failed to find stunned entity %s", _TargetRowId.toString().c_str());
		return true;
	}

	if (!stunnedEntity->isStunned())
		stunnedEntity->stun();

	return false;
}

//--------------------------------------------------------------
//		CStunEffect::removed()
//--------------------------------------------------------------
void CStunEffect::removed()
{
	CEntityBase *stunnedEntity = CEntityBaseManager::getEntityBasePtr(_TargetRowId);
	if (!stunnedEntity) 
		return;

	DEBUGLOG("EFFECT: stun effect ends on entity %s", stunnedEntity->getId().toString().c_str());

	// if this is the last STUN effect on target, then wake it
	const std::vector<CSEffectPtr>& effects = stunnedEntity->getSEffects();
	for (uint i = 0 ; i < effects.size() ; ++i)
	{
		if (effects[i] && effects[i] != this && (effects[i]->getFamily() == EFFECT_FAMILIES::Stun || effects[i]->getFamily() == EFFECT_FAMILIES::CombatStun) )
		{
			DEBUGLOG("EFFECT : entity is still stunned (has another stun effect)");
			return;
		}
	}

	// wake entity
	stunnedEntity->wake();
	DEBUGLOG("EFFECT : was last stun effects on this entity, wake it");

	sendEffectEndMessages();

} // removed //


CEffectTFactory<CStunEffect> *CCombatStunEffectFactory = new CEffectTFactory<CStunEffect>(EFFECT_FAMILIES::CombatStun);
CEffectTFactory<CStunEffect> *CStunEffectFactory = new CEffectTFactory<CStunEffect>(EFFECT_FAMILIES::Stun);
