/** \file magic_action_ai_mass_dispel.cpp
 * <File description>
 *
 * $Id: magic_action_ai_mass_dispel.cpp,v 1.13 2005/02/22 10:22:30 besson Exp $
 */

 

#include "stdpch.h"
#include "magic_action_ai_mass_dispel.h"
#include "phrase_manager/magic_phrase.h"
#include "phrase_manager/effect_factory.h"
#include "phrase_manager/phrase_manager.h"
#include "entity_structure/statistic.h"
#include "entity_manager/entity_manager.h"
#include "server_share/ai_event_report.h"

using namespace NLMISC;
using namespace std;

//--------------------------------------------------------------
//					initFromAiAction
//--------------------------------------------------------------
bool CMagicAiActionMassDispel::initFromAiAction( const CStaticAiAction *aiAction, CMagicPhrase *phrase )
{
#ifdef NL_DEBUG
	nlassert(phrase);
	nlassert(aiAction);
#endif
	
	if (aiAction->getType() != AI_ACTION::EffectSpell )
		return false;
	
	// read parameters
	const CEffectSpellParams &data = aiAction->getData().EffectSpell;
		
	return true;
} // initFromAiAction //

//--------------------------------------------------------------
//					launch
//--------------------------------------------------------------
void CMagicAiActionMassDispel::launch( CMagicPhrase * phrase, sint deltaLevel, sint skillLevel, float successFactor, MBEHAV::CBehaviour & behav,
									   const std::vector<float> &powerFactors, NLMISC::CBitSet & affectedTargets, const NLMISC::CBitSet & invulnerabilityOffensive,
									   const NLMISC::CBitSet & invulnerabilityAll, bool isMad, NLMISC::CBitSet & resists, const TReportAction & actionReport )
{
	H_AUTO(CMagicAiActionEffect_launch);

	if (!phrase || successFactor <= 0.0f)
		return;

	const vector<CSpellTarget> &targets = phrase->getTargets();
	const uint nbTargets = targets.size();
	for (uint i = 0 ; i < nbTargets ; ++i)
	{
		if (!TheDataset.isAccessible(targets[i].getId()))
			continue;

		// valid on all targets, no test needed

		// get target entity
		CEntityBase *target = CEntityBaseManager::getEntityBasePtr(targets[i].getId());
		if (!target)
			continue;

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
void CMagicAiActionMassDispel::apply( CMagicPhrase * phrase, sint deltaLevel, sint skillLevel, float successFactor, MBEHAV::CBehaviour & behav,
									  const std::vector<float> &powerFactors, NLMISC::CBitSet & affectedTargets, const NLMISC::CBitSet & invulnerabilityOffensive,
									  const NLMISC::CBitSet & invulnerabilityAll, bool isMad, NLMISC::CBitSet & resists, const TReportAction & actionReport,
									  sint32 vamp, float vampRatio, bool reportXp )
{
	H_AUTO(CMagicAiActionMassDispel_apply);

	const uint nbTargets = _ApplyTargets.size();
	for (uint i = 0 ; i < nbTargets ; ++i)
	{
		if (!TheDataset.isAccessible(_ApplyTargets[i].RowId))
			continue;

		// valid on all targets, no test needed

		// get target entity
		CEntityBase *target = CEntityBaseManager::getEntityBasePtr(_ApplyTargets[i].RowId);
		if (!target)
			continue;

		// clear all effects on entity
		target->removeAllSpells();
	}
} // apply //


CMagicAiSpecializedActionTFactory<CMagicAiActionMassDispel> *CMagicActionAiMassDispelFactoryInstance = new CMagicAiSpecializedActionTFactory<CMagicAiActionMassDispel>(AI_ACTION::MassDispel);
