/** \file magic_action_hot.cpp
 * <File description>
 *
 * $Id: magic_action_debuff.cpp,v 1.2 2004/03/01 19:22:18 lecroart Exp $
 */

 

#include "stdpch.h"
#include "magic_action.h"
#include "magic_phrase.h"
#include "creature.h"
#include "character.h"
#include "game_share/entity_structure/statistic.h"
#include "s_link_effect_debuff_skill.h"

using namespace NLNET;
using namespace NLMISC;
using namespace RY_GAME_SHARE;
using namespace std;


class CMagicActionDebuffSkill : public IMagicAction
{
public:
	CMagicActionDebuffSkill()
		:_TargetSkill(SKILLS::unknown),_DebuffValue(0){}
protected:
	virtual bool addBrick( const CStaticBrick & brick, CMagicPhrase * phrase )
	{
		for ( uint i=0 ; i<brick.Params.size() ; ++i)
		{
			switch(brick.Params[i]->id())
			{	
				
			case TBrickParam::MA_DEBUFF:
				INFOLOG("MA_DEBUFF: %u",((CSBrickParamMagicDebuff *)brick.Params[i])->Debuff);
				_DebuffValue = ((CSBrickParamMagicDebuff *)brick.Params[i])->Debuff;
				break;
				
			case TBrickParam::MA_LINK_COST:
				INFOLOG("MA_LINK_COST: %u",((CSBrickParamMagicLinkCost *)brick.Params[i])->Cost);
				_CostPerUpdate = ((CSBrickParamMagicLinkCost *)brick.Params[i])->Cost;
				break;
				
			case TBrickParam::SKILL:
				{
					INFOLOG("SKILL: %s",((CSBrickParamSkill *)brick.Params[i])->Skill.c_str());
					_Skill = SKILLS::toSkill( ((CSBrickParamSkill *)brick.Params[i])->Skill );
					if ( _Skill == SKILLS::unknown )
					{
						nlwarning( "<CMagicActionDebuffSkill addBrick> invalid skill type %s", ((CSBrickParamSkill *)brick.Params[i])->Skill.c_str() );
						return false;
					}
					break;
				}
			default:
				// unused param, can be useful in the phrase
				phrase->applyBrickParam( brick.Params[i] );
				break;
			}
		}
		///\todo nico: check if everything is set
		return true;
	}
	virtual bool validate(CMagicPhrase * phrase)
	{
		return PHRASE_UTILITIES::validateSpellTarget(phrase->getActor(),phrase->getTargets()[0],ACTNATURE::OFFENSIVE);
	}
	virtual void apply( CMagicPhrase * phrase, float successFactor,MBEHAV::CBehaviour & behav )
	{
		///\todo nico:
		//		- localisation
		//		- armure + bouclier
		//		- degâts sur perso + sur armure
		//		- behaviour + messages de chat
		//		- aggro
		
		/// test resistance
		if ( successFactor < 0.0f )
		{
			///\todo nico
			return;
		}
		
		/// apply success factor
		_DebuffValue = uint32( _DebuffValue *  successFactor);
		
		const std::vector< TDataSetRow > & targets = phrase->getTargets();
		CEntityBase* actor = CEntityBaseManager::getEntityBasePtr( phrase->getActor() );
		if (!actor)
			return;

		SCORES::EScores linkEnergy;
		if ( phrase->getSapCost() > 0 )
		{
			linkEnergy = SCORES::sap;
		}
		else
			linkEnergy = SCORES::hit_points;;
		for ( uint i = 0; i < targets.size(); i++ )
		{
			// check target
			CEntityBase* target = CEntityBaseManager::getEntityBasePtr( targets[i] );
			if ( !target)
				continue;
			
			if ( PHRASE_UTILITIES::validateSpellTarget(actor,target,ACTNATURE::OFFENSIVE) )
			{
				CSLinkEffectDebuffSkill* debuff = new CSLinkEffectDebuffSkill( phrase->getActor(),
					targets[i],
					_UpdatePeriod,
					_CostPerUpdate,
					linkEnergy,
					_Skill,
					_TargetSkill,
					_DebuffValue  );
				actor->addLink( debuff );
				target->addSabrinaEffect( debuff );
			}
		}
	}
	
	SKILLS::ESkills			_TargetSkill;
	sint32					_DebuffValue;
	uint					_CostPerUpdate;
};
MAGIC_ACTION_FACTORY( CMagicActionDebuffSkill,BRICK_FAMILIES::MADebuffSkill )


