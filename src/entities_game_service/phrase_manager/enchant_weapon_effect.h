/** \file enchant_weapon_effect.h
 * <File description>
 *
 * $Id: enchant_weapon_effect.h,v 1.2 2006/10/09 15:25:30 saffray Exp $
 */



#ifndef RY_ENCHANT_WEAPON_EFFECT_H
#define RY_ENCHANT_WEAPON_EFFECT_H

// game share
#include "game_share/scores.h"
#include "game_share/persistent_data.h"
//
#include "phrase_manager/s_effect.h"
#include "entity_manager/entity_base.h"



/** Class for weapon enchants
 * \author Jerome Vuarand
 * \author Nevrax France
 * \date 2005
 * 
 * This class is inspired from CNoLinkDOTEffect and thus may have residual
 * side effects from the copy'n'paste.
*/
class CEnchantWeaponEffect
: public CSTimedEffect
{
public:
	NLMISC_DECLARE_CLASS(CEnchantWeaponEffect)
		
	DECLARE_PERSISTENCE_METHODS

	// default ctor
	CEnchantWeaponEffect() : CSTimedEffect() {}

	CEnchantWeaponEffect(
		const TDataSetRow & creatorRowId,
		const TDataSetRow & targetRowId, // should be replaced with weapon id (CGameItemPtr)
		EFFECT_FAMILIES::TEffectFamily family,
		sint32 effectValue,
		NLMISC::TGameCycle endDate,
		DMGTYPE::EDamageType damageType,
		SCORES::TScores	affectedScore,
		float dpsBonus,
		DMGTYPE::EDamageType oldDamageType)
	: CSTimedEffect(creatorRowId, targetRowId, family, false, effectValue, abs((sint32)dpsBonus), endDate)
	, _DamageType(damageType)
	, _DpsBonus(dpsBonus)
	, _AffectedScore(affectedScore)
	, _CycleDamage(0.f)
	{
		_RemainingDamage = 0;
		_EndsAtCasterDeath = false;
		_Stackable = false;
	}
	
	/// apply the effect
	virtual bool update(CTimerEvent * event, bool applyEffect);
	
	/// callback called when the effect is actually removed
	virtual void removed();
	
	/// if true effect ends at caster death 
	void endsAtCasterDeath(bool flag) { _EndsAtCasterDeath = flag; }
	
	/// set the stackable flag
	void stackable(bool flag) { _Stackable = flag; }
	
	float getDpsBonus() const { return _DpsBonus; }
	
	/// This method should return a direct damage value computed according to weapon speed
	float getDmgBonus() const { return _DpsBonus; }
	
	DMGTYPE::EDamageType getDmgType() const { return _DamageType; }

	virtual NLMISC::CSheetId getAssociatedSheetId() const;

	virtual bool automaticallyReplaceFamily() const { return true; }
	
	virtual bool canBeInactive() const { return false; }

	// re-activate a magic protection modifier loaded with character
	void activate();
	
private:
	/// DPS bonus
	float					_DpsBonus;
	/// number of score points lost by target each cycle
	float					_CycleDamage;
	/// fraction of lost points when not integer (0-1)
	float					_RemainingDamage;
	/// affected score
	SCORES::TScores			_AffectedScore;
	/// damage type
	DMGTYPE::EDamageType	_DamageType;
	/// if true effect ends at caster death 
	bool					_EndsAtCasterDeath;
	/// if true DoT can stacks, otherwise they don't stack
	bool					_Stackable;
	NLMISC::CEntityId		_CreatorEntityId;
};

#endif
