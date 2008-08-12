/** \file mission_step_queue.h
 * <File description>
 *
 * $Id: mission_step_queue.h,v 1.3 2005/07/12 09:50:28 berenguier Exp $
 */



#ifndef RY_MISSION_STEP_AI_H
#define RY_MISSION_STEP_AI_H

#include "mission_step_template.h"
#include "nel/misc/smart_ptr.h"

/***************************************************************************************************
Steps linked with waiting queues
	- queue_start	: create a queue or insert player in queue
	- queue_end 	: remove player from queue, next waiting player can validate the queue_start step
***************************************************************************************************/

/**
 * class used for queue start steps
 * \author David Fleury
 * \author Nevrax France
 * \date 2005
 */
class CMissionStepQueueStart : public IMissionStepTemplate, public NLMISC::CRefCount
{
public:
	virtual bool buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData );
	
	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow );
	
	void getInitState( std::vector<uint32>& ret );
	
	virtual void getTextParams( uint & nbSubSteps,const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates);

	virtual uint32	sendStepText(CCharacter * user,const std::vector<uint32>& stepStates,const NLMISC::CEntityId & giver);
	
	virtual void onActivation(CMission* inst,uint32 stepIndex, std::list< CMissionEvent * > & eventList);

	MISSION_STEP_GETNEWPTR(CMissionStepQueueStart)

	std::string QueueName;
	uint32		Timer; // in ticks

private:
	uint16		_NbWaiters;
	uint16		_NbOnlineWaiters;
	bool		_HasPlayerInCriticalZone;
};

typedef NLMISC::CRefPtr<CMissionStepQueueStart> CMissionStepQueueStartRefPtr;

/**
 * class used for queue end steps
 * \author David Fleury
 * \author Nevrax France
 * \date 2005
 */
class CMissionStepQueueEnd : public IMissionStepTemplate
{
public:

	virtual bool buildStep( uint32 line, const std::vector< std::string > & script, CMissionGlobalParsingData & globalData, CMissionSpecificParsingData & missionData );
	
	uint processEvent( const TDataSetRow & userRow, const CMissionEvent & event,uint subStepIndex,const TDataSetRow & giverRow );
	
	void getInitState( std::vector<uint32>& ret );
	
	virtual void getTextParams( uint & nbSubSteps,const std::string* & textPtr,TVectorParamCheck& retParams, const std::vector<uint32>& subStepStates)
	{}
	
	virtual void onActivation(CMission* inst,uint32 stepIndex, std::list< CMissionEvent * > & eventList);

	virtual bool isDisplayed() const { return false; }

	std::string QueueName;
		
	MISSION_STEP_GETNEWPTR(CMissionStepQueueEnd)	
};

#endif // RY_MISSION_STEP_AI_H //
