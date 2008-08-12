/** \file ai_grp_pet.h
 * 
 * $Id: ai_grp_pet.h,v 1.40 2005/06/24 13:03:51 vuarand Exp $
 * 
 * This file defines the classes CSpawnGroupPet and CGrpPet.
 */

#ifndef RYAI_GRP_PET_H
#define RYAI_GRP_PET_H
#include "ai_mgr_pet.h"
#include "ai_grp.h"
#include "time_interface.h"
#include "path_behaviors.h"
#include "service_dependencies.h"

class CMgrPet;
class CPetOwner;

//////////////////////////////////////////////////////////////////////////////
// CSpawnGroupPet                                                           //
//////////////////////////////////////////////////////////////////////////////

/// This is the base class for PET groups
class CSpawnGroupPet
: public CSpawnGroup
{
public:	
	CSpawnGroupPet(CPersistent<CSpawnGroup>& owner)
	: CSpawnGroup(owner)
	, _PathCont(NLMISC::safe_cast<CGroup*>(&owner)->getAStarFlag())
	{
		_LastUpdate = CTimeInterface::gameCycle();
		_IsPlayerSpawned = true;
	}
	
	CGrpPet& getPersistent() const;
	
	void spawnBots() { }
	void despawnBots (bool immediately) { }
	
	void update();
		
	CPathCont& getPathCont() { return _PathCont; }
	
	CAIVector const& getPos() const { return _PathCont.getDestination(); }
	
private:
	CPathCont	_PathCont;		// this path container is share by all player pets .. (thats accelerate our computing).
	uint32		_LastUpdate;
	bool		_IsPlayerSpawned;
};

//////////////////////////////////////////////////////////////////////////////
// CGrpPet                                                                  //
//////////////////////////////////////////////////////////////////////////////

class CGrpPet
: public CGroup
{
public:
	CGrpPet(CMgrPet* mgr, NLMISC::CEntityId const& owner, CAIAliasDescriptionNode* aliasTree = NULL);
	
	CDynGrpBase* getGrpDynBase() { return NULL; }
	
	RYZOMID::TTypeId getRyzomType() { return RYZOMID::pack_animal; }
	
	CAIS::CCounter& getSpawnCounter();
	
	/// @name Service events
	//@{
	void serviceUp(uint32 serviceId, std::string const& serviceName);
	void serviceDown(uint32 serviceId, std::string const& serviceName);
	//@}
	
	void init() { }
	
	void release() { }
	
	void setEvent(uint eventId);
	
	NLMISC::CSmartPtr<CSpawnGroup> createSpawnGroup();
	
	CPersistentStateInstance* getPersistentStateInstance();
	
	NLMISC::CEntityId const& getPetOwner() const { return _PetOwner; }
	
	CMgrPet& getPetManager() { return *(NLMISC::safe_cast<CMgrPet*>(getOwner())); }
	
	CCont<CBot>& bots() { return _Bots; }
	
	virtual std::string	getOneLineInfoString() const { return std::string("Pet group '") + getName() + "'"; }
	
private:
	NLMISC::CEntityId const _PetOwner;
};

/****************************************************************************/
/* Inlined methods                                                          */
/****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// CSpawnGroupPet                                                           //
//////////////////////////////////////////////////////////////////////////////

inline
CGrpPet& CSpawnGroupPet::getPersistent() const
{
	return static_cast<CGrpPet&>(CSpawnGroup::getPersistent());
}

//////////////////////////////////////////////////////////////////////////////
// CGrpPet                                                                  //
//////////////////////////////////////////////////////////////////////////////

inline
CGrpPet::CGrpPet(CMgrPet* mgr, NLMISC::CEntityId const& owner, CAIAliasDescriptionNode* aliasTree)
: CGroup(mgr, RYAI_MAP_CRUNCH::Nothing, aliasTree)
, _PetOwner(owner)
{
	_Bots.setChildSize(4);
}

inline
void CGrpPet::setEvent(uint eventId)
{
	nlwarning("Can't set event on a CGrpPet object !");
}

inline
NLMISC::CSmartPtr<CSpawnGroup> CGrpPet::createSpawnGroup()
{
	NL_ALLOC_CONTEXT(AIGPGSG);
	return new CSpawnGroupPet(*this);
}

inline
CPersistentStateInstance* CGrpPet::getPersistentStateInstance()
{
	// WE NEVER HAVE TO GO HERE AS PET ARE NOT DERIVED FROM STATE_INSTANCE STUFF !
	nldebug("State instance stuff called on a pet group");
	return (CPersistentStateInstance*)NULL;
}

#endif
