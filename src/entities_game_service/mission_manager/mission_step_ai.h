/** \file mission_action.h
 * <File description>
 *
 * $Id: mission_step_ai.h,v 1.3 2005/07/12 09:47:43 berenguier Exp $
 */



#ifndef RY_MISSION_STEP_AI_H
#define RY_MISSION_STEP_AI_H

#include "mission_step_template.h"

/***************************************************************************************************
Steps linked with AI concepts/events
	- escort		: escort a bot 
	- wait_message	: wait for a specific AI event
***************************************************************************************************/

class CMissionStepEscort : public IMissionStepTemplate
{

	std::vector<TAIAlias>	Aliases;
	bool					SaveAll;
		
	virtual bool	buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData );

	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow );

	void getInitState( std::vector<uint32>& ret );

	virtual void getTextParams( uint & nbSubSteps,const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates);

	virtual void onActivation(CMission* inst,uint32 stepIndex, std::list< CMissionEvent * > & eventList);

	virtual void getEscortGroups( std::vector< TAIAlias > & groups );
	
	virtual bool checkEscortFailure( bool groupWiped );

	bool checkTextConsistency();

	MISSION_STEP_GETNEWPTR(CMissionStepEscort)
	
};


class CMissionStepAIMsg : public IMissionStepTemplate
{
	std::string _Msg;

	virtual bool	buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData );

	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow );

	void getInitState( std::vector<uint32>& ret );

	virtual void getTextParams( uint & nbSubSteps,const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates)
	{}

	bool checkTextConsistency();

	MISSION_STEP_GETNEWPTR(CMissionStepAIMsg)
};


#endif
