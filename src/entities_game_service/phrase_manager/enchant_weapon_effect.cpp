/** \file enchant_weapon_effect.cpp
 * <File description>
 *
 * $Id: enchant_weapon_effect.cpp,v 1.2 2006/10/09 15:25:30 saffray Exp $
 */



#include "stdpch.h"
// net
#include "nel/net/message.h"
//
#include "nel/misc/string_conversion.h"

#include "enchant_weapon_effect.h"
#include "phrase_manager/phrase_utilities_functions.h"

#include "entity_manager/entity_base.h"
#include "player_manager/character.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

extern CPlayerManager PlayerManager;


//----------------------------------------------------------------------------

bool CEnchantWeaponEffect::update(CTimerEvent* event, bool applyEffect)
{
	NL_ALLOC_CONTEXT(EWEUPD);
	// if needed check if caster is dead
	if (_EndsAtCasterDeath)
	{
		const CEntityBase *caster = CEntityBaseManager::getEntityBasePtr(_CreatorRowId);
		if ( !caster || caster->isDead())
		{
			_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
			return true;
		}
	}
	
	CEntityBase	*targetEntity = CEntityBaseManager::getEntityBasePtr(_TargetRowId);
	if (targetEntity == NULL)
	{
		_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
		return true;
	}
	
	// set timer next event
	_UpdateTimer.setRemaining(/*_CycleLength*/20, event);
	
	return false;
}

//----------------------------------------------------------------------------

void CEnchantWeaponEffect::removed()
{
	CEntityBase	*targetEntity = CEntityBaseManager::getEntityBasePtr(_TargetRowId);
	if (targetEntity == NULL)
	{
		return;
	}

	// if entity is dead, do not send messages
	if (targetEntity->isDead())
		return;

	DEBUGLOG("EFFECT: Enchant weapon effect ends on entity %s", targetEntity->getId().toString().c_str());
}

// conversion effect->sheetid
static NLMISC::CStringConversion<DMGTYPE::EDamageType>::CPair const sheetIdTable [] =
{
	{ "enchant_weapon.sbrick",				DMGTYPE::SLASHING },
	{ "enchant_weapon.sbrick",				DMGTYPE::PIERCING },
	{ "enchant_weapon.sbrick",				DMGTYPE::BLUNT },
	
	{ "enchant_weapon_rot.sbrick",			DMGTYPE::ROT },
	{ "enchant_weapon_acid.sbrick",			DMGTYPE::ACID },
	{ "enchant_weapon_fire.sbrick",			DMGTYPE::FIRE },
	{ "enchant_weapon_poison.sbrick",		DMGTYPE::POISON },
	{ "enchant_weapon_electricity.sbrick",	DMGTYPE::ELECTRICITY },
	{ "enchant_weapon_shock.sbrick",		DMGTYPE::SHOCK },
	
	{ "enchant_weapon.sbrick",				DMGTYPE::UNDEFINED },
};
static NLMISC::CStringConversion<DMGTYPE::EDamageType> conversionSheetID(sheetIdTable, sizeof(sheetIdTable) / sizeof(sheetIdTable[0]),  DMGTYPE::UNDEFINED);

/// get the sheetId associated to an effect to display on client interface
static NLMISC::CSheetId getAssociatedSheetId(DMGTYPE::EDamageType effect)
{
	const std::string &str  = conversionSheetID.toString(effect);
	if ( !str.empty() && str != "Unknown")
		return NLMISC::CSheetId(str);
	else
		return NLMISC::CSheetId::Unknown;
}

NLMISC::CSheetId CEnchantWeaponEffect::getAssociatedSheetId() const
{
	return ::getAssociatedSheetId(_DamageType);
}

//--------------------------------------------------------------
void CEnchantWeaponEffect::activate()
{
	CCharacter *actor = PlayerManager.getChar(_CreatorEntityId);
	if (!actor)
	{
		nlwarning("<CEnchantWeaponEffect::activate> Cannot find actor entity or not a player");
		return;
	}

	CEnchantWeaponEffect* effect = new CEnchantWeaponEffect(actor->getEntityRowId(), actor->getEntityRowId(),
		getFamily(),
		getParamValue(),
		getEndDate()+CTickEventHandler::getGameCycle(),
		_DamageType,
		_AffectedScore,
		_DpsBonus,
		DMGTYPE::UNDEFINED);
	if (effect)
	{
		effect->endsAtCasterDeath(true);
		effect->stackable(true);
		actor->addSabrinaEffect(effect);
	}
	else
	{
		nlwarning("<CEnchantWeaponEffect::activate> Failed to allocate new CEnchantWeaponEffect");
		return;
	}
}

//-----------------------------------------------------------------------------
// Persistent data for CModMagicProtectionEffect
//-----------------------------------------------------------------------------

#define PERSISTENT_TOKEN_FAMILY RyzomTokenFamily
#define PERSISTENT_CLASS CEnchantWeaponEffect

#define PERSISTENT_DATA\
	STRUCT2(STimedEffect,					CSTimedEffect::store(pdr),						CSTimedEffect::apply(pdr))\
	PROP2(_CreatorEntityId,		CEntityId,	TheDataset.getEntityId(getCreatorRowId()),		_CreatorEntityId = val)\
	PROP(float,_DpsBonus)\
	PROP(float,_CycleDamage)\
	PROP2(_AffectedScore,		string,		SCORES::toString(_AffectedScore),				_AffectedScore = SCORES::toScore(val))\
	PROP2(_DamageType,			string,		DMGTYPE::toString(_DamageType),					_DamageType = DMGTYPE::stringToDamageType(val))\
	PROP(bool,_EndsAtCasterDeath)\

#pragma message( PERSISTENT_GENERATION_MESSAGE )
#include "game_share/persistent_data_template.h"
