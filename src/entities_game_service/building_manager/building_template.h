/** \file building_template.h
 * <File description>
 *
 * $Id: building_template.h,v 1.8 2005/06/23 18:04:44 boucher Exp $
 */


#ifndef RY_BUILDING_TEMPLATE_H
#define RY_BUILDING_TEMPLATE_H

#include "game_share/lift_icons.h"
#include "building_enums.h"
#include "mission_manager/ai_alias_translator.h"

class CBuildingTemplate;


/// structure containing intermediate data used during building parsing only
struct CBuildingParseData
{
	/// buildings templates sorted by names
	std::map< std::string, CBuildingTemplate *> BuildingTemplates;
};


/**
 * A room template. Used to describe a room organization and content . Example : THE fyros guild council room
 * data are public, as room templates are always const after parsing
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CRoomTemplate
{
public:
	/// build room fromm data
	bool build ( const NLLIGO::IPrimitive* prim, CBuildingParseData & parseData );

	/// name of the room
	std::string									Name;
	/// name id to display on client
	std::string									PhraseId;
	/// icon  to display on client
	LIFT_ICONS::TLiftIcon						Icon;
	/// names of the bot
	std::vector< TAIAlias >						Bots;
	/// restriction to go to this destination
	std::vector<ROOM_RESTRICTION::TRestriction> Restrictions;
};

/**
 * A building template. Used to describe a building organization and content. Example : THE fyros guild building
 * data are public, as building templates are always const after parsing
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CBuildingTemplate
{
	NL_INSTANCE_COUNTER_DECL(CBuildingTemplate);
public:
	/// build the template from data.
	bool build ( const NLLIGO::IPrimitive* prim, CBuildingParseData & parseData );

	/// type of the building
	BUILDING_TYPES::TBuildingType	Type;
	/// rooms in the building
	std::vector<CRoomTemplate>		Rooms;
};



	



#endif // RY_BUILDING_TEMPLATE_H

/* End of building_template.h */
