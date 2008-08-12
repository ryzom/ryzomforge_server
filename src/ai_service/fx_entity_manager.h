/**	@file fx_entity_manager.h
	
	$Id: fx_entity_manager.h,v 1.2 2005/08/10 13:55:56 vuarand Exp $
*/

#ifndef RYAI_FX_ENTITY_MANAGER_H
#define RYAI_FX_ENTITY_MANAGER_H

#include <string>
#include <vector>
#include <set>
#include <map>
#include "fx_entity.h"
#include "fx_entity_manager.h"

/**	Manager for fx entities
	
	This class is a singleton.
	
	@author vuarand
*/
class CFxEntityManager
{
public:
	/// Returns a pointer to the manager.
	static CFxEntityManager* getInstance();
	/// Destroys the manager.
	static void destroyInstance();
	
	void init(TDataSetIndex baseRowIndex, TDataSetIndex size);
	void tickUpdate();
	
	/// Creates a fx entity or return an existing one with that name.
	CFxEntityPtr create(CAIPos const& pos, NLMISC::CSheetId const& sheet);
	/// Removes a fx entity from the manager.
	void destroy(CFxEntityPtr const& entity);
	/// Tells if an entity with the specified id exists in the manager.
	bool exists(NLMISC::CEntityId const& id);
	/// Select a set of entities depending of a request string.
	void select(std::string const& request, std::vector<NLMISC::CEntityId>& entities);
	/// Returns a fx entity with that id or 0 (NULL) if it doesn't exist.
	CFxEntityPtr get(NLMISC::CEntityId const& id);
	
	void registerEntity(CFxEntityPtr const& entity);
	void unregisterEntity(CFxEntityPtr const& entity);

	typedef std::set<CFxEntityPtr> TFxEntityContainer;
	typedef std::map<NLMISC::CEntityId, CFxEntityPtr> TEntityIdContainer;
	TFxEntityContainer const& getEntities() { return _Entities; }
	void dumpIndex()
	{
		FOREACH(itEntity, TEntityIdContainer, _IdIndex)
		{
			nldebug("Entity %s %s", itEntity->first.toString().c_str(), itEntity->second->id().toString().c_str());
		}
	}
	
protected:
	static CFxEntityManager* _Instance;
	
private:
	TFxEntityContainer	_Entities;
	TEntityIdContainer	_IdIndex;
};

#endif
