/** \file combat_action_disarm.cpp
 * <File description>
 *
 * $Id: combat_action_disarm.cpp,v 1.13 2005/03/16 16:01:38 lancon Exp $
 */

 

#include "stdpch.h"
#include "combat_action_disarm.h"
#include "combat_phrase.h"
#include "player_manager/player.h"

using namespace NLMISC;
using namespace std;

extern SKILLS::ESkills		BarehandCombatSkill;

//--------------------------------------------------------------
//					initFromAiAction  
//--------------------------------------------------------------
bool CCombatActionDisarm::initFromAiAction( const CStaticAiAction *aiAction, CCombatPhrase *phrase )
{
#if !FINAL_VERSION
	nlassert(phrase);
	nlassert(aiAction);
#endif
	
	if (aiAction->getType() != AI_ACTION::Range && aiAction->getType() != AI_ACTION::Melee)
		return false;
	
	_ActorRowId = phrase->getAttacker()->getEntityRowId();
	_ActingEntity = CEntityBaseManager::getEntityBasePtr(_ActorRowId);
	
	// read parameters
	//const CCombatParams &data = aiAction->getData().Combat;
	
	
	return true;
} // initFromAiAction //

//--------------------------------------------------------------
//					apply  
//--------------------------------------------------------------
void CCombatActionDisarm::apply( CCombatPhrase *phrase )
{
#if !FINAL_VERSION
	nlassert(phrase);
#endif

	H_AUTO(CCombatActionDisarm_apply);

	const vector<CCombatPhrase::TTargetInfos> &targets = phrase->getTargets();
	const uint nbTargets = targets.size();
	for (uint i = 0 ; i < nbTargets ; ++i)
	{
		//if ( !phrase->hasTargetDodged(i) )
		if ( phrase->getTargetDodgeFactor(i) == 0.0f )
			applyOnTarget(i,phrase);
	}
} // apply //

//--------------------------------------------------------------
//					applyOnTarget()  
//--------------------------------------------------------------
void CCombatActionDisarm::applyOnTarget(uint8 targetIndex, CCombatPhrase *phrase)
{
#if !FINAL_VERSION
	nlassert(phrase);
#endif
	
	const CCombatDefenderPtr &targetDefender = phrase->getTarget(targetIndex);
	if(!targetDefender) return;
	
	CEntityBase *entity = targetDefender->getEntity();
	if (!entity)
	{
		nlwarning("COMBAT : <CCombatActionDisarm::applyOnTarget> Cannot find the target entity, cancel");
		return;
	}
	
//	applyOnEntity(entity, phrase->getPhraseSuccessDamageFactor());
	applyOnEntity(entity, 1.0f-phrase->getTargetDodgeFactor(targetIndex));
	
} // applyOnTarget //


//--------------------------------------------------------------
//					applyOnEntity()  
//--------------------------------------------------------------
void CCombatActionDisarm::applyOnEntity( CEntityBase *entity, float successFactor )
{
	if (!entity ) return;
	if (_ActingEntity == NULL) return;
	
	// if entity is already dead, return
	if (entity->isDead())
		return;
	
	// check entity is a player
	if (entity->getId().getType() != RYZOMID::player)
	{
		return;
	}

	CCharacter *character = dynamic_cast<CCharacter*> (entity);
	if (!character)
	{
		nlwarning("Entity %s type is player but dynamic_cast in CCharacter * returns NULL ?!", entity->getId().toString().c_str());
		return;
	}

	// check character has an item in right hand
	if ( character->getRightHandItem() == NULL)
	{
		if (_ActingEntity->getId().getType() == RYZOMID::player)
		{
			// send chat messages
			SM_STATIC_PARAMS_1(params, STRING_MANAGER::player);
			params[0].setEIdAIAlias( character->getId(), CAIAliasTranslator::getInstance()->getAIAlias(character->getId()) );
			
			PHRASE_UTILITIES::sendDynamicSystemMessage( _ActorRowId, "COMBAT_DISARM_NO_ITEM", params);
		}

		return;
	}

	
	// unequip right hand item
	character->unequipCharacter( INVENTORIES::handling, INVENTORIES::right );
		
	// send chat messages
	SM_STATIC_PARAMS_1(params, STRING_MANAGER::entity);
	params[0].setEIdAIAlias( _ActingEntity->getId(), CAIAliasTranslator::getInstance()->getAIAlias(_ActingEntity->getId()) );

	PHRASE_UTILITIES::sendDynamicSystemMessage( character->getEntityRowId(), "COMBAT_DISARM_DEFENDER", params);

	if ( _ActingEntity->getId().getType() == RYZOMID::player )
	{
		// send chat messages
		params.resize(1);
		params[0].Type = STRING_MANAGER::player;
		params[0].setEIdAIAlias( character->getId(), CAIAliasTranslator::getInstance()->getAIAlias(character->getId()) );
		
		PHRASE_UTILITIES::sendDynamicSystemMessage( _ActorRowId, "COMBAT_DISARM_ATTACKER", params);
	}
	
} // applyOnEntity //

CCombatAIActionTFactory<CCombatActionDisarm> *CCombatAiDisarmFactoryInstance = new CCombatAIActionTFactory<CCombatActionDisarm>(AI_ACTION::Disarm);
