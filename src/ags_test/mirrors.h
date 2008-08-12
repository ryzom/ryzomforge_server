/** \file mirrors.h
 *
 * $Id: mirrors.h,v 1.12 2004/06/14 15:13:07 cado Exp $
 */



#ifndef RY_CMS_MIRRORS_H
#define RY_CMS_MIRRORS_H

// include files
#include "nel/misc/types_nl.h"
#include "nel/misc/entity_id.h"
#include "nel/misc/sheet_id.h"
#include "game_share/mode_and_behaviour.h"
#include "game_share/mirror.h"
#include "game_share/mirror_prop_value.h"

class CMirrors
{
public:
	// singleton initialisation and release
	static void				init( void (*cbUpdate)(), void (*cbSync)()=NULL, void (*cbRelease)() = NULL );
	static void				initMirror();
	static void				processMirrorUpdates();
	static void				release();

	static bool				exists( const NLMISC::CEntityId& id ) { return (DataSet->getDataSetRow( id ).isValid()); }

	static sint32			x( const NLMISC::CEntityId& id ) { CMirrorPropValueRO<sint32> value( *DataSet, id, "X" ); return (sint32)value(); }
	static sint32			y( const NLMISC::CEntityId& id ) { CMirrorPropValueRO<sint32> value( *DataSet, id, "Y" ); return (sint32)value(); }
	static sint32			z( const NLMISC::CEntityId& id ) { CMirrorPropValueRO<sint32> value( *DataSet, id, "Z" ); return (sint32)value(); }
	static sint32			mode( const NLMISC::CEntityId& id ) { CMirrorPropValueRO<uint64> value( *DataSet, id, "Mode" ); return (sint32)(MBEHAV::TMode(value()).Mode); }
	static sint32			behaviour( const NLMISC::CEntityId& id ) { CMirrorPropValueRO<uint32> value( *DataSet, id, "Behaviour" ); return (uint32)value(); }

	static void				initSheet( const NLMISC::CEntityId& id, const NLMISC::CSheetId& sheetId ) { CMirrorPropValue<uint32> value( *DataSet, id, "Sheet" ); value = sheetId.asInt(); }
	static NLMISC::CSheetId	sheet( const NLMISC::CEntityId& id ) { CMirrorPropValueRO<uint32> value( *DataSet, id, "Sheet" ); return NLMISC::CSheetId(value()); }

private:
	// callbacks used at service connection and disconnection
	static void				cbServiceUp( const std::string& serviceName, uint16 serviceId, void * );
	static void				cbServiceDown( const std::string& serviceName, uint16 serviceId, void * );

public:
	static CMirror											Mirror;
	static CMirroredDataSet									*DataSet;
};


#define TheDataset (*CMirrors::DataSet)


#endif // RY_CMS_MIRRORS_H

