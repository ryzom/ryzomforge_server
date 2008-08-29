/** \file npc_description_messages.cpp
 *
 * $Id: npc_description_messages.cpp,v 1.14 2007/06/12 17:06:04 verquerre Exp $
 */




//----------------------------------------------------------------------------

#include "stdpch.h"

#include "nel/misc/types_nl.h"
#include "nel/misc/common.h"
#include "nel/misc/command.h"
#include "nel/misc/path.h"
#include "npc_description_messages.h"
#include "../../server/src/ai_share/ai_share.h"

using namespace NLMISC;
//using namespace NLNET;
using namespace std;


//---------------------------------------------------------------------------------------
// Stuff used for management of log messages

bool VerboseNpcDescriptionMsgLog=false;
#define LOG if (!VerboseNpcDescriptionMsgLog) {} else nlinfo




CNpcChatProfile::CNpcChatProfile(const CNpcChatProfile &other0,const CNpcChatProfile &other1)
{
	uint i,j;

	// run through shop types in other0 - trying to add to output shop type list
	for (i=0;i<other0.getShopTypes().size();++i)
	{
		// make sure shop type isn't listed in other1's negation vector
//		for (j=0;j<other1._shopTypesNegators.size();++j)
//			if (other0._shopTypes[i]==other1._shopTypesNegators[j])
//				break;
//		if (j<other1._shopTypesNegators.size())
//			continue;

		// not found in negator list so add to output list
		_ShopTypes.push_back(other0._ShopTypes[i]);
	}

	// run through shop types in other1 - trying to add to output shop type list
	for (i=0;i<other1._ShopTypes.size();++i)
	{
		// make sure shop type isn't listed in other0's negation vector
//		for (j=0;j<other0._shopTypesNegators.size();++j)
//			if (other1._shopTypes[i]==other0._shopTypesNegators[j])
//				break;
//		if (j<other0._shopTypesNegators.size())
//			continue;

		// make sure shop type isn't already in output list
		for (j=0;j<_ShopTypes.size();++j)
			if (other1._ShopTypes[i]==_ShopTypes[j])
				break;
		if (j<_ShopTypes.size())
			continue;

		// not found in negator list or existing output list so add it now
		_ShopTypes.push_back(other0._ShopTypes[i]);
	}

	// run through shop item types in other0 - trying to add to output shop item type list
	for (i=0;i<other0._ExplicitSales.size();++i)
	{
		// make sure shop item type isn't listed in other1's negation vector
//		for (j=0;j<other1._shopItemTypesNegators.size();++j)
//			if (other0._shopItemTypes[i]==other1._shopItemTypesNegators[j] && other0._shopItemQualities[i]==other1._shopItemQualitiesNegators[j])
//				break;
//		if (j<other1._shopItemTypesNegators.size())
//			continue;

		_ExplicitSales.push_back(other0._ExplicitSales[i]);

//		// not found in negator list so add to output list
//		_shopItemTypes.push_back(other0._shopItemTypes[i]);
//		_shopItemQualities.push_back(other0._shopItemQualities[i]);
//		_shopItemPrices.push_back(other0._shopItemPrices[i]);
//		_shopItemFactionTypes.push_back(other0._shopItemFactionTypes[i]);
//		_shopItemFactionPointPrices.push_back(other0._shopItemFactionPointPrices[i]);
	}

	// run through shop item types in other1 - trying to add to output shop item type list
	for (i=0;i<other1._ExplicitSales.size();++i)
	{
		// make sure shop item type isn't listed in other0's negation vector
//		for (j=0;j<other0._shopItemTypesNegators.size();++j)
//			if (other1._shopItemTypes[i]==other0._shopItemTypesNegators[j] && other1._shopItemQualities[i]==other0._shopItemQualitiesNegators[j])
//				break;
//		if (j<other0._shopItemTypesNegators.size())
//			continue;
//
		// make sure shop item type isn't already in output list
		for (j=0;j<_ExplicitSales.size();++j)
			if (other1._ExplicitSales[i]==_ExplicitSales[j])
				break;
		if (j<_ExplicitSales.size())
			continue;

		// not found in negator list or existing output list so add it now
		_ExplicitSales.push_back(other1._ExplicitSales[i]);
//		_shopItemTypes.push_back(other1._shopItemTypes[i]);
//		_shopItemQualities.push_back(other1._shopItemQualities[i]);
//		_shopItemPrices.push_back(other1._shopItemPrices[i]);
//		_shopItemFactionTypes.push_back(other1._shopItemFactionTypes[i]);
//		_shopItemFactionPointPrices.push_back(other1._shopItemFactionPointPrices[i]);
	}

	// run through missions in other0 - trying to add to output mission list
	_Missions=other0._Missions;
	for (i=0;i<other1._Missions.size();++i)
	{
		// make sure mission isn't listed in other0's negation vector
//		for (j=0;j<other0._missionsNegators.size();++j)
//			if (other1._missions[i]==other0._missionsNegators[j])
//				break;
//		if (j<other0._missionsNegators.size())
//			continue;

		// make sure shop type isn't already in output list
		for (j=0;j<_Missions.size();++j)
			if (other1._Missions[i]==_Missions[j])
				break;
		if (j<_Missions.size())
			continue;

		// not found in existing output list so add it now
		_Missions.push_back(other1._Missions[i]);
	}

//	LOG("+ Combining:%s",buildChatDebugString(other0._shopTypes, other0._shopItemTypes, other0._missions).c_str());
//	LOG("+ With     :%s",buildChatDebugString(other1._shopTypes, other1._shopItemTypes, other1._missions).c_str());
//	LOG("= Result   :%s",buildChatDebugString(_shopTypes, _shopItemTypes, _missions).c_str());
}

void CCustomElementId::serial(NLMISC::IStream &f)
{
	f.serial(PrimAlias);
	f.serial(Id);
}


void CScriptData::serial(NLMISC::IStream &f)
{
	uint16 size;
	if (f.isReading())
	{
		scripts.clear();
		f.serial(size);

		uint32 i = 0;
		for (; i < size; ++i)
		{
			//std::string tmpKey;
			CCustomElementId tmpKey;
			std::vector<std::string> tmpVal;
			f.serial(tmpKey);
			f.serialCont(tmpVal);
			scripts.insert(make_pair(tmpKey,tmpVal));
		}
	}
	else
	{
		size = scripts.size();
		f.serial(size);	
		for (TScripts::iterator it = scripts.begin(); it != scripts.end(); ++it)
		{
			//std::string tmp = it->first;			
			nlWrite(f, serial, it->first);
			nlWrite(f, serialCont, it->second);			
		}
	}
}

void CCustomLootTable::serial(NLMISC::IStream &f)
{
	f.serial(lootSets);
	f.serial(moneyFactor);
	f.serial(moneyProba);
	f.serial(moneyBase);
}

void CCustomLootTableManager::serial(NLMISC::IStream &f)
{
	uint16 size;
	if (f.isReading())
	{	
		tables.clear();
		f.serial(size);

		uint32 i = 0;
		for (; i < size; ++i)
		{
			//std::string tmpKey;
			CCustomElementId tmpKey;
			CCustomLootTable tmpVal;
			f.serial(tmpKey);
			f.serial(tmpVal);
			tables.insert(make_pair(tmpKey,tmpVal));
		}
	}
	else
	{
		size = tables.size();
		f.serial(size);	
		for (TCustomLootTable::iterator it = tables.begin(); it != tables.end(); ++it)
		{
			nlWrite(f, serial, it->first);
			nlWrite(f, serial, it->second);
		}


	}
}


//---------------------------------------------------------------------------------------
// Control over verbose nature of logging
//---------------------------------------------------------------------------------------

NLMISC_COMMAND(verboseNpcDescriptionMsgLog,"Turn on or off or check the state of verbose AI->EGS NPC description message logging","")
{
	if(args.size()>1)
		return false;

	if(args.size()==1)
	{
		if(args[0]==string("on")||args[0]==string("ON")||args[0]==string("true")||args[0]==string("TRUE")||args[0]==string("1"))
			VerboseNpcDescriptionMsgLog=true;

		if(args[0]==string("off")||args[0]==string("OFF")||args[0]==string("false")||args[0]==string("FALSE")||args[0]==string("0"))
			VerboseNpcDescriptionMsgLog=false;
	}

	nlinfo("verbose Logging is %s",VerboseNpcDescriptionMsgLog?"ON":"OFF");
	return true;
}

//---------------------------------------------------------------------------------------
