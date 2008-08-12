/** \file s_link_effect_debuff_stat.cpp
 * <File description>
 *
 * $Id: s_link_effect_debuff_stat.cpp,v 1.12 2005/02/22 10:22:30 besson Exp $
 */



#include "stdpch.h"
#include "s_link_effect_debuff_stat.h"
#include "s_link_effect_dot.h"
#include "entity_manager/entity_manager.h"
#include "entity_structure/statistic.h"



using namespace std;
using namespace NLMISC;

extern CRandom RandomGenerator;


//--------------------------------------------------------------
bool CSLinkEffectDebuffStat::update(CTimerEvent * event, bool applyEffect)
{
	NL_ALLOC_CONTEXT(SLEDS);
	if ( CSLinkEffectOffensive::update(event, applyEffect) )
		return true;
	
	if (_LinkExists)
	{
//		CEntityBase * caster = CEntityBaseManager::getEntityBasePtr( _CreatorRowId );
//		if ( !caster )
//		{
//			nlwarning("<CSLinkEffectDebuffStat update> Invalid target %u",_CreatorRowId.getIndex() );
//			return true;
//		}
	}
	
	if (applyEffect && !_Applied)
	{
		CEntityBase * target = CEntityBaseManager::getEntityBasePtr( _TargetRowId );
		if ( !target )
		{
			nlwarning("<CSLinkEffectDebuffStat update> Invalid target %u",_TargetRowId.getIndex() );
			_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
			return true;
		}

		switch( _Type )
		{
		case STAT_TYPES::Skill:
			///\todo nico
			break;
		case STAT_TYPES::Score:
			///\todo nico
			///\todo progression (report action with scores damage if made by NPC)
			break;
		case STAT_TYPES::Speed:
			target->getPhysScores().SpeedVariationModifier += _Value;
			break;
		default:
			nlwarning("<CSLinkEffectDebuffStat update> invalid stat type %d", _Type);
			_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
			return true;
		}

		_Applied = true;
	}

	return false;
}


//--------------------------------------------------------------
void CSLinkEffectDebuffStat::removed()
{
	// remove effect if effect have been applied
	if (_Applied)
	{
		CEntityBase * target = CEntityBaseManager::getEntityBasePtr( _TargetRowId );
		if ( target )
		{
			switch( _Type )
			{
			case STAT_TYPES::Skill:
				break;
			case STAT_TYPES::Score:
				break;
			case STAT_TYPES::Speed:
				target->getPhysScores().SpeedVariationModifier -= _Value;
				break;
//			default:
//				nlwarning("invalid stat type %d", _Type);
			}
		}
	}

	CSLinkEffectOffensive::removed();
}
