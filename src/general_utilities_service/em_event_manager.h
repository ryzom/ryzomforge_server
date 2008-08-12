/** \file em_event_manager.h
 *
 * $id$
 *
 */

#ifndef EM_EVENT_MANAGER_H
#define EM_EVENT_MANAGER_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "nel/misc/sstring.h"


//-----------------------------------------------------------------------------
// advanced class declarations
//-----------------------------------------------------------------------------

class CFileDescriptionContainer;


//-----------------------------------------------------------------------------
// class CEventManager
//-----------------------------------------------------------------------------

class CEventManager
{
public:
	// get hold of the singleton instance
	static CEventManager* getInstance();

public:
	// try to log in to a shard
	virtual void login(const NLMISC::CSString& shardName,const NLMISC::CSString& userId,const NLMISC::CSString& password)=0;

	// upload an event to a shard
	virtual void upload(const NLMISC::CSString& shardName,const NLMISC::CSString& eventName,const CFileDescriptionContainer& fdc,const NLMISC::CVectorSString& fileBodies)=0;

	// tell the shard to start the event running (if it's not already)
	virtual void startEvent(const NLMISC::CSString& shardName)=0;

	// tell the shard to stop the current event (if there is one running)
	virtual void stopEvent(const NLMISC::CSString& shardName)=0;

	// attempt to restart a shard (shut down and re-launch)
	virtual void updateTools()=0;

	// send a history request to a given shard
	virtual void peekInstalledEvent(const NLMISC::CSString& shardName) const=0;

	// get the set of shard names for the shards we're logged into
	virtual void getShards(NLMISC::CVectorSString& shardNames) const=0;
};


//-----------------------------------------------------------------------------
#endif
