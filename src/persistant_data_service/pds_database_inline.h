/** \file pds_database_inline.h
 * 
 *
 * $Id: pds_database_inline.h,v 1.3 2004/06/15 13:31:51 legros Exp $
 */

#ifndef RY_PDS_DATABASE_H
#error pds_database_inline.h MUST be included by pds_database.h
#endif

#ifndef RY_PDS_DATABASE_INLINE_H
#define RY_PDS_DATABASE_INLINE_H


//
// Inlines
//





//
// Get methods
//

/*
 * Get Type
 */
inline const CType*	CDatabase::getType(TTypeId typeId) const
{
	if (typeId >= _Types.size())
	{
		//warning("getType(): type '"+NLMISC::toString(typeId)+"' is not initialised");
		return NULL;
	}

	return _Types[typeId];
}

/*
 * Get Table
 */
inline const CTable*	CDatabase::getTable(TTypeId tableId) const
{
	if (tableId >= _Tables.size())
	{
		//warning("getTable(): table '"+NLMISC::toString(tableId)+"' is not initialised");
		return NULL;
	}

	return _Tables[tableId];
}



/*
 * Private Get Table (non const)
 */
inline CTable*	CDatabase::getNonConstTable(RY_PDS::TTableIndex tableId)
{
	if (tableId >= _Tables.size())
		return NULL;

	return _Tables[tableId];
}

#endif //RY_PDS_DATABASE_INLINE_H

