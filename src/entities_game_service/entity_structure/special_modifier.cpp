/** \special_modifier.cpp
 * 
 *
 * $Id: special_modifier.cpp,v 1.4 2005/02/22 10:22:35 besson Exp $
 */



#include "stdpch.h"

#include "special_modifier.h"


///////////
// USING //
///////////
using namespace std;
using namespace NLMISC;

//-----------------------------------------------
// CSpecialModifier default constructor
//-----------------------------------------------
CSpecialModifiers::CSpecialModifiers()
{
	init();
} // CSpecialModifier //


//-----------------------------------------------
// CSpecialModifier init
//-----------------------------------------------
void CSpecialModifiers::init()
{
	MeleeAttackModifierOnEnemy	= 0;
	MeleeAttackModifierOnSelf	= 0;
	
	RangeAttackModifierOnEnemy	= 0;
	RangeAttackModifierOnSelf	= 0;
	
	MagicCastingModifierOnSelf	= 0;
	MagicCastingModifierOnEnemy	= 0;
	
	AttackModifierOnSelf		= 0;
	
	ChanceToFailStrategy		= 0;
	ChanceToFailSpell			= 0;
	ChanceToFailFaber			= 0;
	ChanceToFailHarvest			= 0;
	ChanceToFailTracking		= 0;
	
	MeleeSlashingDamageArmor	= 0;
	MeleeBluntDamageArmor		= 0;
	MeleePiercingDamageArmor	= 0;
	
	MeleeDamageModifierFactor	= 1000; /// 1000 * real factor, so 1000 = 1.0
	RangeDamageModifierFactor	= 1000; /// 1000 * real factor, so 1000 = 1.0
	
	CreatureMeleeTakenDamageFactor	= 1000; /// 1000 * real factor, so 1000 = 1.0
	CreatureRangeTakenDamageFactor	= 1000; /// 1000 * real factor, so 1000 = 1.0
	
	MeleeAttackSlow				= 0;
	
	CombatBrickLatencyMultiplier = 1;
	MagicBrickLatencyMultiplier = 1;
	
	ArmorQualityModifier		= 0;
	WeaponQualityModifier		= 0;
	
	ArmorAbsorbtionMultiplier = 100; /// 100 * real factor, so 100 = 1.0
	
} // CSpecialModifier init //



//-----------------------------------------------
// CSpecialModifiers::serial
//-----------------------------------------------
void CSpecialModifiers::serial(NLMISC::IStream &f) throw(NLMISC::EStream)
{
	f.serial( MeleeAttackModifierOnEnemy );
	f.serial( MeleeAttackModifierOnSelf );
	
	f.serial( RangeAttackModifierOnEnemy );
	f.serial( RangeAttackModifierOnSelf );
	
	f.serial( AttackModifierOnSelf );
	
	f.serial( MagicCastingModifierOnSelf );
	f.serial( MagicCastingModifierOnEnemy );
	
	f.serial( ChanceToFailStrategy );
	f.serial( ChanceToFailSpell );
	f.serial( ChanceToFailFaber );
	f.serial( ChanceToFailHarvest );
	f.serial( ChanceToFailTracking );
	
	f.serial( MeleeSlashingDamageArmor );
	f.serial( MeleeBluntDamageArmor );
	f.serial( MeleePiercingDamageArmor );
	
	f.serial( MeleeDamageModifierFactor );
	f.serial( RangeDamageModifierFactor );
	
	f.serial(CreatureMeleeTakenDamageFactor);
	f.serial(CreatureRangeTakenDamageFactor);
	
	f.serial( MeleeAttackSlow );
	
	f.serial(CombatBrickLatencyMultiplier);
	f.serial(MagicBrickLatencyMultiplier);
	
	f.serial(ArmorQualityModifier);
	f.serial(WeaponQualityModifier);
	
	f.serial(ArmorAbsorbtionMultiplier);
	
} // CSpecialModifiers::serial //

