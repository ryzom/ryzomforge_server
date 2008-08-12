/** \file fx_entity.h
  * 
  * $Id: fx_entity.h,v 1.2 2005/08/10 13:55:56 vuarand Exp $
  */

#ifndef RYAI_FX_ENTITY_H
#define RYAI_FX_ENTITY_H

#include <string>
#include "nel/misc/entity_id.h"
#include "ai_pos.h"

class CGroupNpc;

class CFxEntity
: public NLMISC::CRefCount
{
public:
	CFxEntity(CAIPos const& pos, NLMISC::CSheetId const& sheet);
	~CFxEntity();
	NLMISC::CEntityId const& id() const;
	bool spawn();
	void despawn();
	bool update() { }
	void set(std::string const& prop, std::string const& value, bool reportChange=false) { }
	std::string get(std::string const& prop);
	std::string getIndexString() const { return _EntityId.toString(); }
	virtual std::string getOneLineInfoString() const;
	virtual std::vector<std::string> getMultiLineInfoString() const;
	
private:
	NLMISC::CEntityId	_EntityId;
	TDataSetRow			_DataSetRow;
	CAIPos				_Pos;
	NLMISC::CSheetId	_Sheet;
};
typedef NLMISC::CSmartPtr<CFxEntity> CFxEntityPtr;
typedef NLMISC::CSmartPtr<CFxEntity const> CFxEntityCPtr;

#endif
