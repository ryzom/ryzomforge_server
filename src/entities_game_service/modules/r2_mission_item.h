/** \file r2_mission_item.h
 * Keep definition of R2 item per scenario (instance of) and manage 
 * instanciated item of that type with specifics rules of persistance.
 *
 * $Id: r2_mission_item.h,v 1.3 2006/09/14 17:04:21 cado Exp $
 */

#ifndef R2_MISSION_ITEM_H
#define R2_MISSION_ITEM_H

#include <string>
#include <vector>
#include <map>

#include "nel/misc/types_nl.h"
#include "nel/misc/singleton.h"
#include "nel/misc/entity_id.h"
#include "game_share/scenario.h"

#include "game_item_manager/game_item.h"

extern const uint32 MaxItemTypePerScenario;

class CR2MissionItem : public NLMISC::CSingleton<CR2MissionItem>
{
public:

	typedef TSessionId TScenarioId;
	typedef std::map< TScenarioId, std::vector< R2::TMissionItem> > TMissionItemContainer;
	typedef std::map< TScenarioId, std::vector< NLMISC::CEntityId > > TMissionItemInstanciatedOwner;
	
	// ctor/dtor
	CR2MissionItem() {}
	~CR2MissionItem();

	// a new scenario send it's used items descriptions
	void itemsDescriptionsForScenario(TScenarioId scenarioId, const std::vector<R2::TMissionItem> &missionItem);

	// a scenario ended, we must destroy all it's item (descriptions and instance)
	void endScenario(TScenarioId scenarioId);

	// give a scenario item to a player character
	void giveMissionItem(const NLMISC::CEntityId &eid, TScenarioId scenarioId, const std::vector< R2::TItemAndQuantity > &items);

	// a character is disconnected, we must destroy all it's item scenario instance
	void characterDisconnection(const NLMISC::CEntityId &eid);

	// return a reference on definition of mission item
	const R2::TMissionItem * getR2ItemDefinition(TScenarioId scenarioId, const NLMISC::CSheetId &itemSheetId) const;

	// destroy a mission item on character inventory (destroy it)
	void destroyMissionItem(const NLMISC::CEntityId &eid, const std::vector< R2::TItemAndQuantity > &items);

	// return number of mission item a player character have
	uint32 getNumberMissionItem(const NLMISC::CEntityId &eid, const NLMISC::CSheetId &itemSheetId) const;

	// return R2 mission item a player character have
	void getMissionItemOwnedByCharacter(const NLMISC::CEntityId & eid, std::vector< R2::TItemAndQuantity > &items) const;

	// event DM select a character for gift an mission item(s)
	void dmGiftBegin( NLMISC::CEntityId eid );

	// event DM gift item(s) to previous selected character
	void dmGiftValidate( NLMISC::CEntityId eid, std::vector< R2::TItemAndQuantity > items );

	// keep R2 item owner association
	void keepR2ItemAssociation(const NLMISC::CEntityId& eid, TScenarioId scenarioId);

private:
	void _removeAllR2ItemsOfInventories(const NLMISC::CEntityId &eid, std::vector< CGameItemPtr > *items = NULL);
	void _removeAllR2ItemsOfInventory(CInventoryPtr inv, std::vector< CGameItemPtr > *items = NULL);
	void _destroyMissionItem(CInventoryPtr inv, const NLMISC::CSheetId &itemSheetId, uint32 &quantity);
	uint32 _getNumberMissionItem(CInventoryPtr inv, const NLMISC::CSheetId &itemSheetId) const;
	void _getMissionItemOwnedByCharacter( CInventoryPtr inv, std::vector< R2::TItemAndQuantity > &items) const;


private:
	TMissionItemContainer								_ScenarioMissionItemsDef;
	TMissionItemInstanciatedOwner						_OwnerOfInstanciatedItemFromScenario;
	std::map< NLMISC::CEntityId, NLMISC::CEntityId >	_DMSelectedPlayer;
};

#endif
