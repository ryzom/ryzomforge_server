/** \file mission_step_guild.cpp
 * <File description>
 *
 * $Id: mission_step_guild.cpp,v 1.12 2007/08/02 12:24:48 dailyserver Exp $
 */



#include "stdpch.h"
#include "nel/misc/sstring.h"
#include "mission_manager/mission_manager.h"
#include "mission_step_template.h"
#include "mission_log.h"
#include "mission_manager/mission_parser.h"
#include "mission_manager/ai_alias_translator.h"
#include "player_manager/character.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"
#include "team_manager/team_manager.h"

#include "server_share/msg_ai_service.h"

#include "nel/misc/algo.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

// ----------------------------------------------------------------------------
class CMissionStepGainChargePoint : public IMissionStepTemplate
{
	uint32	_ChargePoints;
		
	virtual bool	buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData )
	{
		_SourceLine = line;
		if( script.size() != 2 )
		{
			MISLOGSYNTAXERROR("<points>");
			return false;
		}
		_ChargePoints = uint32(atoi( script[1].c_str() ));
		if ( _ChargePoints == 0 )
		{
			MISLOGERROR("charge points = 0");
			return false;
		}
		return true;
	}

	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow )
	{
		// the event contains the guild charge points
		if( event.Type == CMissionEvent::ChargePoints )
		{
			CMissionEventChargePoints & eventSpe = (CMissionEventChargePoints &) event;
			LOGMISSIONSTEPSUCCESS("charge_point");
			return eventSpe.Points;
		}
		return 0;
	}
	
	void getInitState( std::vector<uint32>& ret )
	{
		ret.clear();
		ret.resize( 1 );
		ret[0] = _ChargePoints;
	}

	virtual void getTextParams( uint & nbSubSteps,const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates)
	{
		static const std::string stepText = "MIS_CHARGE_POINT";
		textPtr = &stepText;
		nlassert( subStepStates.size() == 1);
		retParams.push_back(STRING_MANAGER::TParam());
		retParams.back().Type = STRING_MANAGER::integer;
		retParams.back().Int = _ChargePoints;

		retParams.push_back(STRING_MANAGER::TParam());
		retParams.back().Type = STRING_MANAGER::integer;
		retParams.back().Int = 100 - sint32( ( 100.0f * subStepStates.back() ) / _ChargePoints );
	}
	
	
	bool checkTextConsistency()
	{
		return true;
	}

	MISSION_STEP_GETNEWPTR(CMissionStepGainChargePoint)
};
MISSION_REGISTER_STEP(CMissionStepGainChargePoint,"charge_point")


// ----------------------------------------------------------------------------
class CMissionStepGainOutpostControl : public IMissionStepTemplate
{
	std::string OutpostName;
	virtual bool	buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData )
	{
		_SourceLine = line;
		if( script.size() != 2)
		{
			MISLOGSYNTAXERROR("<outpost_name>");
			return false;
		}

		OutpostName = CSString(script[1]).strip();
		return true;
	}
	
	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow )
	{
		// the event contains the guilsd charge points
		if( event.Type == CMissionEvent::OutpostGain )
		{
			LOGMISSIONSTEPSUCCESS("gain_control");
			return 1;	
		}
		return 0;
	}
	
	void getInitState( std::vector<uint32>& ret )
	{
		ret.clear();
		ret.resize( 1 );
		ret[0] = 1;
	}
	
	virtual void getTextParams( uint & nbSubSteps,const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates)
	{
		static const std::string stepText = "MIS_GAIN_CONTROL";
		textPtr = &stepText;
		nlassert( subStepStates.size() == 1);
		retParams.push_back(STRING_MANAGER::TParam());
		retParams.back().Type = STRING_MANAGER::place;
		retParams.back().Identifier = OutpostName;
	}
	
	
	bool checkTextConsistency()
	{
		return true;
	}

	MISSION_STEP_GETNEWPTR(CMissionStepGainOutpostControl)
};
MISSION_REGISTER_STEP(CMissionStepGainOutpostControl,"gain_control")

