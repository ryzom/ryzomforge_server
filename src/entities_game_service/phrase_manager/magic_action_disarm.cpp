/** \file magic_action_disarm.cpp
 * <File description>
 *
 * $Id: magic_action_disarm.cpp,v 1.15 2005/03/16 16:01:38 lancon Exp $
 */

 

#include "stdpch.h"
#include "magic_action_disarm.h"
#include "phrase_manager/magic_phrase.h"
#include "phrase_manager/effect_factory.h"
#include "phrase_manager/phrase_manager.h"
#include "player_manager/character.h"
#include "entity_structure/statistic.h"
#include "entity_manager/entity_manager.h"
#include "server_share/ai_event_report.h"

using namespace NLMISC;
using namespace std;


//--------------------------------------------------------------
//					initFromAiAction  
//--------------------------------------------------------------
bool CMagicActionDisarm::initFromAiAction( const CStaticAiAction *aiAction, CMagicPhrase *phrase )
{
#ifdef NL_DEBUG
	nlassert(phrase);
	nlassert(aiAction);
#endif
	
	if (aiAction->getType() != AI_ACTION::EffectSpell )
		return false;
			
	return true;
} // initFromAiAction //

//--------------------------------------------------------------
//					launch
//--------------------------------------------------------------
void CMagicActionDisarm::launch( CMagicPhrase * phrase, sint deltaLevel, sint skillLevel, float successFactor, MBEHAV::CBehaviour & behav,
								 const std::vector<float> &powerFactors, NLMISC::CBitSet & affectedTargets, const NLMISC::CBitSet & invulnerabilityOffensive,
								 const NLMISC::CBitSet & invulnerabilityAll, bool isMad, NLMISC::CBitSet & resists, const TReportAction & actionReport )
{
	H_AUTO(CMagicActionDisarm_launch);

	if (successFactor <= 0.0f)
		return;

	CEntityBase * actor = CEntityBaseManager::getEntityBasePtr(phrase->getActor());
	if (!actor)
		return;

	const vector<CSpellTarget> &targets = phrase->getTargets();
	const uint nbTargets = targets.size();
	for (uint i = 0 ; i < nbTargets ; ++i)
	{
		if (!TheDataset.isAccessible(targets[i].getId()))
			continue;

		// get target entity
		CEntityBase *target = CEntityBaseManager::getEntityBasePtr(targets[i].getId());
		if (!target)
			continue;

		// if entity is already dead, return
		if (target->isDead())
			continue;
		
		// check entity is a player
		if (target->getId().getType() != RYZOMID::player)
		{
			continue;
		}

		affectedTargets.set(i);

		CTargetInfos targetInfos;
		targetInfos.RowId		= target->getEntityRowId();
		targetInfos.MainTarget	= (i == 0);

		_ApplyTargets.push_back(targetInfos);
	}
} // launch //

//--------------------------------------------------------------
//					apply  
//--------------------------------------------------------------
void CMagicActionDisarm::apply( CMagicPhrase * phrase, sint deltaLevel, sint skillLevel, float successFactor, MBEHAV::CBehaviour & behav,
								const std::vector<float> &powerFactors, NLMISC::CBitSet & affectedTargets, const NLMISC::CBitSet & invulnerabilityOffensive,
								const NLMISC::CBitSet & invulnerabilityAll, bool isMad, NLMISC::CBitSet & resists, const TReportAction & actionReport,
								sint32 vamp, float vampRatio, bool reportXp )
{
	H_AUTO(CMagicActionDisarm_apply);

	CEntityBase *actor = CEntityBaseManager::getEntityBasePtr(phrase->getActor());
	if (!actor)
		return;

	const uint nbTargets = _ApplyTargets.size();
	for (uint i = 0 ; i < nbTargets ; ++i)
	{
		if (!TheDataset.isAccessible(_ApplyTargets[i].RowId))
			continue;

		// get target entity
		CEntityBase *target = CEntityBaseManager::getEntityBasePtr(_ApplyTargets[i].RowId);
		if (!target)
			continue;

		// if entity is already dead, return
		if (target->isDead())
			continue;
		
		// check entity is a player
		if (target->getId().getType() != RYZOMID::player)
		{
			continue;
		}
		CCharacter *character = dynamic_cast<CCharacter*> (target);
		if (!character)
			continue;
		
		// check character has an item in right hand
		if ( character->getRightHandItem() == NULL)
		{
			if (actor->getId().getType() == RYZOMID::player)
			{
				// send chat messages
				SM_STATIC_PARAMS_1(params, STRING_MANAGER::player);
				params[0].setEIdAIAlias( character->getId(), CAIAliasTranslator::getInstance()->getAIAlias(character->getId()) );
				
				PHRASE_UTILITIES::sendDynamicSystemMessage( actor->getEntityRowId(), "COMBAT_DISARM_NO_ITEM", params);
			}
			
			continue;
		}

		// unequip right hand item
		character->unequipCharacter( INVENTORIES::handling, INVENTORIES::right );
		
		// send chat messages
		SM_STATIC_PARAMS_1(params, STRING_MANAGER::entity);
		params[0].setEIdAIAlias( actor->getId(), CAIAliasTranslator::getInstance()->getAIAlias(actor->getId()) );
		
		PHRASE_UTILITIES::sendDynamicSystemMessage( character->getEntityRowId(), "COMBAT_DISARM_DEFENDER", params);
		
		if ( actor->getId().getType() == RYZOMID::player )
		{
			// send chat messages
			params.resize(1);
			params[0].Type = STRING_MANAGER::player;
			params[0].setEIdAIAlias( character->getId(), CAIAliasTranslator::getInstance()->getAIAlias(character->getId()) );
			
			PHRASE_UTILITIES::sendDynamicSystemMessage( actor->getEntityRowId(), "COMBAT_DISARM_ATTACKER", params);
		}
	}
} // apply //


CMagicAiSpecializedActionTFactory<CMagicActionDisarm> *CMagicActionAiDisarmFactoryInstance = new CMagicAiSpecializedActionTFactory<CMagicActionDisarm>(AI_ACTION::Disarm);
