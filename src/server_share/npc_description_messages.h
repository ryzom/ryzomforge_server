/** \file npc_description_messages.h
 *
 * $Id: npc_description_messages.h,v 1.56 2007/05/30 16:32:23 verquerre Exp $
 */



#ifndef RY_NPC_DESCRIPTION_MESSAGES_H
#define RY_NPC_DESCRIPTION_MESSAGES_H

#include "nel/misc/types_nl.h"
#include "nel/misc/sheet_id.h"
#include "nel/misc/entity_id.h"
#include "nel/net/transport_class.h"
#include "game_share/msg_ais_egs_gen.h"
#include "game_share/base_types.h"
#include "game_share/synchronised_message.h"
#include "game_share/sp_type.h"


//----------------------------------------------------------------
// Logging and debugging stuff...
//----------------------------------------------------------------

// The following serve for controling verbose nature of logging - LOG is undefined at end of file
extern bool VerboseNpcDescriptionMsgLog;
#define LOG if (!(VerboseNpcDescriptionMsgLog && Mode==4)) {} else nlinfo

// build a man-readable description of a chat parameter set fomr component parts
std::string buildChatDebugString(const std::vector<uint32> &ShopCategories,
								 const std::vector<NLMISC::CSheetId> &ItemTypesForSale,
								 const std::vector<uint32> &MissionIds);

//----------------------------------------------------------------
// class used to describe a bot's chat possibilities
//----------------------------------------------------------------

class CNpcChatProfile
{
public:
	CNpcChatProfile() : /*_guildCreator(false),*/ /*_dynamicMissionGiver(false),*/ _FilterExplicitActionTradeByPlayerRace(false), 
		_ExplicitActionSPType(EGSPD::CSPType::Unknown), _FilterExplicitActionTradeByBotRace(true){}
	CNpcChatProfile(const CNpcChatProfile &other0,const CNpcChatProfile &other1);
	virtual ~CNpcChatProfile() {}

	// interface for interpreting chat info
	const std::vector<uint32>			&getShopTypes()	const		{ return _ShopTypes; }
	const std::vector< RYMSG::TExplicitSale >	getExplicitSales() const	{ return _ExplicitSales; }
//	const std::vector<NLMISC::CSheetId>	&getShopItemTypes()	{ return _shopItemTypes; }
//	const std::vector<uint32>			&getShopItemQualities()	{ return _shopItemQualities; }
//	const std::vector<sint32>			&getShopItemPrices() const { return _shopItemPrices; }
//	const std::vector<uint8>			&getShopItemFactionTypes()	const { return _shopItemFactionTypes; }
//	const std::vector<uint32>			&getShopItemFactionPointPrices() const	{ return _shopItemFactionPointPrices; }
	const std::vector<uint32>			&getMissions()	const	{ return _Missions; }
//	bool								getGuildCreator() const{ return _GuildCreator; } 
	bool								getDynamicMissionGiver() const { return _DynamicMissionGiver;}
	const std::vector<std::string>		&getNewsChannels() const { return _NewsChannels; }
	const std::vector< RYMSG::TContextOption >	&getContextOptions() const	{ return _ContextOptions; };
//	const std::vector<std::string>		&getContextOptionsTitles() const  { return _ContextOptionsTitles;}
//	const std::vector<std::string>		&getContextOptionsDetails() const  { return _ContextOptionsDetails;}
	const std::vector<std::string>		&getOptionalProperties() const  { return _OptionalProperties;}

//	const std::vector<std::string>		&getShopNamedItemNames() const { return _shopNamedItemNames; }
//	const std::vector<uint32>			&getShopNamedItemPrices() const { return _shopNamedItemPrices; }
//	const std::vector<uint8>			&getShopNamedItemFactionTypes() const { return _shopNamedItemFactionTypes; }
//	const std::vector<uint32>			&getShopNamedItemFactionPointPrices() const { return _shopNamedItemFactionPointPrices; }

//	const std::vector<NLMISC::CSheetId>	&getExplicitActionTradeList() const	{ return _ExplicitActionTradeList; }
	bool								getFilterExplicitActionTradeByPlayerRace() const {return _FilterExplicitActionTradeByPlayerRace;}
	EGSPD::CSPType::TSPType				getExplicitActionSPType() const {return _ExplicitActionSPType;}
	bool								getFilterExplicitActionTradeByBotRace() const {return _FilterExplicitActionTradeByBotRace;}
	
	const std::string					&getWelcomePhrase() const	{ return _WelcomePhrase; }
	const std::string					&getWebPage() const			{ return _WebPage; }
	const std::string					&getWebPageName() const		{ return _WebPageName; }

	const NLMISC::CSheetId				&getOutpost() const			{ return _Outpost; }
	
protected:
	std::vector< RYMSG::TExplicitSale >	_ExplicitSales;
//	std::vector<NLMISC::CSheetId>	_shopItemTypes;			// list of specific items to be found in shop
//	std::vector<uint32>				_shopItemQualities;		// list of quality of specific item
//	std::vector<sint32>				_shopItemPrices;		// list of specific item prices. -1 indicate "use standard price"
//	std::vector<uint8>				_shopItemFactionTypes;
//	std::vector<uint32>				_shopItemFactionPointPrices;
//	std::vector<NLMISC::CSheetId>	_shopItemTypesNegators;	// field used when combining chat profiles
//	std::vector<uint32>				_shopItemQualitiesNegators;	// list of quality of specific item
	std::vector<uint32>				_ShopTypes;				// categories of shop inventory to include
//	std::vector<uint32>				_shopTypesNegators;		// field used when combining chat profiles 

//	std::vector<std::string>		_shopNamedItemNames;
//	std::vector<uint32>				_shopNamedItemPrices;
//	std::vector<uint8>				_shopNamedItemFactionTypes;
//	std::vector<uint32>				_shopNamedItemFactionPointPrices;

//	std::vector<NLMISC::CSheetId>	_ExplicitActionTradeList;	// list of specific actions to be found in shop
	bool							_FilterExplicitActionTradeByPlayerRace;
	EGSPD::CSPType::TSPType			_ExplicitActionSPType;
	bool							_FilterExplicitActionTradeByBotRace;
	
	std::vector<uint32>				_Missions;				// array of mission aliases
//	std::vector<uint32>				_missionsNegators;		// field used when combining chat profiles
	std::string						_WelcomePhrase;			// The welcome message
	std::string						_WebPage;				// The web page
	std::string						_WebPageName;			// The web page name (server phrase id)
//	bool							_GuildCreator;			// true if the bot proposes guild creation
	bool							_DynamicMissionGiver;	// true if this bot give dynamic mission
	std::vector<std::string>		_NewsChannels;			// List of news channel.
	std::vector< RYMSG::TContextOption >	_ContextOptions;
	/// titles of the bot context options ContextOptionsDetails.size() == ContextOptionsTitles.size()
//	std::vector< std::string >		_ContextOptionsTitles;
	/// detail text of the option WARNING: we assert that ContextOptionsDetails.size() == ContextOptionsTitles.size()
//	std::vector< std::string >		_ContextOptionsDetails;

	/// optional and rare properties
	std::vector<std::string>		_OptionalProperties;
	
	NLMISC::CSheetId				_Outpost;
};

//----------------------------------------------------------------
// Message sent by AIS to EGS in reaction to EGS's service up 
// Messages also sent when new NPC entities are spawned
//----------------------------------------------------------------

//----------------------------------------------------------------
// Descrition of an NPC bot
//class CNpcBotDescription : public CMirrorTransportClass
//{
//public:
//	CNpcBotDescription	()
//	{
//	}
//	// public data
//	uint32				Alias;
//	uint32				GrpAlias;
//	std::vector<uint32> MissionIds;
//
//	std::vector<uint32>				ShopCategories;
//
//	// Standard Explicit Item
//	std::vector<NLMISC::CSheetId>	ItemTypesForSale;
//	std::vector<uint32>				ItemQualitiesForSale;
//	std::vector<sint32>				ItemPrices;				// -1 indicate: use standard price, else use specific price
//	std::vector<uint8>				ItemFactionType;		// PVP_CLAN::TPVPClan
//	std::vector<uint32>				ItemFactionPointPrice;
//	
//	// Named Item
//	std::vector<std::string>	NamedItemName;				// must correspond to a phrase id (in named_items.txt)
//	std::vector<uint32>			NamedItemPrice;
//	std::vector<uint8>			NamedItemFactionType;		// PVP_CLAN::TPVPClan
//	std::vector<uint32>			NamedItemFactionPointPrice;
//
//	// Explicit .sphrase Actions
//	std::vector<NLMISC::CSheetId>	ExplicitActionTradeList;
//	bool							FilterExplicitActionTradeByPlayerRace;
//	uint32							ExplicitActionSPType;
//	bool							FilterExplicitActionTradeByBotRace;
//	
//	std::string			WelcomePhrase;
//	std::string			WebPage;
//	std::string			WebPageName;
//	NLMISC::CSheetId	Sheet;
//	TDataSetRow			EntityIndex;
//	bool				PlayerAttackable;
//	bool				BotAttackable;
//	// active sheath description
//	NLMISC::CSheetId	RightHandItem;
//	NLMISC::CSheetId	LeftHandItem;
//	uint8				RightHandItemQuality;
//	uint8				LeftHandItemQuality;
//	/// True if this bot can give dynamic mission
//	bool				DynamicMissionGiver;
//	bool				DontFollow;
//	// if that bot is a building bot it will be caught by outpost system
//	bool				BuildingBot;
//
//	/// optionnal and rare properties
//	std::vector< std::string > OptionalProperties;
//
//
//	/// List of news channel.
//	std::vector<std::string>	NewsChannels;
//
//	/// titles of the bot context options ContextOptionsDetails.size() == ContextOptionsTitles.size()
//	std::vector< std::string > ContextOptionsTitles;
//	/// detail text of the option WARNING: we assert that ContextOptionsDetails.size() == ContextOptionsTitles.size()
//	std::vector< std::string > ContextOptionsDetails;
//
//	std::vector<NLMISC::CSheetId>	lootList;				// list of loot 
//	
//	NLMISC::CSheetId	Outpost;

//	float				MaxHitRangeForPC;	// Max effective hit range for PC against this npc
	
//	virtual void description ()
//	{
//		className ("CNpcBotDescription");
//		property ("alias", PropUInt32, (uint32)0, Alias);
//		property ("grpAlias", PropUInt32, (uint32)0, GrpAlias);
//		property ("serverSheet", PropSheetId, NLMISC::CSheetId::Unknown,Sheet);
//		property ("entityIndex", PropDataSetRow, TDataSetRow(), EntityIndex);
//		property ("playerAttackable", PropBool, false, PlayerAttackable);
//		property ("botAttackable", PropBool, false, BotAttackable);
//		propertyCont ("missions", PropUInt32, MissionIds);
//		propertyCont ("shopTypes", PropUInt32, ShopCategories);
//		propertyCont ("shopItemTypes", PropSheetId, ItemTypesForSale);
//		propertyCont ("shopItemQualities", PropUInt32, ItemQualitiesForSale);
//		propertyCont ("shopItemPrices", PropSInt32, ItemPrices);
//		propertyCont ("shopItemFactionType", PropUInt8, ItemFactionType);
//		propertyCont ("shopItemFactionPointPrice", PropUInt32, ItemFactionPointPrice);
//		
//		propertyCont ("shopNItemName", PropString, NamedItemName);
//		propertyCont ("shopNItemPrice", PropUInt32, NamedItemPrice);
//		propertyCont ("shopNItemFactionType", PropUInt8, NamedItemFactionType);
//		propertyCont ("shopNItemFactionPointPrice", PropUInt32, NamedItemFactionPointPrice);
//
//		propertyCont ("ExplicitActionTradeList", PropSheetId, ExplicitActionTradeList);
//		property ("FilterExplicitActionTradeByPlayerRace", PropBool, false, FilterExplicitActionTradeByPlayerRace);
//		property ("ExplicitActionSPType", PropUInt32, (uint32)0, ExplicitActionSPType);
//		property ("FilterExplicitActionTradeByBotRace", PropBool, true, FilterExplicitActionTradeByBotRace);
//
//		property ("welcomePhrase", PropString, std::string(), WelcomePhrase);
//		property ("webPage", PropString, std::string(), WebPage);
//		property ("webPageName", PropString, std::string(), WebPageName);
//		property ("dynamicMissionGiver", PropBool, false, DynamicMissionGiver);
//		property ("DontFollow", PropBool, false, DontFollow);		
//		property ("BuildingBot", PropBool, false, BuildingBot);		
//
//		propertyCont ("newsChannel", PropString, NewsChannels);
//		
//		property ("rightHandItem", PropSheetId, NLMISC::CSheetId::Unknown, RightHandItem);
//		property ("leftHandItem", PropSheetId, NLMISC::CSheetId::Unknown, LeftHandItem);
//		property ("rightHandItemQuality", PropUInt8, (uint8)0, RightHandItemQuality);
//		property ("leftHandItemQuality", PropUInt8, (uint8)0, LeftHandItemQuality);
//
//		propertyCont ("ContextOptionsTitles",	PropString,  ContextOptionsTitles);
//		propertyCont ("ContextOptionsDetails",	PropString, ContextOptionsDetails);
//		propertyCont ("lootList",				PropSheetId, lootList);
//		propertyCont ("OptionalProperties",		PropString, OptionalProperties);
//		
//		property ("Outpost",		PropSheetId, NLMISC::CSheetId::Unknown, Outpost);
//		
//		
//		LOG("NPC BOT: %8u: %u: %s: %s : RH %s %d: LH %s %d: %s : welcome = '%s' contextTitles size:%u contextDetails size:%u",
//			EntityIndex.getIndex(),
//			Alias,
//			Sheet.toString().c_str(), /*Level,*/
//			"chatDebugStringDisabled",
////			buildChatDebugString(ShopCategories, ItemTypesForSale, MissionIds).c_str(),
//			RightHandItem.toString().c_str(),
//			RightHandItemQuality,
//			LeftHandItem.toString().c_str(),
//			LeftHandItemQuality,
////			AmmoItem.toString().c_str(),
////			AmmoItemQuality,
//			PlayerAttackable ? "Player Attackable" : "NOT Player Attackable",
//			BotAttackable ? "Bot Attackable" : "NOT Bot Attackable",
//			WelcomePhrase.empty() ? "default" : WelcomePhrase.c_str(),
//			ContextOptionsTitles.size(),
//			ContextOptionsDetails.size()
//			);
//	}
//
//	virtual void callback (const std::string &name, NLNET::TServiceId id) {};
//};


//----------------------------------------------------------------
// Descrition of an NPC bot group

//class CNpcGrpDescription : public CMirrorTransportClass
//{
//public:
//	uint32 Alias;
//	NLMISC::CEntityId Eid;
//
//	uint32 grpId() { return (uint32)Eid.getShortId(); }
//	uint32 mgrId() { return (uint32)Eid.getShortId()|0xfffff; }
//
//	virtual void description ()
//	{
//		className ("CNpcGrpDescription");
//		property ("alias", PropUInt32, (uint32)0, Alias);
//		property ("eid", PropEntityId, NLMISC::CEntityId::Unknown, Eid);
//
//		LOG("NPC GRP: %s: %u",Eid.toString().c_str(),Alias);
//	}
//
//	virtual void callback (const std::string &name, NLNET::TServiceId id) {};
//};


//----------------------------------------------------------------
// Descrition of an NPC bot group manager

//class CNpcMgrDescription : public CMirrorTransportClass
//{
//public:
//	uint32 Alias;
//	NLMISC::CEntityId Eid;
//
//	uint32 mgrId() { return (uint32)Eid.getShortId(); }
//
//	virtual void description ()
//	{
//		className ("CNpcMgrDescription");
//		property ("alias", PropUInt32, (uint32)0, Alias);
//		property ("eid", PropEntityId, NLMISC::CEntityId::Unknown, Eid);
//
//		LOG("NPC MGR: %s: %u",Eid.toString().c_str(),Alias);
//	}
//
//	virtual void callback (const std::string &name, NLNET::TServiceId id) {};
//};


//----------------------------------------------------------------
// List of Character starting chat or ending chat with bot

class CCharacterBotChatBeginEnd : public CMirrorTransportClass
{
public:
	// Container contains pair of Player character / bot whith start or end chating
	std::vector< TDataSetRow > BotChatStart;
	std::vector< TDataSetRow > BotChatEnd;
	
	virtual void description ()
	{
		className ("CCharacterBotChatBeginEnd");
		propertyCont ("botChatStart",	PropUInt32, BotChatStart);
		propertyCont ("botChatEnd",		PropUInt32, BotChatEnd);
	}
	
	virtual void callback (const std::string &name, NLNET::TServiceId id) {};
};

class CCharacterDynChatBeginEnd : public CMirrorTransportClass
{
public:
	// Container contains only bot whith start or end chating
	std::vector< TDataSetRow > DynChatStart;
	std::vector< TDataSetRow > DynChatEnd;
	
	virtual void description ()
	{
		className ("CCharacterDynChatBeginEnd");
		propertyCont ("dnChatStart",	PropUInt32, DynChatStart);
		propertyCont ("dnChatEnd",		PropUInt32, DynChatEnd);
	}

	
	virtual void callback (const std::string &name, NLNET::TServiceId id) {};
};

class CCustomElementId
{
public:
	CCustomElementId(uint32 alias = 0, const std::string &id = ""):PrimAlias(alias),Id(id)
	{
	}
	uint32		PrimAlias;
	std::string	Id;
	void serial(NLMISC::IStream &f);
};

inline bool operator<(const CCustomElementId &leftHand, const CCustomElementId &rightHand)
{
	if (leftHand.PrimAlias < rightHand.PrimAlias)
		return true;
	if (leftHand.PrimAlias > rightHand.PrimAlias)
		return false;
	if (leftHand.Id < rightHand.Id)
		return true;
	return false;
}
	


//all script lines
typedef std::vector<std::string> TScriptContent;
//the key is a pair<primAlias, UserModelId>, the value is the content of the script
typedef std::map<CCustomElementId, TScriptContent> TScripts;

//class used for serialization when receiving AIS user_model msg
//also used to represent custom loot set (key : drop proba, value : set script) 
class CScriptData
{
public:
	TScripts scripts;
	void serial(NLMISC::IStream &f);
};



//used for serialization when receiving AIS custom loot table msg
//contains all loot sets of the table, and money infos used for dappers drop
class CCustomLootTable
{
public:
	CScriptData			lootSets;
	float				moneyFactor;
	float				moneyProba;
	sint32				moneyBase;

	void serial(NLMISC::IStream &f);

};

//key : pair<primAlias, customLootTableId>, value : all associated custom loot sets + money info
typedef std::map<CCustomElementId, CCustomLootTable> TCustomLootTable;

class CCustomLootTableManager
{
public:
	TCustomLootTable	tables;
	
	void serial(NLMISC::IStream &f);
};


#undef LOG

//----------------------------------------------------------------
#endif
