/** \file ai_mgr_fauna.h
 *
 * $Id: ai_mgr_fauna.h,v 1.47 2005/06/28 14:07:37 cado Exp $
 * 
 * This file defines the class CMgrFauna
 */

#ifndef RYAI_MGR_FAUNA_H
#define RYAI_MGR_FAUNA_H

#include "ai_mgr.h"
#include "ai_place.h"
#include "event_manager.h"
#include "event_reaction_container.h"

class CFauna;

//////////////////////////////////////////////////////////////////////////////
// CMgrFauna                                                                //
//////////////////////////////////////////////////////////////////////////////

/// This is the manager class for fauna (and fauna groups)
class CMgrFauna
: public CManager
{
public:	
	CMgrFauna(IManagerParent* parent, uint32 alias, std::string const& name, std::string const& filename);
	virtual ~CMgrFauna();
	
	CStateMachine* getStateMachine() { return &_StateMachine; }
	
	virtual std::string getOneLineInfoString() const;
	
	//////////////////////////////////////////////////////////////////////////
	//	CStateMachine
	
	uint32 getAlias() const { return CManager::getAlias(); }
	
	CAIAliasDescriptionNode* getAliasNode() const { return CManager::getAliasNode(); }
	
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////	
	//	Methods inherited from IManager.
	void init();
	void update();
	void release() { CManager::release(); }
	
	AITYPES::TMgrType type() const { return AITYPES::MgrTypeFauna; }
	// event managers --------------------------------------------------
	CAIEvent EventDestinationReachedFirst;
	CAIEvent EventDestinationReachedAll;
	CAIEvent EventBotKilled;
	CAIEvent EventGrpEliminated;
	
	CStateMachine _StateMachine;
	
	void registerEvents();
	
	//////////////////////////////////////////////////////////////////////////	
	//	Alias Tree related Methods.
	
	IAliasCont*			getAliasCont(AITYPES::TAIType type);
	CAliasTreeOwner*	createChild(IAliasCont* cont, CAIAliasDescriptionNode* aliasTree);
	
	/// @name CAIEntity public implementation
	//@{
	virtual void display(CStringWriter& stringWriter);
	//@}
	
protected:
	/// @name CAIEntity protected implementation
	//@{
	virtual std::string buildDebugString(uint idx);
	//@}
};

#endif
