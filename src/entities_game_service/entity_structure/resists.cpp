/** \file resists.cpp
 * <File description>
 *
 * $Id: resists.cpp,v 1.5 2005/02/22 10:22:35 besson Exp $
 */



//////////////
//	INCLUDE	//
//////////////
#include "stdpch.h"
//
#include "resists.h"
#include "player_manager/character.h"
#include "game_item_manager/game_item.h"

//////////////
//	USING	//
//////////////
using namespace std;
using namespace NLMISC;

uint16 CCreatureResists::ImmuneScore = 0xffff;

//--------------------------------------------------------------
//					serial() 
//--------------------------------------------------------------
void CCreatureResists::serial(class NLMISC::IStream &f) throw(NLMISC::EStream)
{
	f.serial(Fear);
	f.serial(Sleep);
	f.serial(Stun);
	f.serial(Root);
	f.serial(Slow);
	f.serial(Snare);
	f.serial(Blind);
	f.serial(Madness);
	
	f.serial(Acid);
	f.serial(Cold);
	f.serial(Electricity);
	f.serial(Fire);
	f.serial(Poison);
	f.serial(Rot);
	f.serial(Shockwave);	
} // serial //
