/** \file player_room.h
 * <File description>
 *
 * $Id: player_room.h,v 1.23 2007/05/09 15:33:38 boucher Exp $
 */


#ifndef RY_PLAYER_ROOM_H
#define RY_PLAYER_ROOM_H

#include "game_item_manager/game_item_manager.h"


class CBuildingPhysicalPlayer;
/**
 * A player room interface
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CPlayerRoomInterface
{
	NL_INSTANCE_COUNTER_DECL(CPlayerRoomInterface);
public:

	/// ctor
	CPlayerRoomInterface();

	/// dtor
	~CPlayerRoomInterface();

	/// persistence methods
	void store(CPersistentDataRecord & pdr) const;
	void apply(CPersistentDataRecord & pdr, CCharacter * owner);

	/// clear player room
	void clear();

	/// return the destination where the room physically is
	const CBuildingPhysicalPlayer * getBuilding()
	{
		if (_Data == NULL)
			return NULL;
		return _Data->Building;
	}

	/// init the room. Should be called when a user buys it
	void init(CCharacter * owner, CBuildingPhysicalPlayer * building);

	/// serial of the interface
//	void serial(NLMISC::IStream & f, CCharacter * owner, uint16 playerVersion);

	/// return true if char is allowed in the building
	bool isAllowedInBuilding(const CCharacter * owner, const CCharacter * user);

	/// return true if user can use inventory
	bool canUseInventory(const CCharacter * owner, const CCharacter * user) const;

	/// return the building inventory
	CInventoryPtr getInventory() const
	{
		if (_Data == NULL)
			return NULL;
		return _Data->Inventory;
	}

	/// return true if the player has a room
	bool isValid() const { return _Data != NULL; }


private:
	/// internal data accessed through the interface
	class CPlayerRoomData
	{
	public:
		DECLARE_PERSISTENCE_METHODS

		/// ctor
		CPlayerRoomData(CCharacter * owner, CBuildingPhysicalPlayer * building);

		/// initialize the inventory
		void initInventory(CCharacter * owner);

		/// clear
		void clear();

		/// serial
//		void serial(NLMISC::IStream & f, CCharacter * owner, uint16 playerVersion);

	public:
		/// the room inventory
		CInventoryPtr Inventory;

		/// the building where the room is
		CBuildingPhysicalPlayer * Building;
	};

	CPlayerRoomData * _Data;
};



#endif // RY_PLAYER_ROOM_H

/* End of player_room.h */
