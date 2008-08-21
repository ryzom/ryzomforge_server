/** \file action_distance_checker.cpp
 * <File description>
 *
 * $Id: action_distance_checker.cpp,v 1.11 2005/02/22 10:22:30 besson Exp $
 */



#include "stdpch.h"
#include "player_manager/action_distance_checker.h"
#include "player_manager/player.h"

CActionDistanceChecker* CActionDistanceChecker::_Instance = NULL;

//---------------------------------------------------
// CActionDistanceChecker init
//---------------------------------------------------
void CActionDistanceChecker::init()
{
	nlassert(_Instance == NULL);
	_Instance = new CActionDistanceChecker;
}// init

//---------------------------------------------------
// CActionDistanceChecker release
//---------------------------------------------------
void CActionDistanceChecker::release()
{
	nlassert(_Instance != NULL);
	delete _Instance;
	_Instance = NULL;
}// init

//---------------------------------------------------
// CActionDistanceChecker ctor
//---------------------------------------------------
CActionDistanceChecker::CActionDistanceChecker()
:_LastCheck(0),_NbCheckPerTick(50)
{
}// ctor


