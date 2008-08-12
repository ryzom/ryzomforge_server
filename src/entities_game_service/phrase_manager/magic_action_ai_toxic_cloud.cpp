/** \file magic_action_ai_toxic_cloud.cpp
 * <File description>
 *
 * $Id: magic_action_ai_toxic_cloud.cpp,v 1.14 2005/07/11 12:33:33 vuarand Exp $
 */

 

#include "stdpch.h"
#include "magic_action_ai_toxic_cloud.h"
#include "phrase_manager/magic_phrase.h"
#include "phrase_manager/toxic_cloud.h"
#include "creature_manager/creature_manager.h"
#include "egs_sheets/egs_static_ai_action.h"


using namespace NLMISC;
using namespace std;

extern CCreatureManager CreatureManager;

//--------------------------------------------------------------
//					initFromAiAction
//--------------------------------------------------------------
bool CMagicAiActionToxicCloud::initFromAiAction( const CStaticAiAction *aiAction, CMagicPhrase *phrase )
{
#ifdef NL_DEBUG
	nlassert(phrase);
	nlassert(aiAction);
#endif
	
	if (aiAction->getType() != AI_ACTION::ToxicCloud )
		return false;
	
	// read parameters
	const COTSpellParams &data = aiAction->getData().OTSpell;

	CCreature *creature = CreatureManager.getCreature( phrase->getActor() );
	if (creature && creature->getForm())
		_Damage = (uint16)(data.SpellParamValue + data.SpellPowerFactor * creature->getForm()->getAttackLevel());
	else
		_Damage = (uint16)data.SpellParamValue;
	
	_EffectDuration = data.Duration;
	_UpdateFrequency = data.UpdateFrequency;
	_AffectedScore = data.AffectedScore;
	_DamageType = data.DamageType;
	
	// get effect radius
	const TAiArea &areaData = aiAction->getAreaData();
	_Radius = areaData.AreaRange;

	return true;
} // initFromAiAction //

//--------------------------------------------------------------
//					launch
//--------------------------------------------------------------
void CMagicAiActionToxicCloud::launch( CMagicPhrase * phrase, sint deltaLevel, sint skillLevel, float successFactor, MBEHAV::CBehaviour & behav,
									   const std::vector<float> &powerFactors, NLMISC::CBitSet & affectedTargets, const NLMISC::CBitSet & invulnerabilityOffensive,
									   const NLMISC::CBitSet & invulnerabilityAll, bool isMad, NLMISC::CBitSet & resists, const TReportAction & actionReport )
{
} // launch //

//--------------------------------------------------------------
//					apply  
//--------------------------------------------------------------
void CMagicAiActionToxicCloud::apply( CMagicPhrase * phrase, sint deltaLevel, sint skillLevel, float successFactor, MBEHAV::CBehaviour & behav,
									  const std::vector<float> &powerFactors, NLMISC::CBitSet & affectedTargets, const NLMISC::CBitSet & invulnerabilityOffensive,
									  const NLMISC::CBitSet & invulnerabilityAll, bool isMad, NLMISC::CBitSet & resists, const TReportAction & actionReport,
									  sint32 vamp, float vampRatio, bool reportXp )
{
	NL_ALLOC_CONTEXT(MAATCAPY);
	H_AUTO(CMagicAiActionToxicCloud_apply);

	if (!phrase || !_EffectDuration)
		return;
	
	// get acting entity position
	const TDataSetRow actorRowId = phrase->getActor();
	CEntityBase *actor = CEntityBaseManager::getEntityBasePtr(actorRowId);
	if (!actor)
		return;

	CVector pos;
	pos.x = actor->getX() / 1000.0f;
	pos.y = actor->getY() / 1000.0f;
	pos.z = actor->getZ() / 1000.0f;

	CToxicCloud *cloud = new CToxicCloud();
	if (!cloud)
	{
		nlwarning("MAGIC: failed to allocate new CToxicCloud object, memory full?");
		return;
	}

	cloud->init(pos, _Radius, _Damage, _UpdateFrequency, _EffectDuration);

	// fx radius
	uint8 fxRadius; // {0,1,2} for range (1,3,5 m)
	if (_Radius <= 1.5f)
	{
		fxRadius = 0;
	}
	else if (_Radius <= 4)
	{
		fxRadius = 1;
	}
	else
	{
		fxRadius = 2;
	}

	// spawn toxic cloud and add it to manager
	CSheetId sheet( toString( "toxic_cloud_%d.fx", fxRadius ));
	if ( cloud->spawn( sheet ) )
	{
		CEnvironmentalEffectManager::getInstance()->addEntity( cloud );
	}
	else
	{
		nlwarning( "MAGIC: Unable to spawn toxic cloud sheet %s", sheet.toString().c_str() );
		delete cloud;
	}
} // apply //

CMagicAiActionTFactory<CMagicAiActionToxicCloud> *CMagicActionToxicCloudAiFactoryInstance = new CMagicAiActionTFactory<CMagicAiActionToxicCloud>(AI_ACTION::ToxicCloud);
