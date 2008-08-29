/** \file ai_logic_action_.h
 *
 * $Id: ai_logic_action.h,v 1.23 2006/09/14 17:06:18 cado Exp $
 */



#ifndef RYAI_LOGIC_ACTION_H
#define RYAI_LOGIC_ACTION_H

#include "alias_tree_owner.h"
#include "game_share/r2_basic_types.h"

class IAIEvent;

class CAIEventReaction;
class CGroupFamily;
class CGroup;
class CStateInstance;

//---------------------------------------------------------------------------------
// CAIEventReactionAction
//---------------------------------------------------------------------------------
// this is the base class for action types that can be used to process events for
// teams and other entiites

class	IAILogicAction
	:	public NLMISC::CRefCount
{
public:
	typedef	NLMISC::CSmartPtr<IAILogicAction> TSmartPtr;

	// NOTE: ctor takes following form:
	// CLASS(const std::vector<std::string> &args, const std::vector<CAIEventReactionAction *> &subActions) 

	// note that actions are NOT responsible for deleting child actions
	virtual	~IAILogicAction()
	{};

	// this is the execute 'callback' for the action type.
	// NOTE: This code should be fast and compact as it may be called very large numbers of times
	// depending on the whim of the level designers
	// returns true on success, false on failure
	virtual bool executeAction		(CStateInstance *entity,const IAIEvent *event)=0;

	virtual	void addPropertyZone	(CTmpPropertyZone::TSmartPtr	zone)
	{}

	// attach a group family to the action if it supports it (assert otherwise)
	virtual void addGroupFamily(CGroupFamily *gf) { nlassert(0) }
};

// Code use by native functions and LogicAction
class CAILogicActionDssStartActHelper
{
public:	
	static void dssStartAct(TSessionId sessionId, uint32 actId);	
};

class CAILogicActionSitDownHelper
{
public:	
	static void sitDown(CGroup* group);
	static void standUp(CGroup* group);
};


class CAILogicDynamicIfHelper
{
public:
	static void setConditionSuccess(bool value) {_ConditionSuccess = value;}
	static bool getConditionSuccess() { return _ConditionSuccess;}
private:
	static bool _ConditionSuccess;
};
//---------------------------------------------------------------------------------
#endif
