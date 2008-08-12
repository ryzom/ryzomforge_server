/** \file ai_bot_easter_egg.h
 *
 * $Id: ai_bot_easter_egg.h,v 1.2 2006/05/31 12:10:20 boucher Exp $
 * 
 * This file defines the class CBotEasterEgg.
 */

#ifndef RYAI_BOT_EASTER_EGG_H
#define RYAI_BOT_EASTER_EGG_H

#include "ai_bot_npc.h"

//////////////////////////////////////////////////////////////////////////////
// CBotEasterEgg                                                            //
//////////////////////////////////////////////////////////////////////////////

class CBotEasterEgg : public CBotNpc
{
public:
	CBotEasterEgg(CGroup* owner, uint32 alias, std::string const& name, uint32 easterEggId);
	virtual ~CBotEasterEgg();

	/// get the easter egg ID
	uint32	getEasterEggId() const { return _EasterEggId; }

	virtual std::string	getOneLineInfoString() const;

private:
	uint32	_EasterEggId;
};

#endif
