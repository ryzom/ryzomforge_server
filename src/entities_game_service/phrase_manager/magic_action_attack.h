/** \file magic_action_attack.h
 * <File description>
 *
 * $Id: magic_action_attack.h,v 1.2 2006/05/31 12:14:12 boucher Exp $
 */


#ifndef RY_MAGIC_ACTION_ATTACK_H
#define RY_MAGIC_ACTION_ATTACK_H

#include "magic_action.h"


class CMagicActionBasicDamage
: public IMagicAction
{
public:
	CMagicActionBasicDamage();
	
	/// build from an ai action
	bool initFromAiAction(CStaticAiAction const* aiAction, CMagicPhrase* phrase);
	
public:
	class CTargetInfos
	{
	public:
		/// returns true if the target needs to be treated by apply()
		bool needsApply() const
		{
			return (DmgHp > 0 || Immune || ResistFactor<=0.f);
		}
		
	public:
		TDataSetRow		RowId;
		bool			MainTarget;
		sint32			DmgHp;
		float			ResistFactor;
		float			DmgFactor;
		bool			Immune;
		TReportAction	ReportAction;
	};

protected:
	/// @name IMagicAction interface
	//@{
	virtual bool validate(CMagicPhrase* phrase, std::string& errorCode);
	
	virtual void launch(
		CMagicPhrase*				phrase,
		sint						deltaLevel,
		sint						skillLevel,
		float						successFactor,
		MBEHAV::CBehaviour&			behav,
		std::vector<float> const&	powerFactors,
		NLMISC::CBitSet&			affectedTargets,
		NLMISC::CBitSet const&		invulnerabilityOffensive,
		NLMISC::CBitSet const&		invulnerabilityAll,
		bool						isMad,
		NLMISC::CBitSet&			resists,
		TReportAction const&		actionReport);
	
	virtual void apply(
		CMagicPhrase*				phrase,
		sint						deltaLevel,
		sint						skillLevel,
		float						successFactor,
		MBEHAV::CBehaviour&			behav,
		std::vector<float> const&	powerFactors,
		NLMISC::CBitSet&			affectedTargets,
		NLMISC::CBitSet const&		invulnerabilityOffensive,
		NLMISC::CBitSet const&		invulnerabilityAll,
		bool						isMad,
		NLMISC::CBitSet&			resists,
		TReportAction const&		actionReport,
		sint32						vamp,
		float						vampRatio,
		bool						reportXp);
	
	virtual bool addBrick(CStaticBrick const& brick, CMagicPhrase* phrase, bool& effectEnd, CBuildParameters& buildParams);
	//@}
	
private:
	/// returns true if target resists
	bool launchOnEntity(
		CMagicPhrase*		phrase,
		CEntityBase*		actor,
		CEntityBase*		target,
		bool				mainTarget,
		uint32				casterSkillvalue,
		uint32				casterSkillBaseValue,
		MBEHAV::CBehaviour&	behav,
		bool				isMad,
		float				rangeFactor,
		CTargetInfos&		targetInfos);
	
public:
	/// returns true if target resists
	static bool applyOnEntity(
		CMagicPhrase*	phrase,
		CEntityBase*	actor,
		CEntityBase*	target,
		sint32			vamp,
		float			vampRatio,
		CTargetInfos&	targetInfos,
		
		DMGTYPE::EDamageType const	_DmgType,
		sint32 const				_DmgHp,
		sint32 const				_DmgSap,
		sint32 const				_DmgSta,
		sint32 const				_VampirismValue);

	static bool computeMagicResistance(
		CEntityBase* const target,
		CTargetInfos& targetInfos, //< modified
		uint32 const casterSkillvalue,
		DMGTYPE::EDamageType const _DmgType,
		sint32 _DmgHp,
		CEntityBase const* const actor,
		float rangeFactor,
		float powerFactor);
		
private:
	DMGTYPE::EDamageType	_DmgType;
	sint32					_DmgHp;
	sint32					_DmgSap;
	sint32					_DmgSta;
	sint32					_VampirismValue;
	
	/// targets that need to be treated by apply()
	std::vector<CTargetInfos>	_ApplyTargets;
};

#endif
