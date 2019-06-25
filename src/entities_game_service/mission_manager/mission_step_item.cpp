// Ryzom - MMORPG Framework <http://dev.ryzom.com/projects/ryzom/>
// Copyright (C) 2010  Winch Gate Property Limited
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.



#include "stdpch.h"
#include "nel/misc/algo.h"
#include "mission_step_template.h"
#include "game_item_manager/player_inv_xchg.h"
#include "mission_manager/mission_template.h"
#include "player_manager/character.h"
#include "player_manager/player_manager.h"
#include "creature_manager/creature_manager.h"
#include "mission_log.h"
#include "mission_manager/mission_parser.h"
#include "mission_manager/ai_alias_translator.h"
#include "egs_mirror.h"
#include "primitives_parser.h"
#include "egs_sheets/egs_sheets.h"
#include "egs_pd.h"


using namespace std;
using namespace NLMISC;
using namespace EGSPD;

/***************************************************************************************************
Steps linked with items
	-forage
	-craft
	-buy
	-sell
***************************************************************************************************/

bool	IMissionStepItem::buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData )
{
	_SourceLine = line;
	bool ret = true;
	if ( script.size() < 2 )
	{
		MISLOGSYNTAXERROR("<item> [<quantity>][<quality>] *[; <item> [<quantity>][<quality>]]");
		return false;
	}
	else
	{
		std::vector< std::string > subs;
		NLMISC::splitString( script[1],";", subs );
		bool qualityFound = false;
		bool qualityNotFound = false;
		for ( uint i = 0; i < subs.size(); i++ )
		{
			CSubStep subStep;
			std::vector< std::string > args;
			CMissionParser::tokenizeString( subs[i]," \t", args );

			//// Dynamic Mission Args : #dynamic#
			if ((args.size() == 1) && (args[0] == "#dynamic#"))
			{
				subStep.Dynamic = missionData.Name;
				subStep.Quantity = 10000; // Use a very high value to prevent end of mission
			}
			////
			else
			{
				if ( args.size() < 1 || args.size() > 3 )
				{
					ret = false;
					MISLOGSYNTAXERROR("<item> [<quantity>][<quality>] *[; <item> [<quantity>][<quality>]]");
					return false;
				}
				missionData.ChatParams.push_back( make_pair( args[0], STRING_MANAGER::item ) );
				subStep.Dynamic = "";
				subStep.Sheet = CSheetId(args[0] + ".sitem");
				if ( args.size() > 1 )
					NLMISC::fromString(args[1], subStep.Quantity);
				else
					subStep.Quantity = 1;

				if ( args.size() == 3 )
				{
					NLMISC::fromString(args[2], subStep.Quality);
					qualityFound = true;
				}
				else
				{
					subStep.Quality = 0;
					qualityNotFound = true;
				}
				if ( subStep.Sheet == CSheetId::Unknown )
				{
					ret = false;
					MISLOGERROR1("invalid sheet %s", args[0].c_str());
				}
				if ( qualityFound && qualityNotFound )
				{
					ret = false;
					MISLOGERROR("step mixing steps mixing quality and quantity");
				}
			}
			_SubSteps.push_back( subStep );
		}

		return ret;
	}
}

void IMissionStepItem::getInitState( std::vector<uint32>& ret )
{
	ret.clear();
	ret.resize( _SubSteps.size() );
	for ( uint i = 0; i < _SubSteps.size(); i++ )
	{
		ret[i] = _SubSteps[i].Quantity;
	}
}

inline void IMissionStepItem::getTextParams(uint & nbSubSteps, TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates)
{
	nlassert( _SubSteps.size() == subStepStates.size() );
	CSheetId itemSheet;
	uint16 quality;
	uint32 quantity;

	bool isCraftAndGive = _CraftType == "Craft&Give";

	for ( uint i  = 0; i < subStepStates.size();i++ )
	{
		if ( subStepStates[i] != 0 )
		{
			if (_SubSteps[i].Dynamic.empty())
			{
				itemSheet = _SubSteps[i].Sheet;
				quantity = subStepStates[i];
				quality = _SubSteps[i].Quality;
			}
			else
			{
				//// Dynamic Mission Args
				vector<string> params = _User->getCustomMissionParams(_SubSteps[i].Dynamic);
				vector<string> status = _User->getCustomMissionParams(_SubSteps[i].Dynamic+"_STATUS");

				if (params.size() < 2)
				{
					itemSheet = CSheetId::Unknown;
				}
				else
				{
					itemSheet = CSheetId(params[1]);
				}

				if (params.size() > 2)
					NLMISC::fromString(params[2], quantity);
						
				if (status.size() > 0) // Use saved step quantity
					NLMISC::fromString(status[0], quantity);

				if (params.size() > 3) {
					NLMISC::fromString(params[3], quality);
				}
				////
			}

			if (itemSheet != CSheetId::Unknown)
			{
				nbSubSteps++;
				retParams.push_back(STRING_MANAGER::TParam());
				retParams.back().Type = STRING_MANAGER::item;
				retParams.back().SheetId = itemSheet;

				retParams.push_back(STRING_MANAGER::TParam());
				retParams.back().Type = STRING_MANAGER::integer;
				if (isCraftAndGive)
					retParams.back().Int = (uint)(quantity / 10000);
				else
				retParams.back().Int = quantity;

				if (quality)
				{
					retParams.push_back(STRING_MANAGER::TParam());
					retParams.back().Type = STRING_MANAGER::integer;
					retParams.back().Int = quality;
				}

				if (isCraftAndGive)
				{
					retParams.push_back(STRING_MANAGER::TParam());
					retParams.back().Type = STRING_MANAGER::integer;
					retParams.back().Int = quantity % 10000;
				}
			}
		}
	}
}


// ----------------------------------------------------------------------------
class CMissionStepForage : public IMissionStepItem
{

	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow )
	{
		string webAppUrl;
		_User = PlayerManager.getChar(getEntityIdFromRow(userRow));
		
		if ( event.Type == CMissionEvent::Forage )
		{
			CMissionEventForage & eventSpe = (CMissionEventForage&)event;
			CSheetId itemSheet;
			uint16 quality;
			uint32 quantity;

			
			if (_SubSteps[subStepIndex].Dynamic.empty()) {
				itemSheet = _SubSteps[subStepIndex].Sheet;
				quality = _SubSteps[subStepIndex].Quality;
				quantity = _SubSteps[subStepIndex].Quantity;
			}
			else
			{   /// Dynamic Mission Args
				vector<string> params = _User->getCustomMissionParams(_SubSteps[subStepIndex].Dynamic);
				webAppUrl = params[0];
				if (params.size() < 2)
				{
					LOGMISSIONSTEPERROR("forage : invalid item");
					return 0;
				}
				else
				{
					itemSheet = CSheetId(params[1]);
				}

				if (params.size() > 2)
					NLMISC::fromString(params[2], quantity);

				if (params.size() > 3)
					NLMISC::fromString(params[3], quality);
			}

			if ( eventSpe.Sheet == itemSheet && eventSpe.Quality >= quality )
			{
				LOGMISSIONSTEPSUCCESS("forage");
				if (!webAppUrl.empty() && _SubSteps[subStepIndex].Quantity > quantity)
				{
					/// TODO : Check it

					_SubSteps[subStepIndex].Quantity = 0;
					_User->validateDynamicMissionStep(webAppUrl);
				}
				return eventSpe.Quantity;
			}
		}
		return 0;
	}

	virtual void getTextParams( uint & nbSubSteps, const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates)
	{
		IMissionStepItem::getTextParams(nbSubSteps, retParams, subStepStates);
		static const std::string stepText = "MIS_FORAGE_";
		textPtr = &stepText;
	}

	MISSION_STEP_GETNEWPTR(CMissionStepForage)
};
MISSION_REGISTER_STEP(CMissionStepForage,"forage")


// ----------------------------------------------------------------------------
/// !!!!!!!!!!!! UNUSED !!!!!!!!!!!!!
// ----------------------------------------------------------------------------
class CMissionStepLootItem : public IMissionStepItem
{
	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow )
	{
		string webAppUrl;
		uint16 quantity = 1;
		_User = PlayerManager.getChar(getEntityIdFromRow(userRow));

		if ( event.Type == CMissionEvent::LootItem )
		{
			CSheetId itemSheet;
			uint16 quality;

			if (_SubSteps[subStepIndex].Dynamic.empty()) {
				itemSheet = _SubSteps[subStepIndex].Sheet;
				quality = _SubSteps[subStepIndex].Quality;
			}
			else
			{   /// Dynamic Mission Args
				vector<string> params = _User->getCustomMissionParams(_SubSteps[subStepIndex].Dynamic);
				vector<string> status = _User->getCustomMissionParams(_SubSteps[subStepIndex].Dynamic+"_STATUS");
				webAppUrl = params[0];
				if (params.size() < 2)
				{
					LOGMISSIONSTEPERROR("loot : invalid item");
					return 0;
				}
				else
				{
					itemSheet = CSheetId(params[1]);
				}


				if (params.size() < 3) // If no quantity in mission params => 1 by default
					params[2] = "1";

				if (status.size() == 0) // If no saved quantity => use mission param
					status.push_back(params[2]);
				
				NLMISC::fromString(status[0], quantity); // Use saved quantity

				if (params.size() > 3)
					NLMISC::fromString(params[3], quality);
			}

		
			CMissionEventLootItem & eventSpe = (CMissionEventLootItem&)event;
			if ( eventSpe.Sheet == itemSheet && eventSpe.Quality >= quality )
			{
				if (!webAppUrl.empty())
					{
						if (quantity <= eventSpe.Quantity)
						{
							_User->setCustomMissionParams(_SubSteps[subStepIndex].Dynamic+"_STATUS", "");
							_User->validateDynamicMissionStep(webAppUrl);
							LOGMISSIONSTEPSUCCESS("loot_item");
							return 1000; // Force the end of mission

						}
						else
						{
							_User->setCustomMissionParams(_SubSteps[subStepIndex].Dynamic+"_STATUS", NLMISC::toString("%d", quantity-eventSpe.Quantity));
						}
					}
				
				LOGMISSIONSTEPSUCCESS("loot_item");
				return eventSpe.Quantity;
			}
		}
		return 0;
	}

	virtual void getTextParams( uint & nbSubSteps, const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates)
	{
		IMissionStepItem::getTextParams(nbSubSteps, retParams, subStepStates);
		static const std::string stepText = "MIS_LOOT_ITEM_";
		textPtr = &stepText;
	}

	MISSION_STEP_GETNEWPTR(CMissionStepLootItem)
};
MISSION_REGISTER_STEP(CMissionStepLootItem,"loot_item")


// ----------------------------------------------------------------------------
uint CMissionStepLootRm::processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow )
{
	string webAppUrl;
	uint16 quantity = 1;
	_User = PlayerManager.getChar(getEntityIdFromRow(userRow));


	if ( event.Type == CMissionEvent::LootRm )
	{
		CSheetId itemSheet;
		uint16 quality;

		if (_SubSteps[subStepIndex].Dynamic.empty()) {
			itemSheet = _SubSteps[subStepIndex].Sheet;
			quality = _SubSteps[subStepIndex].Quality;
		}
		else
		{   /// Dynamic Mission Args
			vector<string> params = _User->getCustomMissionParams(_SubSteps[subStepIndex].Dynamic);
			vector<string> status = _User->getCustomMissionParams(_SubSteps[subStepIndex].Dynamic+"_STATUS");
			webAppUrl = params[0];
			if (params.size() < 2)
			{
				LOGMISSIONSTEPERROR("loot : invalid item");
				return 0;
			}
			else
			{
				itemSheet = CSheetId(params[1]);
			}


			if (params.size() < 3) // If no quantity in mission params => 1 by default
				params[2] = "1";

			if (status.size() == 0) // If no saved quantity => use mission param
				status.push_back(params[2]);
			
			NLMISC::fromString(status[0], quantity); // Use saved quantity

			if (params.size() > 3)
				NLMISC::fromString(params[3], quality);
		}
		
		CMissionEventLootRm & eventSpe = (CMissionEventLootRm&)event;
		if ( eventSpe.Sheet == itemSheet && eventSpe.Quality >= quality )
		{
			if (!webAppUrl.empty())
				{
					if (quantity <= eventSpe.Quantity)
					{
						_User->setCustomMissionParams(_SubSteps[subStepIndex].Dynamic+"_STATUS", "");
						_User->validateDynamicMissionStep(webAppUrl);
						LOGMISSIONSTEPSUCCESS("loot_item");
						return 1000; // Force the end of mission

					}
					else
					{
						_User->setCustomMissionParams(_SubSteps[subStepIndex].Dynamic+"_STATUS", NLMISC::toString("%d", quantity-eventSpe.Quantity));
					}
				}
			
			LOGMISSIONSTEPSUCCESS("loot_mp");
			return eventSpe.Quantity;
		}
	}
	return 0;
}

void CMissionStepLootRm::getTextParams( uint & nbSubSteps, const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates)
{
	IMissionStepItem::getTextParams(nbSubSteps, retParams, subStepStates);
	static const std::string stepText = "MIS_LOOT_MP_";
	textPtr = &stepText;
}
MISSION_REGISTER_STEP(CMissionStepLootRm,"loot_mp")


// ----------------------------------------------------------------------------
class CMissionStepCraft : public IMissionStepItem
{
	virtual bool	buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData )
	{
		_SourceLine = line;
		_HasBot = false;
		_Bot = CAIAliasTranslator::Invalid;
		if ( !IMissionStepItem::buildStep(line, script,globalData,missionData) )
			return false;
		if ( script.size() == 3 )
		{
			_HasBot = true;
			if ( !CMissionParser::parseBotName(script[2],_Bot,missionData) )
				return false;
		}
		return true;
	}

	virtual uint32 sendContextText(const TDataSetRow& user, const TDataSetRow& interlocutor, CMission * instance, bool & gift, const NLMISC::CEntityId & giver )
	{
		if (_HasBot) {
			CCreature * bot = CreatureManager.getCreature( interlocutor );
			if ( bot )
			{
				if ( ( _Bot != CAIAliasTranslator::Invalid && _Bot == bot->getAlias() ) ||
					( _Bot == CAIAliasTranslator::Invalid && bot->getAlias() == instance->getGiver() ) )
				{
					gift = true;
					TVectorParamCheck vect(1);
					vect[0].Type = STRING_MANAGER::integer;
					vect[0].Int = (sint32)_SubSteps.size();

					CMissionParser::solveEntitiesNames(vect,user,giver);
					return STRING_MANAGER::sendStringToClient( user, "MIS_GIVE_ITEM_MENU" , vect );
				}
			}
			else
			{
				MISLOG("sline:%u ERROR : give_item (sendContextText) : invalid bot %u", _SourceLine, interlocutor.getIndex());
			}
		}
		return 0;
	}

	virtual bool hasBotChatOption(const TDataSetRow & interlocutor, CMission * instance, bool & gift)
	{
		if (!_HasBot)
			return false;

		CCreature * bot = CreatureManager.getCreature( interlocutor );
		if ( ( _Bot != CAIAliasTranslator::Invalid && _Bot == bot->getAlias() ) ||
			( _Bot == CAIAliasTranslator::Invalid && bot->getAlias() == instance->getGiver() ) )
		{
			gift = true;
			return true;
		}
		else
		{
			MISLOG("sline:%u ERROR : craft (hasBotChatOption) : invalid bot %u", _SourceLine, interlocutor.getIndex());
		}
		return false;
	}

	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow )
	{
		if ( event.Type == CMissionEvent::Craft )
		{
			CMissionEventCraft & eventSpe = (CMissionEventCraft&)event;
			if ( eventSpe.Sheet == _SubSteps[subStepIndex].Sheet && eventSpe.Quality >= _SubSteps[subStepIndex].Quality )
			{
				LOGMISSIONSTEPSUCCESS("craft");
				if ( _HasBot )
					return eventSpe.Quantity*10000;
				return eventSpe.Quantity;
			}
		}
		else if( event.Type == CMissionEvent::GiveItem ) {
			if ( _HasBot )
			{
				const CMissionEventGiveItem& eventSpe = (const CMissionEventGiveItem&)event;
				if ( subStepIndex == eventSpe.StepIndex )
				{
					LOGMISSIONSTEPSUCCESS("give_item");
					return eventSpe.Quantity % 10000;
				}
			}
		}
		return 0;
	}

	void getInitState( std::vector<uint32>& ret )
	{
		ret.clear();
		ret.resize( _SubSteps.size() );
		for ( uint i = 0; i < _SubSteps.size(); i++ )
		{
			// Dirty hack by Ulukyn to manage craft and give item in same step (The state are : Craft + 1000*Give)
			ret[i] = _SubSteps[i].Quantity+10000*_SubSteps[i].Quantity;
		}
	}


	virtual void getTextParams( uint & nbSubSteps, const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates)
	{
		if ( _HasBot )
			_CraftType = "Craft&Give";

		IMissionStepItem::getTextParams(nbSubSteps, retParams, subStepStates);
		static const std::string stepText = "MIS_CRAFT_";
		static const std::string stepTextNpc = "MIS_CRAFT_NPC_";
		if ( _HasBot )
		{
			STRING_MANAGER::TParam param;
			param.Type = STRING_MANAGER::bot;

			if ( _Bot != CAIAliasTranslator::Invalid )
				param.Int = _Bot;
			else
				param.Identifier = "giver";
			retParams.push_back(param);

			textPtr = &stepTextNpc;
		}
		else
		textPtr = &stepText;
	}

	virtual TAIAlias getInvolvedBot(bool& invalidIsGiver) const { invalidIsGiver=true; return _Bot; }

	//***********************
	bool checkPlayerGift( CMission * instance, CCharacter * user )
	{
		if ( user->getExchangeMoney() != 0 )
			return false;

		std::vector<CSubStep> validateSteps = _SubSteps;

		// build the list of need item by substracting the template step with the current step state
		// TODO : this code is only aware of the first active step !
		if (instance->getStepsBegin() == instance->getStepsEnd())
			return false;

		const CActiveStepPD &activeStep = instance->getStepsBegin()->second;

		for (uint i=0; i<_SubSteps.size(); ++i)
		{
			const CActiveStepStatePD *activeStepState = activeStep.getStates(i+1);
			if (activeStepState != NULL) {
				validateSteps[i].Quantity = activeStepState->getState() % 10000;
			}
		}
		bool notEmpty = false;

		nlassert(user->getExchangeView() != NULL);
		for (uint i = 0; i < CExchangeView::NbExchangeSlots; i++)
		{
			uint32 exchangeQuantity;
			CGameItemPtr item = user->getExchangeView()->getExchangeItem(i, &exchangeQuantity);
			if (item == NULL)
				continue;

			notEmpty = true;
			uint k = 0;
			for (; k < validateSteps.size(); k++)
			{
				if (item->getSheetId() == validateSteps[k].Sheet && item->recommended() >= validateSteps[k].Quality)
				{
					if (exchangeQuantity > validateSteps[k].Quantity)
					{
						// if user has put more that this sub step quantity, just decrease the quantity
						exchangeQuantity -= validateSteps[k].Quantity;
						validateSteps[k].Quantity = 0;
					}
					else
					{
						// This sub step consume all this stack in the exchange inventory
						validateSteps[k].Quantity -= exchangeQuantity;
						exchangeQuantity = 0;
					}
				}
			}
			// the give is invalid only if there are still some quantity in the exchange bag
			if (exchangeQuantity > 0)
				return false;
		}
		return notEmpty;
	}

	//***********************
	bool itemGiftDone( CCharacter & user , const std::vector< CGameItemPtr > & itemsGiven, const EGSPD::CActiveStepPD & step, std::vector<uint32>& result )
	{
		// init the result vector with the initial values of the sub steps
		for ( map<uint32,EGSPD::CActiveStepStatePD>::const_iterator it = step.getStatesBegin(); it != step.getStatesEnd(); ++it )
		{
			result.push_back( (*it).second.getState() % 10000 );
		}
		// iterate through the exchange inventory items. For now Store in result the remianing quantity of each substep
		for ( uint i  =0; i < itemsGiven.size(); i++ )
		{
			if ( itemsGiven[i] != NULL)
			{


				// the slot is not empty : get quantity / quality /sheet. Special case if we have a stack...
				CSheetId sheet = itemsGiven[i]->getSheetId();
				uint32 quantity = itemsGiven[i]->getStackSize();
				uint32 recommended = itemsGiven[i]->recommended();

				// check if a step matches the item? ( we are sure that the steps are sorted by quality, so the first step who matches will ve the good one )
				bool noMatch = true;
				for ( uint k = 0; k < _SubSteps.size(); k++ )
				{
					if ( _SubSteps[k].Sheet == sheet && _SubSteps[k].Quality <= recommended )
					{
						noMatch = false;
						if ( quantity > result[k] )
						{
							quantity -= result[k];
							result[k] = 0;
							if ( quantity == 0)
								break;
						}
						else
						{
							result[k] -= quantity;
							quantity = 0;
							break;
						}
					}
				}
				if( noMatch )
					return false;
			}
		}

		// we now store in result the actual given quantity
		uint i = 0;
		for ( map<uint32,EGSPD::CActiveStepStatePD>::const_iterator it = step.getStatesBegin(); it != step.getStatesEnd(); ++it )
		{
			result[i] = (*it).second.getState() - result[i];
			i++;
		}
		return true;
	}


	bool _HasBot;
	TAIAlias _Bot;

	MISSION_STEP_GETNEWPTR(CMissionStepCraft)
};
MISSION_REGISTER_STEP(CMissionStepCraft,"craft")


// ----------------------------------------------------------------------------
class CMissionStepBuyItem : public IMissionStepItem
{
	virtual bool	buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData )
	{
		_SourceLine = line;
		_HasBot = false;
		_Bot = CAIAliasTranslator::Invalid;
		if ( !IMissionStepItem::buildStep(line, script,globalData,missionData) )
			return false;
		if ( script.size() == 3 )
		{
			_HasBot = true;;
			if ( !CMissionParser::parseBotName(script[2],_Bot,missionData) )
				return false;
		}
		return true;
	}

	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow )
	{
		if ( event.Type == CMissionEvent::BuyItem )
		{
			CMissionEventBuyItem & eventSpe = (CMissionEventBuyItem&)event;
			if ( eventSpe.Sheet == _SubSteps[subStepIndex].Sheet && eventSpe.Quality >= _SubSteps[subStepIndex].Quality )
			{
				if ( _HasBot )
				{
					if ( _Bot != CAIAliasTranslator::Invalid )
					{
						const CEntityId & eId = CAIAliasTranslator::getInstance()->getEntityId( _Bot );
						if ( eId == CEntityId::Unknown )
						{
							LOGMISSIONSTEPERROR("buy : invalid npc alias '" + CPrimitivesParser::aliasToString(_Bot) + "'");
							return 0;
						}
						if ( getEntityIdFromRow(eventSpe.TargetEntity) != eId )
							return 0;
					}
					else
					{
						if ( eventSpe.TargetEntity != giverRow )
							return 0;
					}
				}
				LOGMISSIONSTEPSUCCESS("buy");
				return eventSpe.Quantity;
			}
		}
		return 0;
	}

	virtual void getTextParams( uint & nbSubSteps, const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates)
	{
		IMissionStepItem::getTextParams(nbSubSteps, retParams, subStepStates);
		static const std::string stepText = "MIS_BUY_";
		static const std::string stepTextNpc = "MIS_BUY_NPC_";
		if ( _HasBot )
		{
			STRING_MANAGER::TParam param;
			param.Type = STRING_MANAGER::bot;

			if ( _Bot != CAIAliasTranslator::Invalid )
				param.Int = _Bot;
			else
				param.Identifier = "giver";
			retParams.push_back(param);
			textPtr = &stepTextNpc;
		}
		else
			textPtr = &stepText;
	}

	virtual TAIAlias getInvolvedBot(bool& invalidIsGiver) const { invalidIsGiver=true; return _Bot; }

	bool _HasBot;
	TAIAlias _Bot;

	MISSION_STEP_GETNEWPTR(CMissionStepBuyItem)
};
MISSION_REGISTER_STEP(CMissionStepBuyItem,"buy")


// ----------------------------------------------------------------------------
class CMissionStepSellItem : public IMissionStepItem
{
	virtual bool	buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData )
	{
		_SourceLine = line;
		_HasBot = false;
		_Bot = CAIAliasTranslator::Invalid;
		if ( !IMissionStepItem::buildStep(line, script,globalData,missionData) )
			return false;
		if ( script.size() == 3 )
		{
			_HasBot = true;;
			if ( !CMissionParser::parseBotName(script[2],_Bot,missionData) )
				return false;
		}
		return true;
	}

	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow )
	{
		if ( event.Type == CMissionEvent::SellItem )
		{
			CMissionEventSellItem & eventSpe = (CMissionEventSellItem&)event;
			if ( eventSpe.Sheet == _SubSteps[subStepIndex].Sheet && eventSpe.Quality >= _SubSteps[subStepIndex].Quality )
			{
				if ( _HasBot )
				{
					if ( _Bot != CAIAliasTranslator::Invalid )
					{
						const CEntityId & eId = CAIAliasTranslator::getInstance()->getEntityId( _Bot );
						if ( eId == CEntityId::Unknown )
						{
							LOGMISSIONSTEPERROR("sell : invalid bot alias '" + CPrimitivesParser::aliasToString(_Bot) + "'");
							return 0;
						}
						if ( getEntityIdFromRow(eventSpe.TargetEntity) != eId )
							return 0;
					}
					else
					{
						if ( eventSpe.TargetEntity != giverRow )
							return 0;
					}
				}
				LOGMISSIONSTEPSUCCESS("sell");
				return eventSpe.Quantity;
			}
		}
		return 0;
	}

	virtual void getTextParams( uint & nbSubSteps, const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates)
	{
		IMissionStepItem::getTextParams(nbSubSteps,retParams, subStepStates);
		static const std::string stepText = "MIS_SELL_";
		static const std::string stepTextNpc = "MIS_SELL_NPC_";
		if ( _HasBot )
		{
			STRING_MANAGER::TParam param;
			param.Type = STRING_MANAGER::bot;

			if ( _Bot != CAIAliasTranslator::Invalid )
				param.Int = _Bot;
			else
				param.Identifier = "giver";

			retParams.push_back(param);
			textPtr = &stepTextNpc;
		}
		else
			textPtr = &stepText;
	}

	virtual TAIAlias getInvolvedBot(bool& invalidIsGiver) const { invalidIsGiver=true; return _Bot; }

	bool _HasBot;
	TAIAlias _Bot;

	MISSION_STEP_GETNEWPTR(CMissionStepSellItem)
};
MISSION_REGISTER_STEP(CMissionStepSellItem,"sell")
