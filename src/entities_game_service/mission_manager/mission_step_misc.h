/** \file mission_action.h
 * <File description>
 *
 * $Id: mission_step_misc.h,v 1.4 2005/07/12 09:49:21 berenguier Exp $
 */



#ifndef RY_MISSION_STEP_MISC_H
#define RY_MISSION_STEP_MISC_H

#include "mission_step_template.h"

/*
 * 
 */
class CMissionStepHandleCreate : public IMissionStepTemplate
{
	TAIAlias	GroupAlias;
	uint32		DespawnTime;
	
	virtual bool buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData );
	void onActivation(CMission* instance,uint32 stepIndex,std::list< CMissionEvent * > & eventList);
	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow );
	void getInitState( std::vector<uint32>& ret );
	virtual void getTextParams( uint & nbSubSteps,const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates);
	
	MISSION_STEP_GETNEWPTR(CMissionStepHandleCreate)
};

/*
 *
 */
class CMissionStepHandleRelease : public IMissionStepTemplate
{
	TAIAlias	GroupAlias;
	
	virtual bool buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData );
	void onActivation(CMission* instance,uint32 stepIndex,std::list< CMissionEvent * > & eventList);
	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow );
	void getInitState( std::vector<uint32>& ret );
	virtual void getTextParams( uint & nbSubSteps,const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates);
	
	MISSION_STEP_GETNEWPTR(CMissionStepHandleRelease)
};

#endif
