/** \file mission_item.h
 * <File description>
 *
 * $Id: mission_item.h,v 1.8 2005/02/22 10:22:34 besson Exp $
 */



#ifndef RY_MISSION_ITEM_H
#define RY_MISSION_ITEM_H

#include "game_share/string_manager_sender.h"
#include "game_item_manager/game_item.h"

class CCharacter;
/**
 * class used to described a mission item
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CMissionItem
{
public:
	/// build this class from a script. Return true on success, and add the item chat param to the parameter list
	bool buildFromScript( const std::vector<std::string> & script, std::vector< std::pair< std::string, STRING_MANAGER::TParamType > > & chatParams, std::string & varName );
	/// create an ingame item from this class and put it in user temp inventory
	CGameItemPtr createItemInTempInv(CCharacter * user, uint16 quantity);
	/// create an item from the mission item data
	CGameItemPtr createItem(uint16 quantity);
	/// return the quality
	uint16 getQuality() { return _Quality; }
	/// return the quality
	const NLMISC::CSheetId & getSheetId() { return _SheetId; }
private:
	// set a created item parameter
	void setItemParam(CGameItemPtr item);

	
	/// sheet describing the item type
	NLMISC::CSheetId		_SheetId;
	/// parameters of the item
	CCraftParameters		_Params;
	/// quality of the item
	uint16					_Quality;
	/// phrase id of the item ( its name in most cases )
	std::string				_PhraseId;
	/// true if the item cant be dropped
	bool					_NoDrop;
	/// sheet of the phrase
	NLMISC::CSheetId		_SPhraseId;
};


#endif // RY_MISSION_ITEM_H

/* End of mission_item.h */
