/** \file magic_action_ai_mass_dispel.h
 * <File description>
 *
 * $Id: magic_action_ai_mass_dispel.h,v 1.7 2004/12/08 13:26:44 besson Exp $
 */



#ifndef RY_MAGIC_ACTION_AI_MASS_DISPEL_H
#define RY_MAGIC_ACTION_AI_MASS_DISPEL_H


#include "magic_action.h"

class CMagicPhrase;

class CMagicAiActionMassDispel : public IMagicAction
{
public:
	CMagicAiActionMassDispel()
	{
		_Range = 0.0f;
	}

	/// build from an ai action
	virtual bool initFromAiAction( const CStaticAiAction *aiAction, CMagicPhrase *phrase );

protected:
	struct CTargetInfos
	{
		TDataSetRow	RowId;
		bool		MainTarget;
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
	/// range in meters
	float		_Range;

	/// targets that need to be treated by apply()
	std::vector<CTargetInfos>		_ApplyTargets;
};


#endif // RY_MAGIC_ACTION_AI_MASS_DISPEL_H

/* End of magic_action_ai_mass_dispel.h */
