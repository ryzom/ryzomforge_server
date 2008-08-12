/** \file mission_step_kill.cpp
 * <File description>
 *
 * $Id: mission_step_kill.cpp,v 1.38 2007/08/02 12:24:48 dailyserver Exp $
 */



#include "stdpch.h"
#include "mission_step_template.h"
#include "mission_manager/mission_template.h"
#include "mission_log.h"
#include "zone_manager.h"
#include "mission_manager/ai_alias_translator.h"
#include "creature_manager/creature_manager.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"
#include "player_manager/character.h"
#include "mission_manager/mission_parser.h"
#include "nel/misc/algo.h"
#include "game_share/fame.h"
#include "game_share/stl_allocator_checker.h"

using namespace std;
using namespace NLMISC;


/***************************************************************************************************
Steps linked with kill events
	-kill_fauna
	-kill_species ( from the GSPeople::EPeople enum )
	-kill_npc
***************************************************************************************************/

// ----------------------------------------------------------------------------
class CMissionStepKillFauna : public IMissionStepTemplate
{
	struct CSubStep
	{
		CSheetId	Sheet;
		uint16		Quantity;
	};
	virtual bool	buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData )
	{
		_SourceLine = line;
		_Place = 0xFFFF;
		bool ret = true;
		if ( script.size() < 2 || script.size() > 3)
		{
			MISLOGSYNTAXERROR("<creature> <quantity> *[; <creature> <quantity>] [: <place>]");
			return false;
		}
		else
		{
			std::vector< std::string > subs;
			NLMISC::splitString( script[1],";", subs );
			_SubSteps.reserve( subs.size() );
			for ( uint i = 0; i < subs.size(); i++ )
			{
				std::vector< std::string > args;
				CMissionParser::tokenizeString( subs[i]," \t", args );
				if ( args.size() != 2 )
				{
					MISLOGSYNTAXERROR("<creature> <quantity> *[; <creature> <quantity>] [: <place>]");
					return false;
				}
				missionData.ChatParams.push_back( make_pair(args[0],STRING_MANAGER::creature_model) );
				CSubStep subStep;
				subStep.Sheet = CSheetId( args[0] + ".creature");
				if ( subStep.Sheet == CSheetId::Unknown )
				{
					ret = false;
					MISLOGERROR1("invalid sheet '%s'", args[0].c_str());
				}
				subStep.Quantity = atoi( args[1].c_str() );
				_SubSteps.push_back(subStep);
			}
			if ( script.size() == 3 )
			{
				string placeStr = CMissionParser::getNoBlankString( script[2] );
				CPlace * place = CZoneManager::getInstance().getPlaceFromName( placeStr );
				missionData.ChatParams.push_back( make_pair(placeStr,STRING_MANAGER::place) );
				if ( !place )
				{
					ret = false;
					MISLOGERROR1("invalid place '%s'",script[2].c_str());
				}
				else
					_Place = place->getId();
			}
			return ret;
		}
	}
	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow )
	{
	STL_ALLOC_CONTEXT
		if ( event.Type == CMissionEvent::Kill )
		{
			CMissionEventKill & eventSpe = (CMissionEventKill&)event;
			CCreature * c = CreatureManager.getCreature( event.TargetEntity );
			if ( !c )
			{
				LOGMISSIONSTEPERROR("kill_fauna : invalid creature " + toString(event.TargetEntity.getIndex()));
			}
			else if ( _SubSteps[subStepIndex].Sheet == c->getType() )
			{
				if ( _Place != 0xFFFF )
				{
					float gooDistance;
					const CPlace * stable = NULL;
					std::vector<const CPlace *> places;
					const CRegion * region = NULL;
					const CContinent * continent = NULL;
					if ( !CZoneManager::getInstance().getPlace( c->getState().X, c->getState().Y, gooDistance, &stable, places, &region , &continent ) )
						return 0;

					if ( region && region->getId() == _Place )
					{
						LOGMISSIONSTEPSUCCESS("kill_fauna");
						return 1;
					}
					
					for ( uint i = 0; i < places.size(); i++ )
					{
						if ( places[i] && places[i]->getId() == _Place )
						{
							LOGMISSIONSTEPSUCCESS("kill_fauna");
							return 1;
						}
					}
					return 0;
				}
				else
				{
					LOGMISSIONSTEPSUCCESS("kill_fauna");
					return 1;
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
			ret[i] = _SubSteps[i].Quantity;
		}
	}

	virtual void getTextParams( uint & nbSubSteps,const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates)
	{
		static const std::string stepText = "MIS_KILL_FAUNA_";
		static const std::string stepTextLoc = "MIS_KILL_FAUNA_LOC_";
		nlassert( _SubSteps.size() == subStepStates.size() );
		for ( uint i  = 0; i < subStepStates.size(); i++ )
		{
			if( subStepStates[i] != 0 )
			{
				nbSubSteps++;
				retParams.push_back(STRING_MANAGER::TParam());
				retParams.back().Type = STRING_MANAGER::creature_model;
				retParams.back().SheetId = _SubSteps[i].Sheet;
				
				retParams.push_back(STRING_MANAGER::TParam());
				retParams.back().Type = STRING_MANAGER::integer;
				retParams.back().Int = subStepStates[i];
			}
		}
		if ( _Place != 0xFFFF )
		{
			STRING_MANAGER::TParam param;
			param.Type = STRING_MANAGER::place;
			CPlace * place = CZoneManager::getInstance().getPlaceFromId(_Place);
			if ( !place )
			{
				MISLOG("sline:%u ERROR : kill_fauna : Invalid place %u", _SourceLine, _Place);
			}
			else
			{
				param.Identifier = place->getName();
				retParams.push_back(param);
			}
			textPtr = &stepTextLoc;
		}
		else
			textPtr = &stepText;
	}

	std::vector< CSubStep > _SubSteps;
	uint16					_Place;

	MISSION_STEP_GETNEWPTR(CMissionStepKillFauna)
};
MISSION_REGISTER_STEP(CMissionStepKillFauna,"kill_fauna");


// ----------------------------------------------------------------------------
class CMissionStepKillRace : public IMissionStepTemplate
{
	struct CSubStep
	{
		EGSPD::CPeople::TPeople	Race;
		uint16				Quantity;
	};
	virtual bool	buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData )
	{
		_SourceLine = line;
		_Place = 0xFFFF;
		bool ret = true;
		if ( script.size() < 2 || script.size() > 3)
		{
			MISLOGSYNTAXERROR("<race> <quantity> *[; <race> <quantity>] [:<place>]");
			return false;
		}
		else
		{
			std::vector< std::string > subs;
			NLMISC::splitString( script[1],";", subs );
			_SubSteps.reserve(subs.size());
			for ( uint i = 0; i < subs.size(); i++ )
			{
				std::vector< std::string > args;
				CMissionParser::tokenizeString( subs[i]," \t", args );
				if ( args.size() != 2 )
				{
					MISLOGSYNTAXERROR("<race> <quantity> *[; <race> <quantity>] [:<place>]");
					return false;
				}
				missionData.ChatParams.push_back( make_pair(args[0],STRING_MANAGER::race) );
				CSubStep subStep;
				subStep.Race = EGSPD::CPeople::fromString( args[0] );
				if ( subStep.Race == EGSPD::CPeople::EndPeople )
				{
					ret = false;
					MISLOGERROR1("invalid race '%s'", args[0].c_str());
				}
				subStep.Quantity = atoi( args[1].c_str() );
				_SubSteps.push_back( subStep );
			}
			if ( script.size() == 3 )
			{
				string placeStr = CMissionParser::getNoBlankString( script[2] );
				missionData.ChatParams.push_back( make_pair(placeStr,STRING_MANAGER::place) );
				CPlace * place = CZoneManager::getInstance().getPlaceFromName( placeStr );
				if ( !place )
				{
					ret = false;
					MISLOGERROR1("invalid place '%s'", script[2].c_str());
				}
				else
					_Place = place->getId();
			}
			return ret;
		}
	}
	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow )
	{
	STL_ALLOC_CONTEXT
		if ( event.Type == CMissionEvent::Kill )
		{
			CMissionEventKill & eventSpe = (CMissionEventKill&)event;
			CCreature * c = CreatureManager.getCreature( event.TargetEntity );
			if ( !c )
			{
				LOGMISSIONSTEPERROR("kill_race : invalid creature " + toString(event.TargetEntity.getIndex()));
			}
			else if ( _SubSteps[subStepIndex].Race == c->getRace() )
			{
				if ( _Place != 0xFFFF )
				{
					float gooDistance;
					const CPlace * stable = NULL;
					std::vector<const CPlace *> places;
					const CRegion * region = NULL;
					const CContinent * continent = NULL;
					if ( !CZoneManager::getInstance().getPlace( c->getState().X, c->getState().Y, gooDistance, &stable, places, &region , &continent ) )
						return 0;
					if ( continent && continent->getId() == _Place )
					{
						LOGMISSIONSTEPSUCCESS("kill_race");
						return 1;
					}
					if ( region && region->getId() == _Place )
					{
						LOGMISSIONSTEPSUCCESS("kill_race");
						return 1;
					}
					for ( uint i = 0; i < places.size(); i++ )
					{
						if ( places[i] && places[i]->getId() == _Place )
						{
							LOGMISSIONSTEPSUCCESS("kill_race");
							return 1;
						}
					}
					return 0;
				}
				else
				{
					LOGMISSIONSTEPSUCCESS("kill_race");
					return 1;
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
			ret[i] = _SubSteps[i].Quantity;
		}
	}

	virtual void getTextParams( uint & nbSubSteps, const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates)
	{
		static const std::string stepText = "MIS_KILL_RACE_";
		static const std::string stepTextLoc = "MIS_KILL_RACE_LOC_";

		nlassert( _SubSteps.size() == subStepStates.size() );
		for ( uint i  = 0; i < subStepStates.size(); i++ )
		{
			if( subStepStates[i] != 0 )
			{
				nbSubSteps++;
				retParams.push_back(STRING_MANAGER::TParam());
				retParams.back().Type = STRING_MANAGER::race;
				retParams.back().Enum = (uint)_SubSteps[i].Race;
			
				retParams.push_back(STRING_MANAGER::TParam());
				retParams.back().Type = STRING_MANAGER::integer;
				retParams.back().Int = subStepStates[i];
			}
		}
		if ( _Place != 0xFFFF )
		{
			STRING_MANAGER::TParam param;
			param.Type = STRING_MANAGER::place;
			CPlace * place = CZoneManager::getInstance().getPlaceFromId(_Place);
			if ( !place )
			{
				MISLOG("sline:%u ERROR : kill_race : Invalid place %u", _SourceLine, _Place);
			}
			else
			{
				param.Identifier = place->getName();
				retParams.push_back(param);
			}
			textPtr = &stepTextLoc;
		}
		else
			textPtr = &stepText;
	}
	
	std::vector< CSubStep > _SubSteps;
	uint16					_Place;

	MISSION_STEP_GETNEWPTR(CMissionStepKillRace)
};
MISSION_REGISTER_STEP(CMissionStepKillRace,"kill_race");


// ----------------------------------------------------------------------------
class CMissionStepKillNpc : public IMissionStepTemplate
{
	struct CSubStep
	{
		TAIAlias	Alias;
//		NLMISC::TStringId	NpcName;
	};
	virtual bool	buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData )
	{
		_SourceLine = line;
		bool ret = true;
		if ( script.size() < 2 || script.size() > 3)
		{
			MISLOGSYNTAXERROR("<npc_name>*[; <npc_name>]");
			return false;
		}
		else
		{
			std::vector< std::string > subs;
			NLMISC::splitString( script[1],";", subs );
			_SubSteps.reserve(subs.size());
			for ( uint i = 0; i < subs.size(); i++ )
			{
				CSubStep subStep;
				subStep.Alias = CAIAliasTranslator::Invalid;
				if ( !CMissionParser::parseBotName(subs[i],subStep.Alias,missionData) )
					ret = false;
				_SubSteps.push_back( subStep );
			}
			return ret;
		}
	}
	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow )
	{
	STL_ALLOC_CONTEXT
		if ( event.Type == CMissionEvent::Kill )
		{
			CMissionEventKill & eventSpe = (CMissionEventKill&)event;
			CCreature * c = CreatureManager.getCreature( event.TargetEntity );
			if ( !c )
			{
				LOGMISSIONSTEPERROR("kill_npc : invalid creature " + toString(event.TargetEntity.getIndex()));
			}
			else
			{
				if ( _SubSteps[subStepIndex].Alias != CAIAliasTranslator::Invalid )
				{
					if ( _SubSteps[subStepIndex].Alias == c->getAlias() )
					{
						LOGMISSIONSTEPSUCCESS("kill_npc");
						return 1;
					}
				}
				else if (  event.TargetEntity == giverRow )
				{
					LOGMISSIONSTEPSUCCESS("kill_npc");
					return 1;
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
			ret[i] = 1;
		}
	}

	virtual void getTextParams( uint & nbSubSteps, const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates)
	{
		static const std::string stepText = "MIS_KILL_NPC_";
		textPtr = &stepText;
		nlassert( _SubSteps.size() == subStepStates.size() );
		for ( uint i  = 0; i < subStepStates.size(); i++ )
		{
			if( subStepStates[i] != 0 )
			{
				nbSubSteps++;
				retParams.push_back(STRING_MANAGER::TParam());
				retParams.back().Type = STRING_MANAGER::bot;
				if ( _SubSteps[i].Alias != CAIAliasTranslator::Invalid )
					retParams.back().Int = _SubSteps[i].Alias;
				else
					retParams.back().Identifier = "giver";
			}
		}
	}
	
	std::vector< CSubStep > _SubSteps;

	MISSION_STEP_GETNEWPTR(CMissionStepKillNpc)
};
MISSION_REGISTER_STEP(CMissionStepKillNpc,"kill_npc");


// ----------------------------------------------------------------------------
class CMissionStepKillGroup : public IMissionStepTemplate
{
	struct CSubStep
	{
		TAIAlias	Alias;
	};
	
	virtual bool	buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData )
	{
		_SourceLine = line;
		bool ret = true;
		if ( script.size() != 2 )
		{
			MISLOGSYNTAXERROR("<group_name>");
			return false;
		}

		std::vector< std::string > subs;
		NLMISC::splitString( script[1],";", subs );
		
		if ( subs.size() != 1 )
		{
			MISLOGSYNTAXERROR("<group_name>");
			return false;
		}

		_SubSteps.reserve(1);
		
		{
 			CMissionParser::removeBlanks( subs[0] );
			std::vector< TAIAlias > aliases;
			CAIAliasTranslator::getInstance()->getGroupAliasesFromName( subs[0],aliases );
			if ( aliases.empty() )
			{
				ret = false;
				MISLOGERROR1("invalid group %s", subs[0].c_str());
			}

			for ( uint j = 0; j < aliases.size(); j++)
			{
				CSubStep subStep;
				subStep.Alias = aliases[j];
				_SubSteps.push_back( subStep );

			}
			Target = subs[0];
		}
		return ret;
	}
	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow )
	{
	STL_ALLOC_CONTEXT
		if ( event.Type == CMissionEvent::KillGroup )
		{
			CMissionEventKillGroup & eventSpe = (CMissionEventKillGroup&)event;
			{
				if ( _SubSteps[subStepIndex].Alias == eventSpe.Alias )
				{
					LOGMISSIONSTEPSUCCESS("kill_group");
					return 1;
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
			ret[i] = 1;
		}
	}
	
	virtual void getTextParams( uint & nbSubSteps, const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates)
	{
		/// overloaded text in script

		static const std::string stepText = "MIS_KILL_GROUP";
		textPtr = &stepText;
		retParams.push_back(STRING_MANAGER::TParam(STRING_MANAGER::bot_name));
		retParams.back().Type = STRING_MANAGER::bot_name;
		retParams.back().Identifier = Target;

	}

	bool checkTextConsistency()
	{
		return true;
	}
	
	std::vector< CSubStep > _SubSteps;
	std::string Target;

	MISSION_STEP_GETNEWPTR(CMissionStepKillGroup)
};
MISSION_REGISTER_STEP(CMissionStepKillGroup,"kill_group");


// ----------------------------------------------------------------------------
class CMissionStepKillFaction : public IMissionStepTemplate
{
	virtual bool	buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData )
	{
		_SourceLine = line;
		_Place = 0xFFFF;
		bool ret = true;
		if ( script.size() < 2 || script.size() > 3)
		{
			MISLOGSYNTAXERROR("<faction> <quantity> [: <place>]");
			return false;
		}
	
		std::vector< std::string > args;
		CMissionParser::tokenizeString( script[1]," \t", args );
		if ( args.size() != 2 )
		{
			MISLOGSYNTAXERROR("<faction> <quantity> [: <place>]");
			return false;
		}

		missionData.ChatParams.push_back( make_pair(args[0], STRING_MANAGER::faction) );
		_Faction = CStaticFames::getInstance().getFactionIndex(args[0]);
		if ( _Faction == CStaticFames::INVALID_FACTION_INDEX )
		{
			ret = false;
			MISLOGERROR1("invalid faction '%s'", args[0].c_str());
		}
		_Quantity = atoi( args[1].c_str() );

		if ( script.size() == 3 )
		{
			string placeStr = CMissionParser::getNoBlankString( script[2] );
			CPlace * place = CZoneManager::getInstance().getPlaceFromName( placeStr );
			missionData.ChatParams.push_back( make_pair(placeStr,STRING_MANAGER::place) );
			if ( !place )
			{
				ret = false;
				MISLOGERROR1("invalid place '%s'", script[2].c_str());
			}
			else
				_Place = place->getId();
		}
		return ret;
	}
	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow )
	{
	STL_ALLOC_CONTEXT
		if ( event.Type == CMissionEvent::Kill )
		{
			CMissionEventKill & eventSpe = (CMissionEventKill&)event;
			CCreature * c = CreatureManager.getCreature( event.TargetEntity );
			if ( !c )
			{
				LOGMISSIONSTEPERROR("kill_faction : invalid creature " + toString(event.TargetEntity.getIndex()));
			}
			else if ( c->getForm()->getFaction() == _Faction )
			{
				if ( _Place != 0xFFFF )
				{
					float gooDistance;
					const CPlace * stable = NULL;
					std::vector<const CPlace *> places;
					const CRegion * region = NULL;
					const CContinent * continent = NULL;
					if ( !CZoneManager::getInstance().getPlace( c->getState().X, c->getState().Y, gooDistance, &stable, places, &region , &continent ) )
						return 0;
					if ( continent && continent->getId() == _Place )
					{
						LOGMISSIONSTEPSUCCESS("kill_faction");
						return 1;
					}
					if ( region && region->getId() == _Place )
					{
						LOGMISSIONSTEPSUCCESS("kill_faction");
						return 1;
					}
					for ( uint i = 0; i < places.size(); i++ )
					{
						if ( places[i] && places[i]->getId() == _Place )
						{
							LOGMISSIONSTEPSUCCESS("kill_faction");
							return 1;
						}
					}
					return 0;
				}
				else
				{
					LOGMISSIONSTEPSUCCESS("kill_faction");
					return 1;
				}
			}
		}
		return 0;
	}

	void getInitState( std::vector<uint32>& ret )
	{
		ret.clear();
		ret.resize( 1 );
		ret.back() = _Quantity;
	}

	virtual void getTextParams( uint & nbSubSteps,const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates)
	{
		static const std::string stepText = "MIS_KILL_FACTION";
		static const std::string stepTextLoc = "MIS_KILL_FACTION_LOC";
		nlassert( subStepStates.size() == 1);

		nbSubSteps = 1;
		retParams.push_back(STRING_MANAGER::TParam(STRING_MANAGER::faction));
		retParams.back().Enum = _Faction;
		retParams.push_back(STRING_MANAGER::TParam(STRING_MANAGER::integer, sint32(_Quantity)));
				
		if ( _Place != 0xFFFF )
		{
			STRING_MANAGER::TParam param;
			param.Type = STRING_MANAGER::place;
			CPlace * place = CZoneManager::getInstance().getPlaceFromId(_Place);
			if ( !place )
			{
				MISLOG("sline:%u ERROR : kill_faction : invalid place %u", _SourceLine, _Place);
			}
			else
			{
				param.Identifier = place->getName();
				retParams.push_back(param);
			}
			textPtr = &stepTextLoc;
		}
		else
			textPtr = &stepText;
		
	}

	/// Faction as defined in CStaticFame
	uint32		_Faction;
	uint16		_Quantity;
	uint16		_Place;

	MISSION_STEP_GETNEWPTR(CMissionStepKillFaction)
};
MISSION_REGISTER_STEP(CMissionStepKillFaction,"kill_faction");


// ----------------------------------------------------------------------------
class CMissionStepKillByName : public IMissionStepTemplate
{
	bool				GroupKill;
	std::set<TAIAlias>	Aliases;
	string				TargetName;
	uint16				Quantity;
	uint16				Place;
	virtual bool	buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData )
	{
		_SourceLine = line;

		GroupKill = false;
		Place = 0xFFFF;
		if ( script.size() != 2 && script.size() != 3 )
		{
			MISLOGSYNTAXERROR("<npc_name> <quantity>");
			return false;
		}
		std::vector< std::string > args;
		CMissionParser::tokenizeString( script[1]," \t", args );
		if ( args.size() != 2 )
		{
			MISLOGSYNTAXERROR("<npc_name> <quantity>");
			return false;
		}

		TargetName = args[0];
		CAIAliasTranslator::getInstance()->getNPCAliasesFromNameInSet( args[0], Aliases );
		if ( Aliases.empty() )
		{
			// try to look for a group alias
			GroupKill = true;
			vector<TAIAlias> va;
			CAIAliasTranslator::getInstance()->getGroupAliasesFromName( args[0], va );
			if ( va.empty() )
			{
				MISLOGERROR1("invalid name '%s'",args[0].c_str());
				return false;
			}

			Aliases.insert(va.begin(), va.end());
		}
		Quantity = (uint16) atoi( args[1].c_str() );
		if ( Quantity == 0 )
		{
			MISLOGERROR("invalid quantity 0");
			return false;
		}

		missionData.ChatParams.push_back( make_pair( args[0], STRING_MANAGER::bot ) );

		if ( script.size() == 3 )
		{
			string placeStr = CMissionParser::getNoBlankString( script[2] );
			CPlace * place = CZoneManager::getInstance().getPlaceFromName( placeStr );
			missionData.ChatParams.push_back( make_pair(placeStr,STRING_MANAGER::place) );
			if ( !place )
			{
				MISLOGERROR1("invalid place '%s'", script[2].c_str());
				return false;
			}
			Place = place->getId();
		}
		return true;
	}
	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow )
	{
	STL_ALLOC_CONTEXT
		if ( event.Type == CMissionEvent::Kill )
		{
			CMissionStepKillByName & eventSpe = (CMissionStepKillByName&)event;
			CCreature * c = CreatureManager.getCreature( event.TargetEntity );
			if ( !c )
			{
				LOGMISSIONSTEPERROR("kill_npc_by_name : invalid creature " + toString(event.TargetEntity.getIndex()));
			}
			else
			{
				if ( (GroupKill && Aliases.find(c->getAIGroupAlias()) != Aliases.end())
					|| Aliases.find( c->getAlias() ) != Aliases.end() )
				{
					if ( Place != 0xFFFF )
					{
						float gooDistance;
						const CPlace * stable = NULL;
						std::vector<const CPlace *> places;
						const CRegion * region = NULL;
						const CContinent * continent = NULL;
						if ( !CZoneManager::getInstance().getPlace( c->getState().X, c->getState().Y, gooDistance, &stable, places, &region , &continent ) )
							return 0;
						if ( continent && continent->getId() == Place )
						{
							LOGMISSIONSTEPSUCCESS("kill_npc_by_name");
							return 1;
						}
						if ( region && region->getId() == Place )
						{
							LOGMISSIONSTEPSUCCESS("kill_npc_by_name");
							return 1;
						}
						for ( uint i = 0; i < places.size(); i++ )
						{
							if ( places[i] && places[i]->getId() == Place )
							{
								LOGMISSIONSTEPSUCCESS("kill_npc_by_name");
								return 1;
							}
						}
						return 0;
					}
					else
					{
						LOGMISSIONSTEPSUCCESS("kill_npc_by_name");
						return 1;
					}
				}
			}
		}
		return 0;
	}
	
	void getInitState( std::vector<uint32>& ret )
	{
		ret.clear();
		ret.resize( 1 );
		ret[0] = Quantity;
	}

	virtual void getTextParams( uint & nbSubSteps, const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates)
	{
		static const std::string stepTextNoLoc = "MIS_KILL_NPC_BY_NAME";
		static const std::string stepTextLoc = "MIS_KILL_NPC_BY_NAME_LOC";
		if ( Place != 0xFFFF )
			retParams.resize(3);
		else
			retParams.resize(2);
		retParams[0].Type = STRING_MANAGER::bot_name;
		retParams[0].Identifier = TargetName;
		retParams[1].Type = STRING_MANAGER::integer;
		nlassert( subStepStates.size() == 1 )
		retParams[1].Int = subStepStates[0];
		if ( Place != 0xFFFF )
		{
			CPlace * place = CZoneManager::getInstance().getPlaceFromId( Place );
			if ( !place )
			{
				MISLOG("sline:%u ERROR : kill_npc_by_name : invalid place %u", _SourceLine, Place);
			}
			else
			{
				retParams[2].Type = STRING_MANAGER::place;
				retParams[2].Identifier = place->getName();
				textPtr = &stepTextLoc;
			}
		}
		else
			textPtr = &stepTextNoLoc;

	}

	MISSION_STEP_GETNEWPTR(CMissionStepKillByName)
};
MISSION_REGISTER_STEP(CMissionStepKillByName,"kill_npc_by_name");
