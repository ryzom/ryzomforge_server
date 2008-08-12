/** \file s_link_effect_hot.cpp
 * <File description>
 *
 * $Id: s_link_effect_hot.cpp,v 1.2 2004/03/01 19:22:18 lecroart Exp $
 */



#include "stdpch.h"
#include "s_link_effect_hot.h"
#include "entity_manager.h"
#include "character.h"
#include "phrase_utilities_functions.h"
#include "game_share/entity_structure/statistic.h"
#include "nel/misc/random.h"

using namespace std;
using namespace NLMISC;
using namespace RY_GAME_SHARE;

extern CRandom RandomGenerator;


bool CSLinkEffectHot::update(uint32 & updateFlag)
{
	if ( CSLinkEffect::update(updateFlag) )
		return true;

	CEntityBase * caster = CEntityBaseManager::getEntityBasePtr( _CreatorRowId );
	if ( !caster )
	{
		nlwarning("<CSLinkEffectHot update> Invalid caster %u",_CreatorRowId.getIndex() );
		return true;
	}
	CEntityBase * target = CEntityBaseManager::getEntityBasePtr( _TargetRowId );
	if ( !target )
	{
		nlwarning("<CSLinkEffectHot update> Invalid target %u",_TargetRowId.getIndex() );
		return true;
	}
	
	applyOnScore( caster, target,SCORES::hit_points, _HealHp );
	applyOnScore( caster, target,SCORES::sap, _HealSta );
	applyOnScore( caster, target,SCORES::stamina, _HealSta );
	
	updateFlag |= _Family;
	return false;
}


void CSLinkEffectHot::applyOnScore( CEntityBase * caster, CEntityBase * target,SCORES::TScores scoreType, sint32 value )
{
	RY_GAME_SHARE::SCharacteristicsAndScores & score = target->getScores()._PhysicalScores[ scoreType ];
	score.Current = score.Current + sint( value );
	if ( score.Current >= score.Max)
	{
		sint32 realHeal = value + score.Max - score.Current;
		if ( realHeal )
			PHRASE_UTILITIES::sendScoreModifierSpellMessage( caster, target, value ,scoreType , ACTNATURE::DEFENSIVE);
		score.Current = score.Max;
	}
	else
		PHRASE_UTILITIES::sendScoreModifierSpellMessage( caster, target, value,scoreType ,ACTNATURE::DEFENSIVE);
	
}
