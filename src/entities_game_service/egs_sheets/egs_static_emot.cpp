/** \file egs_static_emot.cpp
 * <File description>
 *
 * $Id: egs_static_emot.cpp,v 1.1 2005/07/06 12:13:33 vuarand Exp $
 */



#include "stdpch.h"
#include "egs_sheets/egs_static_emot.h"
#include "nel/georges/u_form_elm.h"
#include "nel/georges/load_form.h"



using namespace NLMISC;
using namespace NLGEORGES;
using namespace std;



void CStaticEmot::readGeorges(const NLMISC::CSmartPtr<NLGEORGES::UForm> &form, const NLMISC::CSheetId &sheetId)
{
	UFormElm &root = form->getRootNode();
	const UFormElm *pElt;
	nlverify (root.getNodeByName (&pElt, "emot_list"));
	uint size;
	nlverify (pElt->getArraySize (size));
	string value;
	_Anims.reserve(size);
	for (uint32 i = 0; i < size; ++i)
	{
	//	const UFormElm *pEltOfList;
	//	// Get the continent
	//	if (pElt->getArrayNode (&pEltOfList, i) && pEltOfList)
	//	{
	//	}
		_Anims.push_back( string() );
		nlverify( pElt->getArrayValue( _Anims.back(), i ) );
	}
	buildAnimIdMap();
}

void CStaticEmot::buildAnimIdMap()
{
	size_t size = _Anims.size();
	for (size_t i=0; i<size; ++i)
		_AnimIdMap.insert(make_pair(_Anims[i], i));
}

