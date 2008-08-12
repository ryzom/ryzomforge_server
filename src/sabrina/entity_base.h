#include "nel/misc/sheet_id.h"
#include "nel/misc/entity_id.h"
#include "game_share/base_types.h"

#ifndef SAB_ENTITY_BASE_H
#define SAB_ENTITY_BASE_H

class ISabrinaActor;

class CEntityBase
{
public:
	CEntityBase(): _Target(NULL), _EntityRowId(0) {}

	virtual	ISabrinaActor*		getSabrinaActor()	=0;

	NLMISC::CSheetId			getSheetId()		const { return NLMISC::CSheetId(); }
	const NLMISC::CEntityId		getId()				const { return NLMISC::CEntityId(); }

	TDataSetRow					getEntityRowId()	const { return TDataSetRow::createFromRawIndex(_EntityRowId); }
	void						setEntityRowId(uint32 i)  { _EntityRowId=i; }

	CEntityBase*				getTarget()			const { return _Target; }
	void						setTarget(CEntityBase* t) { _Target=t; }

private:
	CEntityBase*	_Target;
	uint32			_EntityRowId;
};

#endif