/** \file msg_ai_sercice.cpp
 *
 * $Id: msg_ai_service.cpp,v 1.2 2007/05/09 15:33:08 boucher Exp $
 */




//----------------------------------------------------------------------------

#include "stdpch.h"
#include "msg_ai_service.h"

using namespace NLMISC;
using namespace std;

CQueryEgs::TFuns CQueryEgs::_Funs;

void CQueryEgs::init()
{
#define InsertFun(X) _Funs.insert( std::make_pair(std::string(#	X), X));
	InsertFun(Name);
	InsertFun(Hp); InsertFun(MaxHp); InsertFun(RatioHp);
	InsertFun(Sap); InsertFun(MaxSap); InsertFun(RatioSap);
	InsertFun(Stamina); InsertFun(MaxStamina); InsertFun(RatioStamina);
	InsertFun(Focus); InsertFun(MaxFocus); InsertFun(RatioFocus);
	InsertFun(BestSkillLevel);
	InsertFun(Target);
	InsertFun(IsInInventory); InsertFun(KnowBrick);
#undef InsertFun
}



CQueryEgs::TFunEnum CQueryEgs::getFunEnum(const std::string& funName) const
{
	// lazy intialisation so function is const but can call non const fun
	if (_Funs.empty())
	{
		const_cast<CQueryEgs*>(this)->init();
	}

	TFuns::const_iterator found = _Funs.find(funName);
	if ( found != _Funs.end())
	{
		return found->second;
	}
	return Undef;
}
