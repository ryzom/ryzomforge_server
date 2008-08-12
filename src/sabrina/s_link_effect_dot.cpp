/** \file s_link_effect_dot.cpp
 * <File description>
 *
 * $Id: s_link_effect_dot.cpp,v 1.2 2004/03/01 19:22:18 lecroart Exp $
 */



#include "stdpch.h"
#include "s_link_effect_dot.h"
#include "entity_manager.h"
#include "character.h"
#include "game_share/entity_structure/statistic.h"
#include "nel/misc/random.h"
#include "s_link_effect.h"
#include "phrase_utilities_functions.h"

using namespace std;
using namespace NLMISC;
using namespace RY_GAME_SHARE;

extern CRandom RandomGenerator;


bool CSLinkEffectDot::update(uint32 & updateFlag)
{
	if ( CSLinkEffectOffensive::update(updateFlag) )
		return true;

	CEntityBase * caster = CEntityBaseManager::getEntityBasePtr( _CreatorRowId );
	if ( !caster )
	{
		nlwarning("<CSLinkEffectDot update> Invalid target %u",_CreatorRowId.getIndex() );
		return true;
	}

	CEntityBase * target = CEntityBaseManager::getEntityBasePtr( _TargetRowId );
	if ( !target )
	{
		nlwarning("<CSLinkEffectDot update> Invalid target %u",_TargetRowId.getIndex() );
		return true;
	}
	float mult = _ResistFactor;
	// get damage amplifier on target
	const CSEffect * effect = target->lookForSEffect( EFFECT_FAMILIES::MagicDmgAmpli );
	if ( effect )
		mult *=  (effect->getParamValue() / 100.0f);
	
	

	
	sint32 realDmg = sint32( _DmgHp * mult );
	realDmg = target->applyDamageOnArmor( _DmgType, realDmg );
	if ( target->changeCurrentHp( - realDmg ) )
	{
		// send mission event
		if ( caster->getId().getType() == RYZOMID::player )
		{
			CMissionEventKill event ( target->getEntityRowId() );
			((CCharacter*) caster)->processMissionEvent( event );
		}
		PHRASE_UTILITIES::sendScoreModifierSpellMessage( caster, target, realDmg ,SCORES::hit_points , ACTNATURE::OFFENSIVE);
	}

	{
		RY_GAME_SHARE::SCharacteristicsAndScores &score = target->getScores()._PhysicalScores[SCORES::sap];
		realDmg = sint32( _DmgSap * mult );
		realDmg = target->applyDamageOnArmor( _DmgType, realDmg );
		score.Current = score.Current - realDmg;
		if ( score.Current <= 0)
			score.Current = 0;
		PHRASE_UTILITIES::sendScoreModifierSpellMessage( caster, target, realDmg ,SCORES::sap , ACTNATURE::OFFENSIVE);
	}

	{
		RY_GAME_SHARE::SCharacteristicsAndScores &score = target->getScores()._PhysicalScores[SCORES::stamina];
		realDmg = sint32( _DmgSta * mult );
		realDmg = target->applyDamageOnArmor( _DmgType, realDmg );
		score.Current = score.Current - realDmg;
		if ( score.Current <= 0)
			score.Current = 0;
		PHRASE_UTILITIES::sendScoreModifierSpellMessage( caster, target, realDmg ,SCORES::stamina , ACTNATURE::OFFENSIVE);
	}
	
	updateFlag |= _Family;
	return false;
}
