/** \file outpost_version_adapter.cpp
 * <File description>
 *
 * $Id: outpost_version_adapter.cpp,v 1.1 2005/09/27 09:58:27 besson Exp $
 */

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "stdpch.h"
#include "outpost_version_adapter.h"

//-----------------------------------------------------------------------------
// namespaces
//-----------------------------------------------------------------------------

using namespace std;
using namespace NLMISC;


//-----------------------------------------------------------------------------
// static members COutpostVersionAdapter
//-----------------------------------------------------------------------------

NL_INSTANCE_COUNTER_IMPL(COutpostVersionAdapter);
COutpostVersionAdapter * COutpostVersionAdapter::_Instance = NULL;


//-----------------------------------------------------------------------------
// methods COutpostVersionAdapter
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint32 COutpostVersionAdapter::currentVersionNumber() const
{
	////////////////////////////////////
	// VERSION History
	// 0 : (18/05/2005) initial version
	////////////////////////////////////
	return 0;
}

//-----------------------------------------------------------------------------
void COutpostVersionAdapter::adaptOutpostFromVersion(COutpost & outpost, uint32 version) const
{
	// Do NOT break between case labels
	//switch (version)
	//{
	//case 0: adaptToVersion1(outpost);
	//}
}

//-----------------------------------------------------------------------------
//void COutpostVersionAdapter::adaptToVersion1(COutpost & outpost) const
//{
//}
