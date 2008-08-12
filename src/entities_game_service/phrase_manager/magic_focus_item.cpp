/** \file magic_focus_item.cpp
 * <File description>
 *
 * $Id: magic_focus_item.cpp,v 1.3 2005/02/22 10:22:30 besson Exp $
 */



//////////////
//	INCLUDE	//
//////////////
#include "stdpch.h"
//
#include "magic_focus_item.h"
#include "game_item_manager/game_item.h"

//////////////
//	USING	//
//////////////
using namespace std;
using namespace NLMISC;

//-----------------------------------------------
void CMagicFocusItemFactor::init(const CGameItemPtr& item)
{
	_IsMagicFocus = false;

	if (item == NULL)
		return;

	_RequiredLevel = (uint16)item->recommended();
	
	_ElementalCastingTimeFactor = item->getElementalCastingTimeFactor();
	_ElementalPowerFactor = item->getElementalPowerFactor();
	if (_ElementalCastingTimeFactor != 0.0f || _ElementalPowerFactor != 0.0f)
		_IsMagicFocus = true;
	
	_OffensiveAfflictionCastingTimeFactor = item->getOffensiveAfflictionCastingTimeFactor();
	_OffensiveAfflictionPowerFactor = item->getOffensiveAfflictionPowerFactor();
	if (_OffensiveAfflictionCastingTimeFactor != 0.0f || _OffensiveAfflictionPowerFactor != 0.0f )
		_IsMagicFocus = true;
	
	_HealCastingTimeFactor = item->getHealCastingTimeFactor();
	_HealPowerFactor = item->getHealPowerFactor();
	if (_HealCastingTimeFactor != 0.0f || _HealPowerFactor != 0.0f )
		_IsMagicFocus = true;
	
	_DefensiveAfflictionCastingTimeFactor = item->getDefensiveAfflictionCastingTimeFactor();
	_DefensiveAfflictionPowerFactor = item->getDefensiveAfflictionPowerFactor();
	if (_DefensiveAfflictionCastingTimeFactor != 0.0f || _DefensiveAfflictionPowerFactor != 0.0f )
		_IsMagicFocus = true;		
}

//-----------------------------------------------
float CMagicFocusItemFactor::getCastingTimeFactor( SKILLS::ESkills skill, uint16 spellPower) const
{
	if (spellPower > _RequiredLevel)
		return 0.0f;
	
	float returnVal = 0.0f;
	
	const std::string &str = SKILLS::toString(skill);
	if ( _ElementalCastingTimeFactor && str.substr(0,4) == _ElementalSkill)
	{
		returnVal = _ElementalCastingTimeFactor;
	}
	else if ( _OffensiveAfflictionCastingTimeFactor && str.substr(0,4) == _OffensiveAfflictionSkill)
	{
		returnVal = _OffensiveAfflictionCastingTimeFactor;
	}
	else if ( _HealCastingTimeFactor && str.substr(0,4) == _HealSkill)
	{
		returnVal = _HealCastingTimeFactor;
	}
	else if ( _DefensiveAfflictionCastingTimeFactor && str.substr(0,4) == _DefensiveAfflictionSkill)
	{
		returnVal = _DefensiveAfflictionCastingTimeFactor;
	}
	
	if (returnVal > 0.0f)
		_WearItem = true;
	
	return returnVal;
}

//-----------------------------------------------
float CMagicFocusItemFactor::getPowerFactor( SKILLS::ESkills skill, uint16 spellPower) const
{
	if (spellPower > _RequiredLevel)
		return 0.0f;
	
	float returnVal = 0.0f;
	
	const std::string &str = SKILLS::toString(skill);
	if ( _ElementalPowerFactor && str.substr(0,4) == _ElementalSkill)
	{
		returnVal = _ElementalPowerFactor;
	}
	if ( _OffensiveAfflictionPowerFactor && str.substr(0,4) == _OffensiveAfflictionSkill)
	{
		returnVal = _OffensiveAfflictionPowerFactor;
	}
	if ( _HealPowerFactor && str.substr(0,4) == _HealSkill)
	{
		returnVal = _HealPowerFactor;
	}
	if ( _DefensiveAfflictionPowerFactor && str.substr(0,4) == _DefensiveAfflictionSkill)
	{
		returnVal = _DefensiveAfflictionPowerFactor;
	}
				
	if (returnVal > 0.0f)
		_WearItem = true;
	
	return returnVal;
}
