/** \file faber_phrase.cpp
 * <File description>
 *
 * $Id: faber_phrase.cpp,v 1.64 2007/08/02 12:24:49 dailyserver Exp $
 */


#include "stdpch.h"

#include "nel/misc/command.h"

#include "phrase_manager/faber_phrase.h"
#include "game_share/brick_families.h"
#include "s_phrase_factory.h"
#include "entity_manager/entity_manager.h"
#include "player_manager/character.h"
#include "phrase_manager/phrase_manager.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"
#include "phrase_manager/phrase_utilities_functions.h"
#include "entity_structure/statistic.h"


DEFAULT_SPHRASE_FACTORY( CFaberPhrase, BRICK_TYPE::FABER );

using namespace std;
using namespace NLMISC;



extern CPlayerManager		PlayerManager;
extern NLMISC::CRandom		RandomGenerator;

//-----------------------------------------------
// ctor
//-----------------------------------------------
CFaberPhrase::CFaberPhrase()
{
	_FaberAction = 0;
	_SabrinaCost = 0;
	_SabrinaRelativeCost = 1.0f;
	_FocusCost = 0;
	_FaberTime = 0;
	_CraftedItemStaticForm = 0;
	_RootFaberBricks = false;
	_RootFaberPlan = 0;
	
	// recommended skill level for using crafted item
	_Recommended = 0;

	// Item stats modifier
	_MBOQuality = 0;
	_MBODurability = 0.0f;
	_MBOWeight = 0.0f;
	_MBODmg = 0.0f;
	_MBOSpeed = 0.0f;
	_MBORange = 0.0f;
	_MBOProtection = 0.0f;
	_MBOSapLoad = 0.0f;
	
	// energy buff on item
	_MBOHitPoint = 0;
	_MBOSap = 0;
	_MBOStamina = 0;
	_MBOFocus = 0;
	
	_IsStatic = true;
	_PhraseType = BRICK_TYPE::FABER;
}


//-----------------------------------------------
// CFaberPhrase build
//-----------------------------------------------
bool CFaberPhrase::build( const TDataSetRow & actorRowId, const std::vector< const CStaticBrick* >& bricks, bool buildToExecute )
{
	H_AUTO(CFaberPhrase_build);
	
	// we are sure there is at least one brick and that there are non NULL;
	nlassert( !bricks.empty() );

	_ActorRowId = actorRowId;

	// compute cost and credit and parse other params
	for ( uint i = 0; i < bricks.size(); ++i )
	{
		const CStaticBrick & brick = *bricks[i];
		if( brick.SabrinaValue > 0 )
			_SabrinaCost += brick.SabrinaValue;
		if( brick.SabrinaRelativeValue > 0.0f )
			_SabrinaRelativeCost += brick.SabrinaRelativeValue;

/*		if( brick.Family == BRICK_FAMILIES::BCPA )
		{
			if( _RootFaberBricks == false )
			{
				_RootFaberBricks = true;
			}
			else
			{
				PHRASE_UTILITIES::sendDynamicSystemMessage(actorRowId, "ONLY_ONE_ROOT_FABER");
				return false;
			}
		}
		else*/ if( ( brick.Family >= BRICK_FAMILIES::BeginFaberOption && brick.Family <= BRICK_FAMILIES::EndFaberOption ) 
			 ||  ( brick.Family >= BRICK_FAMILIES::BeginFaberCredit && brick.Family <= BRICK_FAMILIES::EndFaberCredit ) )
		{
			for ( uint j = 0 ; j < brick.Params.size() ; ++j)
			{
				const TBrickParam::IId* param = brick.Params[j];

				switch(param->id())
				{	
					case TBrickParam::FOCUS:
						INFOLOG("FOCUS: %i",((CSBrickParamCraftFocus *)param)->Focus);
						_FocusCost += ((CSBrickParamCraftFocus *)param)->Focus;
						break;
					case TBrickParam::CR_RECOMMENDED:
						INFOLOG("RECOMMENDED: %i",((CSBrickParamCraftRecommended *)param)->Recommended);
						_Recommended = ((CSBrickParamCraftRecommended *)param)->Recommended;
						break;
					case TBrickParam::CR_HP:
						INFOLOG("HP: %i",((CSBrickParamCraftHP *)param)->HitPoint);
						_MBOHitPoint += ((CSBrickParamCraftHP *)param)->HitPoint;
						break;
					case TBrickParam::CR_SAP:
						INFOLOG("SAP: %i",((CSBrickParamCraftSap *)param)->Sap);
						_MBOSap = ((CSBrickParamCraftSap *)param)->Sap;
						break;
					case TBrickParam::CR_STA:
						INFOLOG("STA: %i",((CSBrickParamCraftSta *)param)->Stamina);
						_MBOStamina += ((CSBrickParamCraftSta *)param)->Stamina;
						break;
					case TBrickParam::CR_FOCUS:
						INFOLOG("FOCUS: %i",((CSBrickParamCraftFocus *)param)->Focus);
						_MBOFocus += ((CSBrickParamCraftFocus *)param)->Focus;
						break;
					case TBrickParam::CR_QUALITY:
						INFOLOG("QUALITY: %d", ((CSBrickParamCraftQuality *)param)->Quality);
						_MBOQuality += (sint16)((CSBrickParamCraftQuality *)param)->Quality;
						break;
					case TBrickParam::CR_DURABILITY:
						INFOLOG("DURABILITY: %.2f", ((CSBrickParamCraftDurability *)param)->Durability);
						_MBODurability += ((CSBrickParamCraftDurability *)param)->Durability;
						break;
					case TBrickParam::CR_DAMAGE:
						INFOLOG("DAMAGE: %.2f", ((CSBrickParamCraftDamage *)param)->Damage);
						_MBODmg += ((CSBrickParamCraftDamage *)param)->Damage;
						break;
					case TBrickParam::CR_HITRATE:
						INFOLOG("HITRATE: %.2f", ((CSBrickParamCraftHitRate *)param)->HitRate);
						_MBODmg += ((CSBrickParamCraftHitRate *)param)->HitRate;
						break;
					case TBrickParam::CR_RANGE:
						INFOLOG("RANGE: %.2f", ((CSBrickParamCraftRange *)param)->Range);
						_MBORange += ((CSBrickParamCraftRange *)param)->Range;
						break;
					case TBrickParam::CR_DMG_PROTECTION:
						INFOLOG("DMG_PROTECTION: %.2f", ((CSBrickParamCraftDmgProtection *)param)->DmgProtection);
						_MBOProtection += ((CSBrickParamCraftDmgProtection *)param)->DmgProtection;
						break;
					case TBrickParam::CR_SAPLOAD:
						INFOLOG("SAPLOAD: %.2f", ((CSBrickParamCraftSapload *)param)->Sapload);
						_MBOProtection += ((CSBrickParamCraftSapload *)param)->Sapload;
						break;
					case TBrickParam::CR_WEIGHT:
						INFOLOG("WEIGHT: %.2f", ((CSBrickParamCraftWeight *)param)->Weight);
						_MBOWeight += ((CSBrickParamCraftWeight *)param)->Weight;
						break;
					default:
						// unused param ?
						break;
				}
			}
		}
	}

	CCharacter * c = dynamic_cast< CCharacter * > ( CEntityBaseManager::getEntityBasePtr( _ActorRowId ) );
	if( c == 0 )
	{
		nlwarning("<CFaberPhrase::build> Player character not found but his crafting action still running!!!");
		return false;
	}
/*
	if( ( _RootFaberBricks == false ) || ( _Recommended == 0 ) && ( _SabrinaCost > (sint32)_Recommended ) )
	{
		PHRASE_UTILITIES::sendDynamicSystemMessage(actorRowId, "CRAFT_SENTENCE_INCORRECT");
		return false;
	}
*/
	return true;
}// CFaberPhrase build


//-----------------------------------------------
// CFaberPhrase evaluate
//-----------------------------------------------
bool CFaberPhrase::evaluate()
{
	return true;
}// CFaberPhrase evaluate


//-----------------------------------------------
// CFaberPhrase validate
//-----------------------------------------------
bool CFaberPhrase::validate()
{
	H_AUTO(CFaberPhrase_validate);
	
	if ( !CraftSystemEnabled )
		return false;
	
	CCharacter * c = (CCharacter *) CEntityBaseManager::getEntityBasePtr( _ActorRowId );
	if( c == 0 )
	{
		nlwarning("<CFaberPhrase::validate> Player character not found but his crafting action still running!!!");
		return false;
	}

	// test entity can use action
	if (c->canEntityUseAction() == false)
	{
		return false;
	}

	// check right hand item is a crafting tool 
	CGameItemPtr rightHandItem = c->getRightHandItem();
	if (rightHandItem == NULL || rightHandItem->getStaticForm() == NULL || rightHandItem->getStaticForm()->Family != ITEMFAMILY::CRAFTING_TOOL)
	{
		PHRASE_UTILITIES::sendDynamicSystemMessage(_ActorRowId, "CRAFT_NEED_CRAFTING_TOOL");
		return false;
	}

	// check tool is not worned
	if( rightHandItem->getItemWornState() == ITEM_WORN_STATE::Worned )
	{
		PHRASE_UTILITIES::sendDynamicSystemMessage(_ActorRowId, "CRAFT_NEED_CRAFTING_TOOL");
		return false;
	}

	// entities cant craft if in combat
	/* commented as test of right hand item is now made... 
	TDataSetRow entityRowId = CPhraseManager::getInstance().getEntityEngagedMeleeBy( _ActorRowId );
	if (TheDataset.isAccessible(entityRowId))
	{
		PHRASE_UTILITIES::sendDynamicSystemMessage(_ActorRowId, "CANT_CRAFT_ENGAGED_IN_MELEE");
		return false;
	}
	*/
	
	const sint32 focus = c->getScores()._PhysicalScores[ SCORES::focus ].Current;
	if ( focus < _FocusCost  )
	{
		PHRASE_UTILITIES::sendDynamicSystemMessage(_ActorRowId, "CANT_CRAFT_NOT_ENOUGHT_FOCUS");
		c->unlockFaberRms();
		return false;
	}

	const sint32 hp = c->currentHp();
	if (hp <= 0	||	c->isDead())
	{
		PHRASE_UTILITIES::sendDynamicSystemMessage(_ActorRowId, "CANT_CRAFT_WHEN_DEAD");
		c->unlockFaberRms();
		return false;
	}

	/// todo alain : test if on mount

	// store vector of pointer on raw material item
	if( state() == Evaluated )
	{
		if( c->lockFaberRms() )
		{
			_Mps.clear();
			_MpsFormula.clear();
			if( c->getFillFaberRms( _Mps, _MpsFormula, _LowerRmQuality ) == false ) //TODO check exec step
			{
				c->unlockFaberRms();
				PHRASE_UTILITIES::sendDynamicSystemMessage(_ActorRowId, "CANT_FOUND_RM");
				return false;
			}
		}
		else
		{
			c->unlockFaberRms();
			PHRASE_UTILITIES::sendDynamicSystemMessage(_ActorRowId, "CANT_LOCK_RM");
			return false;
		}
	}

	return true;
}// CFaberPhrase validate


//-----------------------------------------------
// CFaberPhrase update
//-----------------------------------------------
bool  CFaberPhrase::update()
{
	return true;
}// CFaberPhrase update


//-----------------------------------------------
// CFaberPhrase execute
//-----------------------------------------------
void  CFaberPhrase::execute()
{
	H_AUTO(CFaberPhrase_execute);
	
	CCharacter* player = PlayerManager.getChar(_ActorRowId);
	if (!player)
		return;

	const CStaticBrick * plan = CSheets::getSBrickForm( player->getCraftPlan() );
	if( plan == 0 )
	{
		nlwarning("<CFaberPhrase::execute> Can't found static form of craft plan %s", player->getCraftPlan().toString().c_str() );
		return;
	}

	/// set Faber time if not set (default is 2 sec)
	if ( !_FaberTime)
	{
		_FaberTime = (NLMISC::TGameCycle)(plan->CraftingDuration * 10);
	}
	nldebug("CFaberPhrase::execute> _FaberTime = %d",_FaberTime);
	
	const NLMISC::TGameCycle time = CTickEventHandler::getGameCycle();
	
	_ExecutionEndDate  = time + _FaberTime ;

	player->setCurrentAction(CLIENT_ACTION_TYPE::Faber,_ExecutionEndDate);
	player->staticActionInProgress(true);	

	// set behaviour
	PHRASE_UTILITIES::sendUpdateBehaviour( _ActorRowId, MBEHAV::FABER );
}// CFaberPhrase execute


//-----------------------------------------------
// CFaberPhrase launch
//-----------------------------------------------
bool CFaberPhrase::launch()
{
	// apply imediatly
	_ApplyDate = 0;
	return true;
}// CFaberPhrase launch


//-----------------------------------------------
// CFaberPhrase apply
//-----------------------------------------------
void CFaberPhrase::apply()
{
	H_AUTO(CFaberPhrase_apply);
	
	CCharacter * c = dynamic_cast< CCharacter * > ( CEntityBaseManager::getEntityBasePtr( _ActorRowId ) );
	if( c == 0 )
	{
		nlwarning("<CFaberPhrase::apply> Player character not found but his crafting action still running!!!");
		stop();
		return;
	}

	// apply wearing equipment penalty on Recommended skill
	_Recommended -= (uint32)(_Recommended * c->wearMalus() * WearMalusCraftFactor);

	const CStaticBrick * plan = CSheets::getSBrickForm( c->getCraftPlan() );
	if( plan == 0 )
	{
		nlwarning("<CFaberPhrase::apply> Can't found static form of craft plan %s", c->getCraftPlan().toString().c_str() );
		PHRASE_UTILITIES::sendDynamicSystemMessage(_ActorRowId, "UNKNOWN_CRAFT_PLAN");
		stop();
		return;
	}
	_RootFaberPlan = plan;

	// TODO check compatibility of Rms with plan
	// temporary only check number of Mp match with plan

	sint32 nbMp = _Mps.size();

	uint32 nbMpNeedeInPlan = 0;
	uint32 neededMp = _RootFaberPlan->Faber->NeededMps.size();
	for( uint mp = 0; mp < _RootFaberPlan->Faber->NeededMps.size(); ++mp )
	{
		//for each type of Mp needed
		nbMpNeedeInPlan += _RootFaberPlan->Faber->NeededMps[ mp ].Quantity;
	}

	if( nbMpNeedeInPlan != _Mps.size() )
	{
		nlwarning("<CFaberPhrase::apply> Craft plan %s need %d Raw Material and client send %d Raw Material", c->getCraftPlan().toString().c_str(), _RootFaberPlan->Faber->NeededMps.size(), _Mps.size() );
		PHRASE_UTILITIES::sendDynamicSystemMessage(_ActorRowId, "RAW_MATERIAL_MISSING");
		stop();
		return;
	}

	nbMp = _MpsFormula.size();
	
	nbMpNeedeInPlan = 0;
	neededMp = _RootFaberPlan->Faber->NeededMpsFormula.size();
	for( uint mp = 0; mp < _RootFaberPlan->Faber->NeededMpsFormula.size(); ++mp )
	{
		//for each type of Mp needed
		nbMpNeedeInPlan += _RootFaberPlan->Faber->NeededMpsFormula[ mp ].Quantity;
	}
	
	if( nbMpNeedeInPlan != _MpsFormula.size() )
	{
		nlwarning("<CFaberPhrase::apply> Craft plan %s need %d Raw Material Formula and client send %d Raw Material Formula", c->getCraftPlan().toString().c_str(), _RootFaberPlan->Faber->NeededMpsFormula.size(), _MpsFormula.size() );
		PHRASE_UTILITIES::sendDynamicSystemMessage(_ActorRowId, "RAW_MATERIAL_MISSING");
		stop();
		return;
	}

	// Check skill on faber plan
	if( _RootFaberPlan->getSkill(0) == SKILLS::unknown )
	{
		nlwarning("<CFaberPhrase::apply> Craft plan %s contains an invalid skill", c->getCraftPlan().toString().c_str() );
		PHRASE_UTILITIES::sendDynamicSystemMessage(_ActorRowId, "INVALID_CRAFT_PLAN");
		stop();
		return;
	}

	_CraftedItemStaticForm = CSheets::getForm( plan->Faber->CraftedItem );
	if( _CraftedItemStaticForm == 0 )
	{
		nlwarning("<CFaberPhrase::apply> Can't found static form of crafted item %s", plan->Faber->CraftedItem.toString().c_str() );
		PHRASE_UTILITIES::sendDynamicSystemMessage(_ActorRowId, "UNKNOWN_CRAFTED_ITEM");
		stop();
		return;
	}

	// build the craft action
	_FaberAction = IFaberActionFactory::buildAction( _ActorRowId, this, _CraftedItemStaticForm->Type );
	if ( !_FaberAction )
	{
		nlwarning( "<CFaberPhrase build> could not build action for plan brick %s", _RootFaberPlan->SheetId.toString().c_str() );
		stop();
		return;
	}
	
	// spend energies
	SCharacteristicsAndScores &focus = c->getScores()._PhysicalScores[SCORES::focus];
	if ( focus.Current != 0)
	{
		focus.Current = focus.Current - _FocusCost;
		if (focus.Current < 0)
			focus.Current = 0;
	}

	// apply action of the sentence
	_FaberAction->apply(this);
	_CraftedItem = 0;
}//CFaberPhrase apply


//-----------------------------------------------
// CFaberPhrase systemCraftItem:
//-----------------------------------------------
CGameItemPtr CFaberPhrase::systemCraftItem( const NLMISC::CSheetId& sheet, const std::vector< NLMISC::CSheetId >& Mp, const std::vector< NLMISC::CSheetId >& MpFormula )
{
	H_AUTO(CFaberPhrase_systemCraftItem);
	
	std::vector< const CStaticBrick* > bricks;
	_RootFaberPlan = CSheets::getSBrickForm( sheet );
	const CStaticBrick * rootFaberBricks = CSheets::getSBrickForm( CSheetId("bcpa01.sbrick") );
	if( rootFaberBricks )
	{
		_RootFaberBricks = true;
	}
	else
	{
		nlwarning("<CFaberPhrase::systemCraftItem> Can't found form of root faber brick bcpa01.sbrick");
		return 0;
	}

	CGameItemPtr craftedItem = 0;
	
	if( _RootFaberPlan && _RootFaberPlan->Faber )
	{
		_CraftedItemStaticForm = CSheets::getForm( _RootFaberPlan->Faber->CraftedItem );
		if( _CraftedItemStaticForm == 0 )
		{
			return 0;
		}

		bricks.push_back( rootFaberBricks );
		bricks.push_back( _RootFaberPlan );
		
		for( vector< NLMISC::CSheetId >::const_iterator it = Mp.begin(); it != Mp.end(); ++it )
		{
			const CStaticItem * mp = CSheets::getForm( (*it) );
			if( mp == 0 )
			{
				nlwarning("<CFaberPhrase::systemCraftItem> Can't found form for Mp %s for craft %s item", (*it).toString().c_str(), sheet.toString().c_str() );
				return 0;
			}
			_Mps.push_back( mp );
		}

		// Check quantity of gived Mps
		if( _RootFaberPlan->Faber->NeededMps.size() > _Mps.size() )
		{
			nlwarning("<CFaberPhrase::systemCraftItem> Not enought gived RM for crafting %s (gived Mp %d, Needed Mp %d)", sheet.toString().c_str(), _Mps.size(), _RootFaberPlan->Faber->NeededMps.size() );
			return 0;
		}

		for( vector< NLMISC::CSheetId >::const_iterator it = MpFormula.begin(); it != MpFormula.end(); ++it )
		{
			const CStaticItem * mp = CSheets::getForm( (*it) );
			if( mp == 0 )
			{
				nlwarning("<CFaberPhrase::systemCraftItem> Can't found form for Mp Formula %s for craft %s item", (*it).toString().c_str(), sheet.toString().c_str() );
				return 0;
			}
			_MpsFormula.push_back( mp );
		}
		
		// Check quantity of gived Mps formula
		if( _RootFaberPlan->Faber->NeededMpsFormula.size() > _MpsFormula.size() )
		{
			nlwarning("<CFaberPhrase::systemCraftItem> Not enought gived RM formula for crafting %s (gived Mp %d, Needed Mp %d)", sheet.toString().c_str(), _MpsFormula.size(), _RootFaberPlan->Faber->NeededMpsFormula.size() );
			return 0;
		}

		// build the craft action
		_FaberAction = IFaberActionFactory::buildAction( _ActorRowId, this, _CraftedItemStaticForm->Type );
		if ( !_FaberAction )
		{
			nlwarning( "<CFaberPhrase build> could not build action for root faber %s", _RootFaberPlan->SheetId.toString().c_str() );
			return 0;
		}
		_FaberAction->systemApply(this);
		if( _CraftedItem != 0 )
		{
			_CraftedItem->setDefaultColor();
		}
		craftedItem = _CraftedItem;
		_CraftedItem = 0;
	}
	return craftedItem;
} // systemCraftItem //

//-----------------------------------------------
// CFaberPhrase end
//-----------------------------------------------
void CFaberPhrase::end()
{
	H_AUTO(CFaberPhrase_end);
	
	CCharacter* player = PlayerManager.getChar(_ActorRowId);
	if (!player)
		return;

	player->unlockFaberRms();
	player->clearCurrentAction();
	player->staticActionInProgress(false);
	//player->sendCloseTempInventoryImpulsion();

	// set behaviour
	PHRASE_UTILITIES::sendUpdateBehaviour( _ActorRowId, MBEHAV::FABER_END );
} // end //


//-----------------------------------------------
// CFaberPhrase stop
//-----------------------------------------------
void CFaberPhrase::stop()
{
	H_AUTO(CFaberPhrase_stop);
	
	CCharacter* player = PlayerManager.getChar(_ActorRowId);
	if (!player)
		return;

	player->unlockFaberRms();
	player->clearCurrentAction();
	player->staticActionInProgress(false);
	player->sendCloseTempInventoryImpulsion();

	// set behaviour
	PHRASE_UTILITIES::sendUpdateBehaviour( _ActorRowId, MBEHAV::FABER_END );

	// send message
	PHRASE_UTILITIES::sendDynamicSystemMessage(_ActorRowId, "FABER_CANCEL");
} // stop //


NLMISC_COMMAND(simuCraft, "Simulation de craft pour verifier les probabilitÚs de reusir un item","<Nb simulations><level skill><item quality>")
{
	if (args.size() != 3)
		return false;
	
	uint32 nbSimu = (uint32)atoi(args[0].c_str());
	uint32 skillLevel = (uint32)atoi(args[1].c_str());
	uint32 itemQuality = (uint32)atoi(args[2].c_str());

	sint32 deltaLvl = skillLevel - itemQuality;

	float sf;

	uint32	nbFullSuccess = 0;
	uint32	nbPartialSuccess = 0;
	uint32	nbMiss = 0;

	double XpGain = 0;
	sint32 skillValue = 0;
	sint32 deltaLvlXp = 0;

	for(uint32 i = 0; i < nbSimu; ++i)
	{
		uint8 roll =(uint8) RandomGenerator.rand(100);

		sf = CStaticSuccessTable::getSuccessFactor( SUCCESS_TABLE_TYPE::Craft, deltaLvl, roll );

		// xp gains
		skillValue = skillLevel;
		sint32 minimum = max( (sint32)10, min( (sint32)50, (sint32)( skillValue + 10 ) ) );
		deltaLvlXp = deltaLvl * (sint32)50 / minimum;

		if(sf == 1.0f)
		{
			++nbFullSuccess;
			XpGain += CStaticSuccessTable::getXPGain(SUCCESS_TABLE_TYPE::Craft, deltaLvlXp);		
		}
		else if( sf > 0.0f)
		{
			++nbPartialSuccess;
			XpGain += CStaticSuccessTable::getXPGain(SUCCESS_TABLE_TYPE::Craft, deltaLvlXp) * sf;
		}
		else
			++nbMiss;
	}

	nlinfo("FaberSimu: Results after %d roll: Sucess: %d (%.2f%%), partial sucess: %d (%.2f%%), Miss: %d (%.2f%%), Xp Gain %d",
		nbSimu,
		nbFullSuccess, 100.0f*nbFullSuccess/nbSimu,
		nbPartialSuccess, 100.0f*nbPartialSuccess/nbSimu, 
		nbMiss, 100.0f*nbMiss/nbSimu,
		uint32(1000.f*XpGain / (nbSimu-nbMiss/2) ) );

	return true;
}
