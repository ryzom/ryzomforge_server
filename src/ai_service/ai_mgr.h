/** \file ai_mgr.h
 *
 * $Id: ai_mgr.h,v 1.79 2005/06/28 14:07:37 cado Exp $
 * 
 * This file defines the class CManager.
 */

#ifndef RYAI_AI_MGR_H
#define RYAI_AI_MGR_H

#include "ai_entity.h"
#include "alias_tree_root.h"
#include "manager_parent.h"
#include "service_dependencies.h"

extern NLLIGO::CLigoConfig	LigoConfig;
class CSpawnGroup;
class CStateMachine;

//////////////////////////////////////////////////////////////////////////////
// CManager                                                                 //
//////////////////////////////////////////////////////////////////////////////

class CManager
: public CAliasChild<IManagerParent>
, public NLMISC::CRefCount
, public CAliasTreeRoot
, public CServiceEvent::CHandler
, public CAIEntity
{
public:
	CManager(IManagerParent* parent, uint32 alias, std::string const& name, std::string const& filename);
	virtual ~CManager();
	
	/// @name CChild implementation
	//@{
	virtual std::string getIndexString() const;
	virtual std::string	getOneLineInfoString() const;
	virtual std::vector<std::string> getMultiLineInfoString() const;
	virtual std::string getFullName() const;
//	virtual std::string getName() const;
	//@}
	
	/// @name CServiceEvent::CHandler implementation
	//@{
	virtual void serviceEvent(CServiceEvent const& info);
	//@}
	
	/// @name CAIEntity public implementation
	//@{
	virtual CAIInstance* getAIInstance() const;
	//@}
	
public:
	/// @name Virtual interface
	//@{
	virtual void release();
	virtual void update();
	virtual AITYPES::TMgrType type() const = 0;
	virtual void init() = 0;
	virtual CStateMachine* getStateMachine() = 0;
	virtual void spawn();		
	virtual void despawnMgr();
	//@}
	
	/// @name Accessors
	//@{
	CAliasCont<CGroup>& groups() { return _Groups; }
	CAliasCont<CGroup> const& groups() const { return _Groups; }
	CGroup*	getGroup(uint32 index);
	
	bool isEmpty() const;

	CAliasTreeOwner* getAliasTreeOwner() { return this; }
	
	uint32 getAlias() const { return CAliasTreeOwner::getAlias(); }
	std::string getMap() const { return _map; }
	NLMISC::CEntityId getEntityId() { return _EntityId; }
	//@}
	
	CGroup* getNextValidGroupChild(CGroup* group = NULL);
	
	void addToSpawn(CGroup* group);
	void removeFromSpawnList(CGroup const* group);
	
	static CManager* createManager(AITYPES::TMgrType type, IManagerParent* managerParent, uint32 alias, std::string const& name, std::string const& mapName, std::string const& filename);
	
protected:
	/// @name AI service hierarchy
	//@{
	CAliasCont<CGroup> _Groups;
	//@}
	
	std::string _map;
	
private:
	NLMISC::CEntityId _EntityId;
	uint32 _MaxSpawns;
	std::vector<NLMISC::CDbgPtr<CGroup> > _SpawnList;
	uint32 _CurSpawnRing;
};

#endif
