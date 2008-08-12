/** \file combat_action.cpp
 * <File description>
 *
 * $Id: combat_action.cpp,v 1.5 2004/12/24 13:02:39 boucher Exp $
 */



#include "stdpch.h"
#include "combat_action.h"

NL_INSTANCE_COUNTER_IMPL(CCombatAction);
NL_INSTANCE_COUNTER_IMPL(CCombatAIActionFactory);

CCombatAction * CCombatAIActionFactory::buildAiAction(const CStaticAiAction *aiAction, CCombatPhrase * phrase )
{
#ifdef NL_DEBUG
	nlassert(aiAction);
	nlassert(phrase);
#endif
	const AI_ACTION::TAiActionType actionType = aiAction->getType();
	if (actionType != AI_ACTION::Melee && actionType != AI_ACTION::Range)
	{
		return false;
	}
	
	AI_ACTION::TAiEffectType effectType = aiAction->getData().Combat.EffectFamily;
	
	//get appropriate factory
	for ( uint i = 0; i < Factories->size(); i++ )
	{
		if ( (*Factories)[i].first == effectType )
		{
			return (*Factories)[i].second->build(aiAction,phrase);
		}
	}
	nlwarning( "<CCombatActionFactory buildAction> the AIEffect type %s has no corresponding combat action class", AI_ACTION::toString(effectType).c_str() );
	return NULL;
}
