/** \file gus_mfc_popups.h
 *
 * $id$
 *
 */

#ifndef GUS_CHAT_H
#define GUS_CHAT_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "nel/misc/displayer.h"
#include "gus_client_manager.h"


//-----------------------------------------------------------------------------
// GUS namespace
//-----------------------------------------------------------------------------

namespace GUS
{
	//-----------------------------------------------------------------------------
	// static routines
	//-----------------------------------------------------------------------------

	bool selectFromList(const CVectorSString& options,CSString& selectResult);
	bool selectFromListWithText(const CVectorSString& options,CSString& selectResult,CSString& textResult);

}


//-----------------------------------------------------------------------------
#endif
