/** \file ai_bot_pet.h
 * 
 * $Id: ai_bot_pet.h,v 1.67 2005/08/09 16:46:49 vuarand Exp $
 * 
 * This file defines the classes CSpawnBotPet, CBotPet and IAIBotCAIProfile.
 */

#pragma warning (disable : 4355) // warning C4355: 'this' : used in base member initializer list

#ifndef RYAI_BOT_PET_H
#define RYAI_BOT_PET_H

#include "ai_bot.h"
#include "path_behaviors.h"

class CBotPet;
class CGrpPet;
class CPetOwner;

class IAIBotCAIProfile;
class CSpawnGroupPet;

//////////////////////////////////////////////////////////////////////////////
// CSpawnBotPet                                                             //
//////////////////////////////////////////////////////////////////////////////

class CSpawnBotPet
: public NLMISC::CDbgRefCount<CSpawnBotPet>
, public CSpawnBot
{
public:
	CSpawnBotPet(TDataSetRow const& row, CBot& owner, NLMISC::CEntityId const& id, float radius, uint32 level, RYAI_MAP_CRUNCH::TAStarFlag denyFlags);
	
	void processEvent(CCombatInterface::CEvent const& event) { }
	
	RYZOMID::TTypeId getRyzomType() const { return RYZOMID::pack_animal; }
	
	CBotPet& getPersistent	();
	CBotPet const& getPersistent() const;
	
	CSpawnGroupPet& spawnGrp();
	
	void sendInfoToEGS() const { }
	
	// pets are always attackable by bots
	virtual	bool isBotAttackable() const { return true; }
	
	// Take position from mirror
	void updatePos();
	
	// Return true if the animal is mounted (thus controlled by the GPMS)
	bool isMounted() const;
	
	CPathPosition& pathPos() { return _PathPos; }
	
	uint32 _DeathTime;
	
private:

	CPathPosition	_PathPos;
};

//////////////////////////////////////////////////////////////////////////////
// CBotPet                                                                  //
//////////////////////////////////////////////////////////////////////////////

class CBotPet
: public CBot
{
public:
	CBotPet(CGroup* owner, CAIAliasDescriptionNode* alias = NULL);
	~CBotPet();
	
	void getSpawnPos(CAIVector& triedPos, RYAI_MAP_CRUNCH::CWorldPosition& spawnPos, RYAI_MAP_CRUNCH::CWorldMap const& worldMap, CAngle& spawnTheta);
	void setSpawnPos(CAIPos const& spawnPos) { _SpawnPos = spawnPos; }
	CGrpPet& getPetGroup();
	
	void update(uint32 ticks, CAIEntityPhysical const* petOwner);
	
	CSpawnBotPet* getSpawn() { return static_cast<CSpawnBotPet*>(getSpawnObj()); }
	
	CAIS::CCounter& getSpawnCounter();
	
	void setDespawn() { _MustDespawn = true; }
	bool haveToDespawn() const { return _MustDespawn; }
	
	void changeOwner(NLMISC::CEntityId const& newOwner);
	
	virtual std::string	getOneLineInfoString() const { return std::string("Pet bot '") + getName() + "'"; }
	
	virtual void triggerSetSheet(AISHEETS::ICreatureCPtr const& sheet);
	
protected:
	RYZOMID::TTypeId getRyzomType() const { return RYZOMID::pack_animal; }
	
	CSpawnBot* getSpawnBot(TDataSetRow const& row, NLMISC::CEntityId const& id, float radius)
	{
		return new CSpawnBotPet(row, *this, id, radius, getSheet()->Level(), getGroup().getAStarFlag());
	}
	
private:
	CAIPos	_SpawnPos;
	bool	_MustDespawn;
};

/****************************************************************************/
/* Inlined methods                                                          */
/****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// CSpawnBotPet                                                             //
//////////////////////////////////////////////////////////////////////////////

inline
CSpawnBotPet::CSpawnBotPet(TDataSetRow const& row, CBot& owner, NLMISC::CEntityId const& id, float radius, uint32 level, RYAI_MAP_CRUNCH::TAStarFlag denyFlags)
: CSpawnBot(row, owner, id, radius, level, denyFlags)
, _DeathTime(0)
, _PathPos(CAngle())
{
}

inline
CBotPet& CSpawnBotPet::getPersistent()
{
	return static_cast<CBotPet&>(CSpawnBot::getPersistent());
}

inline
CBotPet const& CSpawnBotPet::getPersistent() const
{
	return static_cast<const CBotPet&>(CSpawnBot::getPersistent());
}

//////////////////////////////////////////////////////////////////////////////
// CBotPet                                                                  //
//////////////////////////////////////////////////////////////////////////////

inline
CBotPet::CBotPet(CGroup* owner, CAIAliasDescriptionNode* alias)
: CBot(owner, alias)
, _MustDespawn(false)
{
}

inline
CBotPet::~CBotPet()
{
	if (!isSpawned())
		return;
	despawnBot();
}

inline
CAIS::CCounter& CBotPet::getSpawnCounter()
{
	return CAIS::instance()._PetBotCounter;
}

#endif
