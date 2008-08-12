/** \file admin_properties.h
* <File description>
*
* $Id: admin_properties.h,v 1.7 2005/06/23 18:14:21 boucher Exp $
*/

#ifndef RY_ADMIN_PROPERTIES_H
#define RY_ADMIN_PROPERTIES_H

#include "mission_manager/ai_alias_translator.h"
#include "mission_manager/mission_types.h"

class CCharacter;

/**
 * properties for CSR characters. Use the init method to init this property for CS characters
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CAdminProperties
{
	NL_INSTANCE_COUNTER_DECL(CAdminProperties);
public:

	CAdminProperties()
		:_Data(NULL){}
	~CAdminProperties()
	{
		if (_Data)
		{
			delete _Data;
			_Data = NULL;
		}
	}

	void init()
	{
		NL_ALLOC_CONTEXT(AP_INIT);
		_Data = new CData;
	}

	void setMissionMonitoredUser(const TDataSetRow & row)
	{
		if ( !_Data ) return;
		_Data->MissionUser = row;
	}

	TDataSetRow getMissionMonitoredUser() const
	{
		if ( !_Data ) return TDataSetRow::createFromRawIndex( INVALID_DATASET_ROW );
		return _Data->MissionUser;
	}

	CMission * getMission( uint indexInJournal ) const;

	static void updateCSRJournal( CCharacter * user, CMission * mission,uint8 idx );

private:
	struct CData
	{
		TDataSetRow MissionUser;
	};

	CData * _Data;
};


#endif // RY_ADMIN_PROPERTIES_H

/* End of admin_properties.h */
