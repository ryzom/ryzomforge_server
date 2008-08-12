/** \file magic_action_ai_effect.h
 * <File description>
 *
 * $Id: magic_action_ai_effect.h,v 1.17 2004/12/08 13:26:44 besson Exp $
 */



#ifndef RY_MAGIC_ACTION_AI_EFFECT_H
#define RY_MAGIC_ACTION_AI_EFFECT_H


#include "magic_action.h"

class CMagicPhrase;

class CMagicAiActionEffect : public IMagicAction
{
public:
	CMagicAiActionEffect()
	{
		_EffectDuration = 0;
	}

	/// build from an ai action
	virtual bool initFromAiAction( const CStaticAiAction *aiAction, CMagicPhrase *phrase );

protected:
	struct CTargetInfos
	{
		TDataSetRow	RowId;
		bool		MainTarget;
		float		ResistFactor;
		bool		Immune;
	};

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
	NLMISC::TGameCycle	_EffectDuration;
	/// effect duration type
	DURATION_TYPE::TDurationType	_EffectDurationType;
	/// effect family
	EFFECT_FAMILIES::TEffectFamily _EffectFamily;
	/// effect param value
	sint32				_ParamValue;

	/// targets that need to be treated by apply()
	std::vector<CTargetInfos> _ApplyTargets;
};


#endif // RY_MAGIC_ACTION_AI_EFFECT_H

/* End of magic_action_ai_effect.h */
