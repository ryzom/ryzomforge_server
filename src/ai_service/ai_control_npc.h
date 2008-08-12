/** \file ai_control_npc.h
 *
 * $Id: ai_control_npc.h,v 1.4 2006/12/06 17:22:05 boucher Exp $
 * 
 * 
 */

#ifndef RYAI_CONTROL_NPC_H
#define RYAI_CONTROL_NPC_H

#include "profile.h"

class CBotPlayer;
class CSpawnBotNpc;

//////////////////////////////////////////////////////////////////////////////
// CPlayerControlNpc                                                        //
//////////////////////////////////////////////////////////////////////////////

class CPlayerControlNpc : public NLMISC::CRefCount
{
public:
	/// ctor
	/// \param player : the player which controls the bot
	/// \param bot : the npc which is controlled by the player
	CPlayerControlNpc(CBotPlayer* player, CSpawnBotNpc* bot);
	~CPlayerControlNpc();

	/// check if the object is valid
	/// WARNING: you cannot call any other method if this returns false
	bool isValid() const;

	/// update the control on the npc
	void updateControl(uint ticks);
	CSpawnBotNpc* getSpawnBot() const;

private:
	/// the player controlling the bot
	NLMISC::CRefPtr<CBotPlayer>	_Player;
	CSpawnBotNpc*				_Bot;
	CProfilePtr					_ControlProfileManager;
	uint32						_LastPathUpdate;
	NLMISC::CEntityId			_CPlayerEntityId;
	NLMISC::CEntityId			_CNpcEntityId;

};

#endif
