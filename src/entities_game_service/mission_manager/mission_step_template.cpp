
/** \file mission_step_template.cpp
 * <File description>
 *
 * $Id: mission_step_template.cpp,v 1.29 2007/05/09 15:33:36 boucher Exp $
 */



#include "stdpch.h"
#include "mission_step_template.h"
#include "mission_log.h"
#include "mission_manager/mission_template.h"
#include "player_manager/character.h"
#include "mission_manager/mission_parser.h"
#include "player_manager/player.h"
#include "player_manager/player_manager.h"
#include "nel/misc/algo.h"

using namespace std;
using namespace NLMISC;

NL_INSTANCE_COUNTER_IMPL(IMissionStepTemplate);

std::vector< std::pair< std::string, IMissionStepTemplateFactory* > > * IMissionStepTemplateFactory::Entries;


void logMissionStep(uint32 line, const TDataSetRow & userRow, uint32 subStepIndex, const string &prefix, const string &stepNameAndParams)
{
	if (!VerboseMissions) return;
	string sTmp;
	sTmp = "sline:" + toString(line);
	CCharacter *c = PlayerManager.getChar(userRow);
	if (c != NULL)
		sTmp += " user:" + c->getId().toString();
	sTmp += " step:" + toString(subStepIndex);
	sTmp += " " + prefix + " : " + stepNameAndParams;
	MISLOG("%s", sTmp.c_str());
}



IMissionStepTemplate * IMissionStepTemplate::getCopy()
{
	IMissionStepTemplate * step = getNewPtr();
	for ( uint i = 0; i < _Actions.size(); i++ )
	{
		step->_Actions[i] = _Actions[i]->getCopy();
	}
	return step;
}// IMissionStepTemplate::getCopy

IMissionStepTemplate::~IMissionStepTemplate()
{
	for ( uint i = 0; i < _Actions.size(); i++ )
	{
		delete _Actions[i];
	}
}// IMissionStepTemplate::~IMissionStepTemplate

void IMissionStepTemplate::overrideTexts( const std::string & phraseId, const TVectorParamCheck & params , bool addDefaultParams)
{
	_OverridenText = phraseId;
	_AdditionalParams = params;
	_AddDefaultParams = addDefaultParams;
}//IMissionStepTemplate::OverrideTexts

void IMissionStepTemplate::setRoleplayText( const std::string & phraseId, const TVectorParamCheck & params)
{
	_RoleplayText = phraseId;
	_AdditionalParams = params;
}

bool IMissionStepTemplate::solveTextsParams( CMissionSpecificParsingData & missionData,CMissionTemplate * templ  )
{
	bool ret = true;
	for ( uint i = 0; i < _Actions.size(); i++ )
	{
		if ( !_Actions[i]->solveTextsParams(missionData) )
			ret = false;
	}
	if ( !CMissionParser::solveTextsParams( _SourceLine, _AdditionalParams,missionData ) )
		ret = false;
	return ret;
}// IMissionStepTemplate::solveTextsParams



uint32 IMissionStepTemplate::sendRpStepText(CCharacter * user,const std::vector<uint32>& stepStates,const NLMISC::CEntityId & giver)
{
	TVectorParamCheck params;
	string buffer;
	uint nbSteps = 0;
	const std::string* textPtr = NULL;

	if ( !_RoleplayText.empty() )
	{
		// build the param list
		getTextParams(nbSteps,(const std::string *&)textPtr,params,stepStates);

		params.reserve(params.size() + _AdditionalParams.size());
		params.insert(params.end(), _AdditionalParams.begin(), _AdditionalParams.end());
		if ( textPtr && !textPtr->empty() && (*textPtr)[textPtr->size()-1] == '_' )
		{
			buffer = _RoleplayText + "_";
			textPtr = &buffer;
		}
		else
			textPtr = &_RoleplayText;
	}
	
	if( !textPtr )
		return 0;

	// solve dynamic names
	CMissionParser::solveEntitiesNames(params,user->getEntityRowId(),giver);

	// if the text was generated, compute its suffix
	if ( !textPtr->empty() && (*textPtr)[textPtr->size()-1] == '_' )
	{
		std::string text = NLMISC::toString( "%s%u", textPtr->c_str(),nbSteps );
		return STRING_MANAGER::sendStringToClient( user->getEntityRowId(),text,params);
	}
	else
		return STRING_MANAGER::sendStringToClient( user->getEntityRowId(),*textPtr,params);

}// IMissionStepTemplate::sendRpStepText


uint32 IMissionStepTemplate::sendStepText(CCharacter * user,const std::vector<uint32>& stepStates,const NLMISC::CEntityId & giver)
{
	TVectorParamCheck params;
	string buffer;
	uint nbSteps = 0;
	const std::string* textPtr = NULL;

	// build the param list
	getTextParams(nbSteps,(const std::string *&)textPtr,params,stepStates);
	
	// If the text is overriden, add the overide parameters
	if ( !_OverridenText.empty() )
	{
		if ( _AddDefaultParams )
		{
			params.reserve(params.size() + _AdditionalParams.size());
			params.insert(params.end(), _AdditionalParams.begin(), _AdditionalParams.end());
			if ( textPtr && !textPtr->empty() && (*textPtr)[textPtr->size()-1] == '_' )
			{
				buffer = _OverridenText + "_";
				textPtr = &buffer;
			}
			else
				textPtr = &_OverridenText;
		}
		else
		{
			params = _AdditionalParams;
			textPtr = &_OverridenText;
		}

	}

	if( !textPtr )
		return 0;

	// solve dynamic names
	CMissionParser::solveEntitiesNames(params,user->getEntityRowId(),giver);

	// if the text was generated, compute its suffix
	if ( !textPtr->empty() && (*textPtr)[textPtr->size()-1] == '_' )
	{
//		if( !isAny() )
		{
			std::string text = NLMISC::toString( "%s%u", textPtr->c_str(),nbSteps );
			return STRING_MANAGER::sendStringToClient( user->getEntityRowId(),text,params);
		}
//		else
//		{
//			std::string text = NLMISC::toString( "%s%u", textPtr->c_str(),nbSteps );
//			SM_STATIC_PARAMS_1(paramsAnyOr, STRING_MANAGER::dyn_string_id);
//			paramsAnyOr[0].StringId = STRING_MANAGER::sendStringToClient( user->getEntityRowId(),text,params);
//			return STRING_MANAGER::sendStringToClient( user->getEntityRowId(),"MISSION_GOAL_STEP_ANY_OR",paramsAnyOr);
//		}
	}
	else
	{
//		if( !isAny() )
		{
			return STRING_MANAGER::sendStringToClient( user->getEntityRowId(),*textPtr,params);
		}
//		else
//		{
//			SM_STATIC_PARAMS_1(paramsAnyOr, STRING_MANAGER::dyn_string_id);
//			paramsAnyOr[0].StringId = STRING_MANAGER::sendStringToClient( user->getEntityRowId(),*textPtr,params);
//			return STRING_MANAGER::sendStringToClient( user->getEntityRowId(),"MISSION_GOAL_STEP_ANY_OR",paramsAnyOr);
//		}
	}
}// IMissionStepTemplate::sendStepText

void IMissionStepTemplate::addAction(IMissionAction * action)
{
	_Actions.push_back( action );
}// IMissionAction solveTextsParams

bool IMissionStepTemplate::checkPlayerGift( CMission* instance, CCharacter * user )
{
	nlwarning("<checkPlayerGift> Not implemented in this class");
	return false;
}// IMissionStepTemplate::checkPlayerGift


IMissionStepTemplate* IMissionStepTemplateFactory::buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData )
{
	for ( uint i = 0; i < Entries->size(); i++ )
	{
		if ( script[0] == (*Entries)[i].first )
		{
			IMissionStepTemplate * ret = (*Entries)[i].second->instanciate();
			if ( !ret )
			{
				nlerror("BUG IN STEP FACTORY : BAD INIT CODE");
				return NULL;
			}
			if ( !ret->buildStep(line, script, globalData, missionData) )
			{
				MISLOGERROR("cant build step");
				delete ret;
				return NULL;
			}
			return ret;
		}
	}
	return NULL;
}// IMissionStepTemplateFactory buildStep
	

void IMissionStepTemplateFactory::init()
{
	NL_ALLOC_CONTEXT(MST_INIT);
	if ( ! Entries )
		Entries = new std::vector< std::pair< std::string, IMissionStepTemplateFactory* > >;
}// IMissionStepTemplate init

