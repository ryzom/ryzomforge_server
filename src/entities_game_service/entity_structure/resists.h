/** \file resists.h
 * 
 *
 * $Id: resists.h,v 1.5 2004/12/08 13:26:48 besson Exp $
 */



#ifndef RYZOM_RESISTS_H
#define RYZOM_RESISTS_H

#include "game_share/effect_families.h"
#include "game_share/damage_types.h"
#include "game_share/protection_type.h"

class CCreature;
class CCharacter;

//// struct for creature resists values
class CCreatureResists
{
public:
	uint16	Fear;
	uint16	Sleep;
	uint16	Stun;
	uint16	Root;
	uint16	Snare;
	uint16	Slow;
	uint16	Blind;
	uint16	Madness;

	uint16	Acid;
	uint16	Cold;
	uint16	Electricity;
	uint16	Fire;
	uint16	Poison;
	uint16	Rot;
	uint16	Shockwave;
public:
	// ctor
	CCreatureResists(): Fear(0),Sleep(0), Stun(0), Root(0), Snare(0), Slow(0), Blind(0), Madness(0),
				Acid(0), Cold(0), Electricity(0), Fire(0), Poison(0), Rot(0), Shockwave(0)
	{}

	/// serialize
	void serial(class NLMISC::IStream &f) throw(NLMISC::EStream);

public:
	/// static value indicating the immune score (when someone cannot be affected at all by an effect type)
	static uint16 ImmuneScore;
};

#endif // RYZOM_RESISTS_H

/* End of resists.h */
