/** \file ai_mgr_pet.h
 *
 * $Id: ai_mgr_pet.h,v 1.50 2007/05/25 09:47:42 verquerre Exp $
 * 
 * This files defines the classes CMgrPet, CPetSpawnMsgImp, CPetSetOwnerImp
 * and CPetCommandMsgImp.
 */

#ifndef RYAI_MGR_PET_H
#define RYAI_MGR_PET_H

#include "ai_mgr.h"
#include "ai_bot_pet.h"
#include "server_share/pet_interface_msg.h"

class	CPetOwner;

typedef	std::map<NLMISC::CEntityId, uint32>	TEntityIdMapUint32;

//////////////////////////////////////////////////////////////////////////////
// CMgrPet                                                                  //
//////////////////////////////////////////////////////////////////////////////

/// This is the manager class for pets, pack animals and steeds
class CMgrPet
: public CManager
{
public:
	CMgrPet(IManagerParent* parent, uint32 alias, std::string const& name, std::string const& filename)	;
	
	void init() { }
	void update();
	void release() { }
	
	virtual void spawn() { CManager::spawn(); }
	void despawnMgr() { CManager::despawnMgr(); }
	
	CStateMachine* getStateMachine() { return NULL; }
	
	void createPetGroup(NLMISC::CEntityId const& petOwnerId);
	CGrpPet* getPetGroup(NLMISC::CEntityId const& petOwnerId);
	void removePetGroup(NLMISC::CEntityId const& petOwnerId);
	
	AITYPES::TMgrType type() const { return AITYPES::MgrTypePet; }
	
	void serviceEvent(CServiceEvent const& info);	
	
	virtual std::string	getOneLineInfoString() const { return std::string("Pet manager '") + getName() + "'"; }
	
private:
	TEntityIdMapUint32 _EntityIdToIndex;
};

//////////////////////////////////////////////////////////////////////////////
// CPetSpawnMsgImp                                                          //
//////////////////////////////////////////////////////////////////////////////

class CPetSpawnMsgImp
: public CPetSpawnMsg
{
	virtual void callback(std::string const& name, NLNET::TServiceId id);
};

//////////////////////////////////////////////////////////////////////////////
// CPetSetOwnerImp                                                          //
//////////////////////////////////////////////////////////////////////////////

class CPetSetOwnerImp
: public CPetSetOwner
{
	virtual void callback(std::string const& name, NLNET::TServiceId id);
};

//////////////////////////////////////////////////////////////////////////////
// CPetCommandMsgImp                                                        //
//////////////////////////////////////////////////////////////////////////////

class CPetCommandMsgImp
: public CPetCommandMsg
{
	virtual void callback(std::string const& name, NLNET::TServiceId id);
};

/****************************************************************************/
/* Inlined methods                                                          */
/****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// CMgrPet                                                                  //
//////////////////////////////////////////////////////////////////////////////

inline
CMgrPet::CMgrPet(IManagerParent* parent, uint32 alias, std::string const& name, std::string const& filename)	
: CManager(parent, alias, name, filename)
{
}

#endif
