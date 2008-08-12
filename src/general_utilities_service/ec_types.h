/** \file ec_types.h
 *
 * $id$
 *
 */

#ifndef EC_TYPES_H
#define EC_TYPES_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "nel/misc/types_nl.h"
#include "nel/misc/smart_ptr.h"


//-----------------------------------------------------------------------------
// NLMISC namespace
//-----------------------------------------------------------------------------

namespace NLMISC
{
	//-----------------------------------------------------------------------------
	// advanced class declarations
	//-----------------------------------------------------------------------------

	class CSString;
}


//-----------------------------------------------------------------------------
// GUS namespace
//-----------------------------------------------------------------------------

namespace GUS
{
	//-----------------------------------------------------------------------------
	// advanced class declarations
	//-----------------------------------------------------------------------------

	class CChatChannel;
	typedef NLMISC::CSmartPtr<CChatChannel> TChatChannelPtr;
}


//-----------------------------------------------------------------------------
// EC namespace
//-----------------------------------------------------------------------------

namespace EC
{
	//-----------------------------------------------------------------------------
	// advanced class declarations
	//-----------------------------------------------------------------------------

	class CEventChatModule;
	typedef NLMISC::CSmartPtr<CEventChatModule>	TEventChatModulePtr;

	class IChannel;
	class CCtrlChannel;
	class CFactionChannel;
	class CPartyChannel;
	typedef NLMISC::CSmartPtr<CCtrlChannel>		TCtrlChannelPtr;
	typedef NLMISC::CSmartPtr<CFactionChannel>	TFactionChannelPtr;
	typedef NLMISC::CSmartPtr<CPartyChannel>		TPartyChannelPtr;
}


//-----------------------------------------------------------------------------
#endif
