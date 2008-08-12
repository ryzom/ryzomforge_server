/** \file ai_bot_easter_egg.cpp
 *
 * $Id: ai_bot_easter_egg.cpp,v 1.2 2006/05/31 12:10:20 boucher Exp $
 */

#include "stdpch.h"
#include "ai_bot_easter_egg.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// CBotEasterEgg                                                            //
//////////////////////////////////////////////////////////////////////////////

CBotEasterEgg::CBotEasterEgg(CGroup* owner, uint32 alias, std::string const& name, uint32 easterEggId)
: CBotNpc(owner, alias, name)
, _EasterEggId(easterEggId)
{
}

CBotEasterEgg::~CBotEasterEgg()
{
}

std::string	CBotEasterEgg::getOneLineInfoString() const
{
	string desc = NLMISC::toString("Easter Egg bot %u '%s'", getEasterEggId(), getName().c_str());
	return desc;
}
