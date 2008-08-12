/** \file egs_static_xp_factor_table.cpp
 * 
 *
 * $Id: egs_static_xp_factor_table.cpp,v 1.2 2004/11/30 13:58:47 vizerie Exp $
 */


#include "stdpch.h"
#include "egs_static_xp_factor_table.h"
#include "egs_sheets.h"
//Nel georges
#include "nel/georges/u_form_elm.h"
#include "nel/georges/load_form.h"

using namespace std;
using namespace NLMISC;
using namespace NLGEORGES;

//--------------------------------------------------------------
// serial
//--------------------------------------------------------------
void CStaticXpFactorTable::serial(class NLMISC::IStream &f)
{
	f.serialCont(_XpFactorTable);
} // serial //


//--------------------------------------------------------------
// readGeorges
//--------------------------------------------------------------
void CStaticXpFactorTable::readGeorges (const CSmartPtr<UForm> &form, const CSheetId &sheetId)
{
	if (!form)
	{
		nlwarning("Error reading sheet %s, form == NULL", sheetId.toString().c_str());
		return;
	}

	UFormElm& root = form->getRootNode();		
	
	const UFormElm *array = NULL;
	if (root.getNodeByName (&array, "XpFactor") && array)
    {
		// Get array size
        uint size;
		array->getArraySize (size);
		
		_XpFactorTable.resize( size );
		
        // Get an array value
        for (uint i=0; i<size; ++i)
        {
			array->getArrayValue(_XpFactorTable[i], i);
        }
	}
} // readGeorges //

