/** \file sabrina_item_stats.h
 *
 * $Id: sabrina_item_stats.h,v 1.2 2004/03/01 19:22:19 lecroart Exp $
 */



#ifndef RY_SABRINA_ITEM_STATS_H
#define RY_SABRINA_ITEM_STATS_H

// nel misc
#include "nel/misc/types_nl.h"
// game_share
#include "game_share/skills.h"
#include "game_share/damage_types.h"
#include "game_share/armor_types.h"
#include "game_share/game_item_manager/game_item.h"


/**
 * Sabrina weapon stats description class
 * \author Sadge
 * \author Nevrax France
 * \date 2003
 */

struct CWeaponStats
{
	// construction
	CWeaponStats();
	CWeaponStats(const CGameItemPtr &itemPtr, uint16 quality);

	// debug routines
	std::string toString() const;

	// read accessors
	uint16					getSpeedInTicks()	const { return _SpeedInTicks; }
	uint32					getDamage()			const { return _Damage; }
	uint16					getQuality()		const { return _Quality; }
	DMGTYPE::EDamageType	getDmgType()		const { return _DmgType; }
	ITEMFAMILY::EItemFamily	getFamily()			const { return _Family; }
	float					getRange()			const { return _Range; }
	SKILLS::ESkills			getSkill()			const { return _Skill; }
	sint32					getSkillValue()		const { return _SkillValue; }

	// write accessors
	void setSpeedInTicks(uint16 ticks)				{ _SpeedInTicks=ticks; }
	void setDamage(uint32 damage)					{ _Damage=damage; }
	void setQuality(uint16 quality)					{ _Quality=quality; }
	void setDmgType(DMGTYPE::EDamageType dmgType)	{ _DmgType=dmgType; }
	void setFamily(ITEMFAMILY::EItemFamily family)	{ _Family=family; }
	void setRange(float range)						{ _Range=range; }
	void setSkill(SKILLS::ESkills skill)			{ _Skill=skill; }
	void setSkillValue(sint32 value)				{ _SkillValue=value; }

private:
	uint16					_SpeedInTicks;
	uint32					_Damage;	
	uint16					_Quality;
	DMGTYPE::EDamageType	_DmgType;
	ITEMFAMILY::EItemFamily	_Family;
	float					_Range;		// if > 0 range weapon or ammo, == 0 melee weapon	
	SKILLS::ESkills			_Skill;		// no meaning for ammos
	sint32					_SkillValue; // no meaning for ammos
};


/**
 * Sabrina armor description base class
 * \author Sadge
 * \author Nevrax France
 * \date 2003
 */

class CArmorStats
{
public:
	// construction
	CArmorStats();
	CArmorStats( const CStaticItem *item, uint16 quality );

	// debug routines
	std::string toString(bool overrideTitle=false) const;

	// read accessors
	uint32 getQuality()							const { return _Quality; }
	SKILLS::ESkills	getSkill()					const { return _Skill; }
	ARMORTYPE::EArmorType getArmorType()		const { return _ArmorType; }
	float getProtectionFactor(uint32 index)		const; 
	uint32 getProtectionLimit(uint32 index)		const; 

	// write accessors
	void setQuality(uint32 quality)						{ _Quality=quality; }
	void setSkill(SKILLS::ESkills skill)				{ _Skill=skill; }
	void setArmorType(ARMORTYPE::EArmorType armorType)	{ _ArmorType=armorType; }
	void setProtectionFactor(uint32 index,float val); 
	void setProtectionLimit(uint32 index,uint32 val); 

private:
	uint32					_Quality;
	SKILLS::ESkills			_Skill;
	ARMORTYPE::EArmorType	_ArmorType;

	float _ProtectionFactor[DMGTYPE::NBTYPES];
	uint32 _ProtectionLimit[DMGTYPE::NBTYPES];
};



/**
 * Sabrina shield class (derived from CArmorStats)
 * \author Sadge
 * \author Nevrax France
 * \date 2003
 */

class CShieldStats: public CArmorStats
{
public:
	// construction
	CShieldStats(): CArmorStats(), _ShieldType(SHIELDTYPE::NONE)
	{}

	// debug routines
	std::string toString() const
	{
		return std::string()+SHIELDTYPE::toString(_ShieldType)+CArmorStats::toString(true);
	}

	// read accessors
	SHIELDTYPE::EShieldType getShieldType() const { return _ShieldType; }

	// write accessors
	void setShieldType(SHIELDTYPE::EShieldType shieldType) { _ShieldType=shieldType; }

private:
	SHIELDTYPE::EShieldType _ShieldType;
};


#endif


