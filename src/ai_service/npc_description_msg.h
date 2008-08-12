/** \file npc_description_msg.h
 *
 * $Id: npc_description_msg.h,v 1.25 2006/12/06 17:22:05 boucher Exp $
 */



#ifndef RYAI_NPC_DESCRIPTION_MSG_H
#define RYAI_NPC_DESCRIPTION_MSG_H

#include "game_share/npc_description_messages.h"

//----------------------------------------------------------------
// class used to describe a bot's chat possibilities
//----------------------------------------------------------------
class	CAIInstance;

class	CNpcChatProfileImp : public CNpcChatProfile, public NLMISC::CRefCount
{
	/// A list of cell zone names for witch this bot can give dynamic mission.
	std::vector<std::string>	_CellZones;
public:
	// ctor
	CNpcChatProfileImp() {}
	CNpcChatProfileImp(const CNpcChatProfileImp &other0,const CNpcChatProfileImp &other1);

	// interface for setting up chat info 
	void clear()					{ clearShopInfo(); clearMissions(); clearCellZones(); clearContextOption(); _OptionalProperties.clear(); }
	void clearShopInfo()			
	{ 
		_ShopTypes.clear(); 
		_ExplicitSales.clear();
//		_shopTypesNegators.clear(); 
//		_shopItemTypes.clear(); 
//		_shopItemQualities.clear(); 
//		_shopItemPrices.clear(); 
//		_shopItemFactionTypes.clear(); 
//		_shopItemFactionPointPrices.clear();
//		_shopItemTypesNegators.clear();
//		_shopItemQualitiesNegators.clear(); 
//		_ExplicitActionTradeList.clear();
		_FilterExplicitActionTradeByPlayerRace= false;
		_ExplicitActionSPType= EGSPD::CSPType::Unknown;
		_FilterExplicitActionTradeByBotRace = true;
	}
	void clearCellZones()			{ _CellZones.clear(); }
	void clearMissions()			{ _Missions.clear(); }
	bool add(CAIInstance	*aiInstance, const std::string &chatArgs)	{ return parseChatArgs(aiInstance, chatArgs); }
	void addMission(uint32 mission)	{ _Missions.push_back(mission); }
	void clearContextOption()		{ _ContextOptions.clear();  }
	void addContextOption(const std::string menuId, const std::string contentId) { RYMSG::TContextOption co; co.setTitle(menuId); co.setDetail(contentId); _ContextOptions.push_back(co); }

	// interface for interpreting chat info
//	const std::vector<uint32>			&getShopTypes() const		{ return _shopTypes; }
//	const std::vector<NLMISC::CSheetId>	&getShopItemTypes() const	{ return _shopItemTypes; }
//	const std::vector<uint32>			&getShopItemQualities() const	{ return _shopItemQualities; }
//	const std::vector<uint32>			&getMissions() const		{ return _Missions; }
	const std::vector<std::string>		&getCellZones() const		{ return _CellZones; }

	static CNpcChatProfileImp combineChatProfile(const CNpcChatProfileImp &referenceChat, const CNpcChatProfileImp &currentChat);

	bool parseChatArgs(CAIInstance	*aiInstance,const std::string &args);
};



class TGenNpcDescMsgImp : public RYMSG::TGenNpcDescMsg
{
public:
	// handy write accessors
	void	setChat(const CNpcChatProfileImp& chatProfile);

	void forceNoChat()
	{
		getShopCategories().clear();
		getShopCategories().push_back(0);
	}

};

#endif //RYAI_NPC_DESCRIPTION_MSG_H
