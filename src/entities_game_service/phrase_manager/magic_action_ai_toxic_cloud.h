/** \file magic_action_ai_toxic_cloud.h
 * <File description>
 *
 * $Id: magic_action_ai_toxic_cloud.h,v 1.7 2004/12/08 13:26:44 besson Exp $
 */



#ifndef RY_MAGIC_ACTION_AI_TOXIC_CLOUD_H
#define RY_MAGIC_ACTION_AI_TOXIC_CLOUD_H


#include "magic_action.h"
#include "game_share/damage_types.h"
#include "game_share/scores.h"

class CMagicPhrase;

class CMagicAiActionToxicCloud : public IMagicAction
{
public:
	CMagicAiActionToxicCloud()
	{
		_EffectDuration = 0;
		_Damage = 0;
	}

	/// build from an ai action
	virtual bool initFromAiAction( const CStaticAiAction *aiAction, CMagicPhrase *phrase );

protected:
	virtual bool addBrick( const CStaticBrick & brick, CMagicPhrase * phrase, bool &effectEnd, CBuildParameters &buildParams )
	{ return false; }
	
	virtual bool validate(CMagicPhrase * phrase, std::string &errorCode) { return true; }

	virtual void launch( CMagicPhrase * phrase, sint deltaLevel, sint skillLevel, float successFactor, MBEHAV::CBehaviour & behav,
						 const std::vector<float> &powerFactors, NLMISC::CBitSet & affectedTargets, const NLMISC::CBitSet & invulnerabilityOffensive,
						 const NLMISC::CBitSet & invulnerabilityAll, bool isMad, NLMISC::CBitSet & resists, const TReportAction & actionReport );

	virtual void apply( CMagicPhrase * phrase, sint deltaLevel, sint skillLevel, float successFactor, MBEHAV::CBehaviour & behav,
						const std::vector<float> &powerFactors, NLMISC::CBitSet & affectedTargets, const NLMISC::CBitSet & invulnerabilityOffensive,
						const NLMISC::CBitSet & invulnerabilityAll, bool isMad, NLMISC::CBitSet & resists, const TReportAction & actionReport,
						sint32 vamp, float vampRatio, bool reportXp );

protected:
	/// effect duration
	NLMISC::TGameCycle		_EffectDuration;
	/// UpdateFrequency
	NLMISC::TGameCycle		_UpdateFrequency;
	/// damage type
	DMGTYPE::EDamageType	_DamageType;
	/// affected score
	SCORES::TScores			_AffectedScore;
	/// amount of damage dealt each update
	sint32					_Damage;
	/// cloud radius in meters
	float					_Radius;
};


#endif // RY_MAGIC_ACTION_AI_TOXIC_CLOUD_H

/* End of magic_action_ai_toxic_cloud.h */
