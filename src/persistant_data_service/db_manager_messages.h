/** \file db_manager_messages.h
 * <File description>
 *
 * $Id: db_manager_messages.h,v 1.9 2007/03/09 09:56:56 boucher Exp $
 */

#ifndef NL_DB_MANAGER_MESSAGES_H
#define NL_DB_MANAGER_MESSAGES_H

#include <nel/misc/types_nl.h>
#include <nel/net/unified_network.h>


void	cbInitDatabase(NLNET::CMessage& msgin, const std::string &serviceName, NLNET::TServiceId serviceId);
void	cbUpdateDb(NLNET::CMessage& msgin, const std::string &serviceName, NLNET::TServiceId serviceId);
void	cbSheetIdMapping(NLNET::CMessage& msgin, const std::string &serviceName, NLNET::TServiceId serviceId);
//void	cbAddString(NLNET::CMessage& msgin, const std::string &serviceName, NLNET::TServiceId serviceId);

void	cbRBSTaskSuccess(NLNET::CMessage& msgin, const std::string &serviceName, NLNET::TServiceId serviceId);
void	cbRBSTaskFailure(NLNET::CMessage& msgin, const std::string &serviceName, NLNET::TServiceId serviceId);

void	onServiceDown(const std::string &serviceName, NLNET::TServiceId sid, void *arg);

void	onRBSUp(const std::string &serviceName, NLNET::TServiceId sid, void *arg);
void	onRBSDown(const std::string &serviceName, NLNET::TServiceId sid, void *arg);


void	initDbManagerMessages();


class CMessageStat
{
public:

	CMessageStat()
	{
		clear();
	}

	sint32				NumMessages;
	sint32				NumSubMessages;
	sint32				NumUpdateSubMessages;

	sint64				TotalMessagesSize;
	sint64				TotalHeaderSize;

	uint32				SubMessageTypes[32];

	typedef std::map<uint32, uint32>	TUpdateMap;
	TUpdateMap			UpdateMap;
	typedef std::map<uint64, uint32>	TUpdateRowMap;
	TUpdateRowMap		UpdateRowMap;
	typedef std::map<uint64, uint32>	TUpdateTableRowMap;
	TUpdateTableRowMap	UpdateTableRowMap;

	void				addMessage(uint msgSize)
	{
		++NumMessages;
		TotalMessagesSize += msgSize;
	}

	void				addSubMessage(uint headerSize, uint type)
	{
		++NumSubMessages;
		++SubMessageTypes[type];
		TotalHeaderSize += headerSize;
	}

	void				addUpdate(uint16 table, uint32 row, uint16 column)
	{
		uint32	idu = (table << 16) + (column);
		TUpdateMap::iterator	itu = UpdateMap.find(idu);
		if (itu == UpdateMap.end())
		{
			UpdateMap[idu] = 1;
		}
		else
		{
			++((*itu).second);
		}

		uint64	idr = (((uint64)table) << 48) + (((uint64)column) << 32) + row;
		TUpdateRowMap::iterator	itr = UpdateRowMap.find(idr);
		if (itr == UpdateRowMap.end())
		{
			UpdateRowMap[idr] = 1;
		}
		else
		{
			++((*itr).second);
		}

		uint64	idt = (((uint64)table) << 32) + row;
		TUpdateTableRowMap::iterator	itt = UpdateTableRowMap.find(idt);
		if (itt == UpdateTableRowMap.end())
		{
			UpdateTableRowMap[idt] = 1;
		}
		else
		{
			++((*itt).second);
		}

		++NumUpdateSubMessages;
	}

	void				clear()
	{
		NumMessages = 0;
		NumSubMessages = 0;
		NumUpdateSubMessages = 0;
		TotalMessagesSize = 0;
		TotalHeaderSize = 0;
		memset(SubMessageTypes, 0, sizeof(SubMessageTypes));
		UpdateMap.clear();
		UpdateRowMap.clear();
		UpdateTableRowMap.clear();
	}

	void				display(NLMISC::CLog* log = NLMISC::InfoLog)
	{
		log->displayNL("%d messages, %d submessages, %"NL_I64"d message bytes, %"NL_I64"d header bytes", NumMessages, NumSubMessages, TotalMessagesSize, TotalHeaderSize);
		log->displayNL("%.1f bytes avg per submessage, %.1f bytes avg per submessage header", (double)TotalMessagesSize/(double)NumSubMessages, (double)TotalHeaderSize/(double)NumSubMessages);
		log->displayNL("%d updates, %d values updated, %d column updated, %d row updated", NumUpdateSubMessages, UpdateRowMap.size(), UpdateMap.size(), UpdateTableRowMap.size());
	}
};


#endif // NL_DB_MANAGER_MESSAGES_H

/* End of db_manager_messages.h */
