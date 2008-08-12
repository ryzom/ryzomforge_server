/** \file s_link_effect.h
 * <File description>
 *
 * $Id: s_link_effect.h,v 1.2 2004/03/01 19:22:18 lecroart Exp $
 */



#ifndef RY_S_LINK_EFFECT_H
#define RY_S_LINK_EFFECT_H

#include "nel/misc/types_nl.h"
#include "s_effect.h"

class CSLinkEffect : public CSEffect
{
public:
	inline CSLinkEffect( 
		const TDataSetRow & creatorRowId, 
		const TDataSetRow & targetRowId,
		EFFECT_FAMILIES::TEffectFamily family, 
		sint32 cost,
		SCORES::TScores energyCost,
		SKILLS::ESkills skill,
		sint32 value,
		uint8 power)
		:CSEffect(creatorRowId,targetRowId,family,value,power),
		_CostPerUpdate(cost),
		_EnergyCost(energyCost),
		_Skill(skill),
		_NextUpdate(0)
	{
	
	}

	/**
	 *  return true if it is time to update the effect. It modifies the next update of the effect
	 */
	bool isTimeToUpdate();

	bool update(uint32 & updateFlag);
	
	virtual void removed();
	
	inline static double getUpdatePeriod(){return _UpdatePeriod;}
	
protected:
	NLMISC::TGameCycle		_NextUpdate;
	sint32					_CostPerUpdate;
	SCORES::TScores			_EnergyCost;
	SKILLS::ESkills			_Skill;

	static double			_UpdatePeriod;		
};

class CSLinkEffectOffensive : public CSLinkEffect
{
public:
	inline CSLinkEffectOffensive( const TDataSetRow & creatorRowId, 
		const TDataSetRow & targetRowId,
		EFFECT_FAMILIES::TEffectFamily family, 
		sint32 cost,
		SCORES::TScores energyCost,
		SKILLS::ESkills skill,
		sint32 value,
		uint8 power)
		:CSLinkEffect(creatorRowId,targetRowId,family,cost,energyCost,skill,value,power),_ResistFactor(0.0f)
	{
	}
	
	bool update(uint32 & updateFlag);
	
protected:
	float	_ResistFactor;
};

#endif // RY_S_LINK_EFFECT_H

/* End of s_link_effect.h */
