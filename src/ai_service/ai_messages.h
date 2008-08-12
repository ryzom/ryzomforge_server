/** \file ai_messages.h
 *
 * $Id: ai_messages.h,v 1.5 2007/05/25 09:47:42 verquerre Exp $
 */



#ifndef RYAI_MESSAGES_H
#define RYAI_MESSAGES_H

#include "nel/misc/types_nl.h"
#include "nel/misc/time_nl.h"
#include "nel/misc/sheet_id.h"
#include "nel/misc/entity_id.h"

#include "nel/net/transport_class.h"


//----------------------------------------------------------------
// Message sent by AIS to AIDS in reaction to AIDS's service up 

class CMsgAIServiceUp : public NLNET::CTransportClass
{
public:
	CMsgAIServiceUp(float processorAllocation,float ramAllocation) 
	{
		_processorAllocation=processorAllocation;
		_ramAllocation=ramAllocation;
	}

	virtual void description ()
	{
		className ("CMsgAIServiceUp");
		property ("_processorAllocation", PropFloat, 0.0f, _processorAllocation);
		property ("_ramAllocation", PropFloat, 0.0f, _ramAllocation);
	}

	virtual void callback (const std::string &name, NLNET::TServiceId  id);

protected:
	float _processorAllocation;
	float _ramAllocation;
};

//----------------------------------------------------------------
// AIDS -> AIS: Load & start Managers

class CMsgAIOpenMgrs : public NLNET::CTransportClass
{
public:
	CMsgAIOpenMgrs(uint16 idx,const std::string &name) 
	{
		_idx.push_back(idx);
		_name.push_back(name);
	}

	void push_back(uint16 idx,constr std::string &name)
	{
		_idx.push_back(idx);
		_name.push_back(name);
	}

	virtual void description ()
	{
		className ("CMsgAIOpenMgrs");
		propertyCont ("idx", PropUInt16, _idx);
		propertyCont ("name", PropString, _name);
	}

	virtual void callback (const std::string &name, NLNET::TServiceId  id);

protected:
	std::vector <uint16> _idx;
	std::vector <std::string> _name;
};


//----------------------------------------------------------------
// AIDS -> AIS: Reload Managers

class CMsgAIReloadMgrs : public NLNET::CTransportClass
{
public:
	CMsgAIReloadMgrs(uint16 idx) 
	{
		_idx.push_back(idx);
	}

	void push_back(uint16 idx)
	{
		_idx.push_back(idx);
	}

	virtual void description ()
	{
		className ("CMsgAIReloadMgrs");
		propertyCont ("idx", PropUInt16, _idx);
	}

	virtual void callback (const std::string &name, NLNET::TServiceId id);

protected:
	std::vector <uint16> _idx;
};


//----------------------------------------------------------------
// AIDS -> AIS: Save, stop and unload Managers

class CMsgAICloseMgrs : public NLNET::CTransportClass
{
public:
	CMsgAICloseMgrs(uint16 idx) 
	{
		_idx.push_back(idx);
	}

	void push_back(uint16 idx)
	{
		_idx.push_back(idx);
	}

	virtual void description ()
	{
		className ("CMsgAICloseMgrs");
		propertyCont ("idx", PropUInt16, _idx);
	}

	virtual void callback (const std::string &name, NLNET::TServiceId id);

protected:
	std::vector <uint16> _idx;
};


//----------------------------------------------------------------
// AIDS -> AIS: Save managers' backups

class CMsgAIBackupMgrs : public NLNET::CTransportClass
{
public:
	CMsgAIBackupMgrs(uint16 idx) 
	{
		_idx.push_back(idx);
	}

	void push_back(uint16 idx)
	{
		_idx.push_back(idx);
	}

	virtual void description ()
	{
		className ("CMsgAIBackupMgrs");
		propertyCont ("idx", PropUInt16, _idx);
	}

	virtual void callback (const std::string &name, NLNET::TServiceId id);

protected:
	std::vector <uint16> _idx;
};


#endif

