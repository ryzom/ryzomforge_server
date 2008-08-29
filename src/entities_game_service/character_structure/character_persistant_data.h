/** \character_persistant_data.h
 * 
 *
 * $Id: character_persistant_data.h,v 1.8 2006/01/10 17:38:55 boucher Exp $
 */



#ifndef RY_CHARACTER_PERSISTANT_DATA_H
#define RY_CHARACTER_PERSISTANT_DATA_H

#include "game_share/mirror_prop_value.h"
#include "game_share/player_visual_properties.h"
#include "game_share/character_title.h"
#include "server_share/entity_state.h"

#include "character_structure/pact_class.h"
#include "character_structure/character_sentence.h"
#include "character_structure/known_brick_info.h"
#include "game_item_manager/game_item.h"

/**
 * CCharacterBasePersistantData
 * \author Alain Saffray
 * \author Nevrax France
 * \date 2001
 */
class CCharacterPersistantData
{
public:

	/**
	 * \return the current version of the class. Useful for managing old versions of saved players
	 * WARNING : the version number should be incremented when the serial method is modified
	 */
	static inline uint16 getCurrentVersion() { return 4; }

	// Character Title
	CHARACTER_TITLE::ECharacterTitle	_Title;

	/// Pacts and type with kami or the caravan(give the number of deaths allowed)
	std::vector< CPact >	_Pact;
	uint8								_NbSurvivePact;

	/// Visual properties for player character
	CMirrorPropValueAlice< SPropVisualA, CPropLocationPacked<2> > _VisualPropertyA;
	CMirrorPropValueAlice< SPropVisualB, CPropLocationPacked<2> > _VisualPropertyB;
	CMirrorPropValueAlice< SPropVisualC, CPropLocationPacked<2> > _VisualPropertyC;
	uint8						_HairType;
	uint8						_HairColor;
	uint8						_HatColor;
	uint8						_JacketColor;
	uint8						_ArmsColor;
	uint8						_TrousersColor;
	uint8						_FeetColor;
	uint8						_HandsColor;
	
	/// Memorized Sentences for magic
//	std::vector< CCharacterSentence * >	_MemorizedSentencesMagic;
	/// Memorized Sentences for combat
//	std::vector< CCharacterSentence * >	_MemorizedSentencesCombat;
	/// Memorized Sentences for special sentences / bricks
	//std::vector< CCharacterSentence * >	_MemorizedSentencesSpecial;
	
	/// inventory of known bricks (map Id to Latency end date)
	std::map< NLMISC::CSheetId, CKnownBrickInfo >		_KnownBricks;

	/// the known faber plans for that player (directly the reflect of the database)
//	std::vector<uint64>									_KnownFaberPlans;

	/// inventories of character
//	std::vector< CGameItemPtr >  _Inventory;
//	std::vector< CInventory >  _Inventory;
//	CInventoryBase		_Inventory[INVENTORIES::NUM_INVENTORY];
	CInventoryPtr		_Inventory[INVENTORIES::NUM_INVENTORY];
};

#endif // RY_CHARACTER_PERSISTANT_DATA_H
/* character_persistant_data.h */
