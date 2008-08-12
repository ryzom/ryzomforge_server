/** \file gus_mfc_popups.cpp
 *
 * $id$
 *
 */

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "gus_mfc_select_with_text.h"


//-----------------------------------------------------------------------------
// GUS namespace
//-----------------------------------------------------------------------------

namespace GUS
{
	//-----------------------------------------------------------------------------
	// static routines
	//-----------------------------------------------------------------------------

	bool selectFromList(const CVectorSString& options,CSString& selectResult)
	{ 
		CGusMfcSelect dlg(options);
		if (dlg.DoModal ()== IDOK)
		{
			selectResult= dlg.ComboValue;
			return true;
		}
		return false;
	}

	bool selectFromListWithText(const CVectorSString& options,CSString& selectResult,CSString& textResult)
	{ 
		CGusMfcSelectWithText dlg(options);
		if (dlg.DoModal ()== IDOK)
		{
			selectResult= dlg.ComboValue;
			textResult= dlg.TextValue;
			return true;
		}
		return false;
	}
}