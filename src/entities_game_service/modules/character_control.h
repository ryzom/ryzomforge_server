/** \file character_control.h
 * <File description>
 *
 * $Id: character_control.h,v 1.5 2006/10/31 16:09:06 blanchard Exp $
 */

#ifndef NL_CHARACTER_CONTROL_H
#define NL_CHARACTER_CONTROL_H

#include "nel/misc/types_nl.h"
#include "nel/misc/singleton.h"

#include "game_share/far_position.h"
#include "game_share/scenario.h"

#include "modules/character_control.h"
#include "modules/r2_mission_item.h"

class ICharacterControl
:	public NLMISC::CManualSingleton<ICharacterControl>
{
public:

	virtual void requestStartParams( const NLMISC::CEntityId& entityId, TSessionId lastStoredSessionId ) = 0;
	
	virtual void requestEntryPoint( const NLMISC::CEntityId& entityId ) = 0;

	virtual void sendItemDescription( TSessionId scenarioId, const std::vector<R2::TMissionItem> &missionItem ) = 0;

	virtual void scenarioEnded( TSessionId scenarioId ) = 0;

	virtual void stealMissionItem( const NLMISC::CEntityId &eid, const std::vector<R2::TItemAndQuantity> &items ) = 0;
	
	virtual void getMissionItemOwnedByCharacter(const NLMISC::CEntityId & eid) = 0;

	virtual void activateEasterEgg(uint32 easterEggId, TSessionId scenarioId, uint32 aiInstanceId, const std::vector< R2::TItemAndQuantity > &items, const CFarPosition &pos, const std::string& name, const std::string & look) =0;
	
	virtual void deactivateEasterEgg(uint32 easterEggId, TSessionId scenarioId) =0;

	virtual void getEasterEggDropped(TSessionId scenarioId, std::vector<R2::TEasterEggInfo> &easterEgg ) =0;

	virtual void lootEasterEggEvent( uint32 externalEasterEggId, TSessionId scenarioId ) =0;

	virtual TSessionId getSessionId(TSessionId sessionId) const = 0;

	virtual void characterReady(const NLMISC::CEntityId &entityId) =0;
};


#endif // NL_CHARACTER_CONTROL_H

/* End of character_control.h */
