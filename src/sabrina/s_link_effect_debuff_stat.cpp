/** \file s_link_effect_debuff_stat.cpp
 * <File description>
 *
 * $Id: s_link_effect_debuff_stat.cpp,v 1.2 2004/03/01 19:22:18 lecroart Exp $
 */



#include "stdpch.h"
#include "s_link_effect_debuff_stat.h"
#include "s_link_effect_dot.h"
#include "entity_manager.h"
#include "game_share/entity_structure/statistic.h"



using namespace std;
using namespace NLMISC;
using namespace RY_GAME_SHARE;

extern CRandom RandomGenerator;


bool CSLinkEffectDebuffStat::update(uint32 & updateFlag)
{
	if ( CSLinkEffectOffensive::update(updateFlag) )
		return true;
	
	CEntityBase * caster = CEntityBaseManager::getEntityBasePtr( _CreatorRowId );
	if ( !caster )
	{
		nlwarning("<CSLinkEffectDebuffStat update> Invalid target %u",_CreatorRowId.getIndex() );
		return true;
	}
	
	CEntityBase * target = CEntityBaseManager::getEntityBasePtr( _TargetRowId );
	if ( !target )
	{
		nlwarning("<CSLinkEffectDebuffStat update> Invalid target %u",_TargetRowId.getIndex() );
		return true;
	}

	if ( (_Family & updateFlag) == 0)
	{
		switch( _Type )
		{
		case STAT_TYPES::Skill:
			///\todo nico
			break;
		case STAT_TYPES::Score:
			///\todo nico
			break;
		case STAT_TYPES::Speed:
			target->getPhysScores().SpeedVariationModifier += _Value;
			break;
		default:
			nlwarning("<CSLinkEffectDebuffStat update> invalid stat type %d", _Type);
			return true;
		}
	}
	updateFlag |= _Family;
	return false;
}




