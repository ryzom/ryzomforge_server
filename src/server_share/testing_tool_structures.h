/** \file testing_tool_structures.h
 * TESTING TOOL STRUCTURES: All structures shared with other services
 * Thsi structures is not in game_share because used only for testing tool service
 *
 * $Id: testing_tool_structures.h,v 1.4 2005/02/22 10:25:14 besson Exp $
 */



#ifndef TESTING_TOOL_STRUCTURES_H
#define TESTING_TOOL_STRUCTURES_H

// misc
#include "nel/misc/types_nl.h"
#include "nel/misc/stream.h"
#include "nel/misc/sheet_id.h"

// game share
#include "game_share/ryzom_entity_id.h"

// stl
#include <vector>

struct SActorBeginTest
{
//	uint16 Role;
//	uint16 Level;
	sint32 Hp;
	sint32 Sta;
	sint32 Sap;
	NLMISC::CSheetId Armor;
	uint16	ArmorQuality;
	NLMISC::CSheetId RightHand;
	uint16	RightHandQuality;
	NLMISC::CSheetId LeftHand;
	uint16	LeftHandQuality;
	std::vector< NLMISC::CSheetId > Sentence1;
	std::vector< NLMISC::CSheetId > Sentence2;
	std::vector< NLMISC::CSheetId > Sentence3;

	void serial(NLMISC::IStream &f) throw(NLMISC::EStream)
	{
//		f.serial( Role );
//		f.serial( Level );
		f.serial( Hp );
		f.serial( Sta );
		f.serial( Sap );
		f.serial( Armor );
		f.serial( ArmorQuality );
		f.serial( RightHand );
		f.serial( RightHandQuality );
		f.serial( LeftHand );
		f.serial( LeftHandQuality );
		f.serialCont( Sentence1 );
		f.serialCont( Sentence2 );
		f.serialCont( Sentence3 );
	}
};

struct SLogReport
{
	std::vector< NLMISC::CSheetId > UsedBrick; //
	bool	Stop;
	uint8	SentenceSuccesLuck; //
	bool	SentenceSucces;//
	uint8	HitLuck;//
	bool	Hit;//
	bool	CriticalHit;
	uint32	MaxDamage; //
	uint32	MinDamage; //
	uint32	GivenDamage; //
	uint16	Localized; //
	uint32	ShieldAbsorption; //
 	uint32	ArmorAbsorption; //
	uint32	HpLost; //
	bool	SpecialEffectResist;
	uint16	SpecialEffectStart;
	uint32	SpecialEffectDuration;
	uint32	UsedStamina; //
	uint32	UsedSap;
	uint32	StaminaLeft; //
	uint32	SapLeft;

	void serial(NLMISC::IStream &f) throw(NLMISC::EStream)
	{
		f.serialCont( UsedBrick );
		f.serial( Stop );
		f.serial( SentenceSuccesLuck );
		f.serial( SentenceSucces );
		f.serial( HitLuck );
		f.serial( Hit );
		f.serial( CriticalHit );
		f.serial( MaxDamage );
		f.serial( MinDamage );
		f.serial( GivenDamage );
		f.serial( Localized );
		f.serial( ShieldAbsorption );
		f.serial( ArmorAbsorption );
		f.serial( HpLost );
		f.serial( SpecialEffectResist );
		f.serial( SpecialEffectStart );
		f.serial( SpecialEffectDuration );
		f.serial( UsedStamina );
		f.serial( UsedSap );
		f.serial( StaminaLeft );
		f.serial( SapLeft );
	}
};

extern SLogReport LogReportStructure;

#endif //TESTING_TOOL_H

