/** \file gus_utils.h
 *
 * $id$
 *
 */

#ifndef GUS_UTILS_H
#define GUS_UTILS_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "nel/misc/types_nl.h"
#include "nel/misc/sstring.h"
#include "nel/misc/smart_ptr.h"
#include "nel/net/unified_network.h"

#include "game_share/utils.h"


//-----------------------------------------------------------------------------
// GUS namespace
//-----------------------------------------------------------------------------

namespace GUS
{
	//-----------------------------------------------------------------------------
	// handy utilities
	//-----------------------------------------------------------------------------

	// Clean a path performing the following operations:
	//	- convert '\\' characters to '/'
	//	- replace '//' strings in the middle of the path with '/'
	//	- remove '.' directory entries
	//	- colapse '..' directory entries (removing parent entries)
	//	- append a final '/' (optionally)
	//
	// examples:
	//	- a:/bcd/efg/		=>	a:/bcd/efg/ (no change)
	//	- a:\bcd\efg		=>	a:/bcd/efg/
	//	- \bcd\\efg			=>	/bcd/efg/
	//	- \\bcd\efg			=>	//bcd/efg/
	//	- \bcd\.\efg		=>	/bcd/efg/
	//	- \bcd\..\efg		=>	/efg/
	//	- bcd\..\efg		=>	efg/
	//	- bcd\..\..\efg		=>	../efg/
	//	- \bcd\..\..\efg	=>	/efg/		(NOTE: the redundant '..' entry is lost due to leading '\')
	//
	NLMISC::CSString cleanPath(const NLMISC::CSString& path,bool addTrailingSlash);


	// execute a command on a remote service
	void executeRemoteCommand(NLNET::TServiceId sid,const NLMISC::CSString& cmdLine);
	void executeRemoteCommand(const char* serviceName,const NLMISC::CSString& cmdLine);

}

//-----------------------------------------------------------------------------
#endif
