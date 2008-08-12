/** \file named_entity.h
  * 
  * $Id: named_entity.h,v 1.3 2005/07/26 14:37:53 vuarand Exp $
  */

#ifndef RYAI_NAMED_ENTITY_H
#define RYAI_NAMED_ENTITY_H

#include <string>
#include "nel/misc/entity_id.h"

class CGroupNpc;

class CNamedEntity
{
public:
	CNamedEntity(std::string const& name);
	std::string const& name() const;
	NLMISC::CEntityId const& id() const;
	std::string const& getState();
	std::string const& getParam1();
	std::string const& getParam2();
	std::string get(std::string const& prop);
	void set(std::string const& prop, std::string const& value, bool reportChange=false);
	void addListenerGroup(std::string const& prop, CGroupNpc* persGrp);
	void delListenerGroup(std::string const& prop, CGroupNpc* persGrp);
private:
	void namedEntityCb(std::string const& prop);
	std::string _name;
	NLMISC::CEntityId _id;
	std::string _state;
	std::string _param1;
	std::string _param2;
	typedef std::multimap<std::string, CGroupNpc*> TListenerGroupList;
	TListenerGroupList _listenerGroups;
};

#endif // RYAI_NAMED_ENTITY_H
