/** \file ai_mgr_npc.h
 * 
 * $Id: ai_mgr_npc.h,v 1.48 2005/12/29 17:08:25 vuarand Exp $
 * 
 * This file defines the class CMgrNpc.
 */

#ifndef RYAI_MGR_NPC_H
#define RYAI_MGR_NPC_H

#include "ai_mgr.h"
#include "event_manager.h"
#include "states.h"
#include "ai_variables.h"
#include "event_reaction_container.h"

//////////////////////////////////////////////////////////////////////////////
// CMgrNpc                                                                  //
//////////////////////////////////////////////////////////////////////////////

/// This is the manager class for npc (and npc groups)
class CMgrNpc
: public CManager
{
public:
	CMgrNpc(IManagerParent* parent, uint32 alias, std::string const& name, std::string const& filename);
	virtual ~CMgrNpc();
	
	void update();
	
	CStateMachine* getStateMachine() { return &_StateMachine; }
	
	uint32 getAlias() const { return CManager::getAlias(); }
	CAIAliasDescriptionNode* getAliasNode() const { return CManager::getAliasNode(); }
	
	virtual std::string	getOneLineInfoString() const;
	virtual std::vector<std::string> getMultiLineInfoString() const;
	
	//////////////////////////////////////////////////////////////////////////
	
	//	Methods inherited from IManager.
	void init() { }
	void release() { }
	
	void serviceDown(uint32	sid, std::string const& name) { }
	
	AITYPES::TMgrType type() const { return AITYPES::MgrTypeNpc; }
	
	// instantiate the bot population
	virtual void spawn();
	// clear the bot population
	virtual void despawnMgr();
	
	// event managers --------------------------------------------------
	CAIEvent EventDestinationReachedFirst;
	CAIEvent EventDestinationReachedAll;
	CAIEvent EventBotKilled;
	CAIEvent EventSquadLeaderKilled;
	CAIEvent EventGrpEliminated;
	
	virtual void registerEvents();
	
	//////////////////////////////////////////////////////////////////////////	
	//	Alias Tree related Methods.
	
	IAliasCont* getAliasCont(AITYPES::TAIType type);
	CAliasTreeOwner* createChild(IAliasCont* cont, CAIAliasDescriptionNode* aliasTree);
	
	//////////////////////////////////////////////////////////////////////////
	CStateMachine _StateMachine;
};

#endif
