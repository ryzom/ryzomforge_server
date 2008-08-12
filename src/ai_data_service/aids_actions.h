/** \file aids_actions.h
 *
 * $Id: aids_actions.h,v 1.4 2004/03/01 19:19:03 lecroart Exp $
 */



#ifndef RYAI_AIDS_ACTIONS_H
#define RYAI_AIDS_ACTIONS_H

#include "ai_share/ai_actions.h"
#include "ai_manager.h"
#include <vector>

class CAIDSActions: public CAIActions::IExecutor
{
public:
	//----------------------------------------------------------------------------
	// init & release
	
	static void init() 
	{
		if (Instance==NULL)
			Instance=new CAIDSActions;
		CAIActions::init(Instance); 
	}
	static void release()
	{
		if (Instance!=NULL)
		{
			CAIActions::release(); 
			delete Instance;
			Instance=NULL;
		}
	}
	
	//----------------------------------------------------------------------------
	// inheritted virtual interface

	virtual void openFile(const std::string &fileName);
	virtual void closeFile(const std::string &fileName);
	virtual void begin(const std::string &contextName);
	virtual void end(const std::string &contextName);
	virtual void execute(uint64 action,const std::vector <CAIActions::CArg> &args);

	virtual void	begin(uint32 context)	{}
	virtual void	end(uint32 context)	{}

	//----------------------------------------------------------------------------
	// public singleton data

	static uint CurrentManager;

private:
	//----------------------------------------------------------------------------
	// This is a singleton class so make constructor private
	CAIDSActions() {}
	~CAIDSActions() {}

	//----------------------------------------------------------------------------
	// the singleton class instance
	static CAIDSActions *Instance;
};


#endif

