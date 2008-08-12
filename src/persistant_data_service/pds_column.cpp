/** \file pds_column.cpp
 * <File description>
 *
 * $Id: pds_column.cpp,v 1.5 2004/09/27 17:45:34 legros Exp $
 */

#include "../pd_lib/pds_common.h"

#include "pds_column.h"
#include "pds_attribute.h"
#include "pds_type.h"
#include "pds_database.h"
#include "pds_table.h"

#include <nel/misc/debug.h>

using namespace std;
using namespace NLMISC;

// Destructor
CColumn::~CColumn()
{
	//PDS_DEBUG("delete()");
}

/*
 * Initialize column
 */
bool	CColumn::init(CAttribute* parent, CDatabase *root)
{
	_Parent = parent;
	_Root = root;
	_Init = true;

	// set parent logger
	setParentLogger(_Parent->getParent());

	return true;
}

