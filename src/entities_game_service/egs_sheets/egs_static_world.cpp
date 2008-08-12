/** \file egs_static_rolemaster_phrase.cpp
 * <File description>
 *
 * $Id: egs_static_world.cpp,v 1.1 2004/03/29 15:26:22 brigand Exp $
 */



#include "stdpch.h"
#include "egs_sheets/egs_static_world.h"

#include "game_share/continent.h"

#include "nel/georges/u_form_elm.h"
#include "nel/georges/load_form.h"



using namespace NLMISC;
using namespace NLGEORGES;
using namespace std;


void CStaticWorld::readGeorges (const NLMISC::CSmartPtr<NLGEORGES::UForm> &form, const NLMISC::CSheetId &sheetId)
{
	UFormElm &root = form->getRootNode();
	const UFormElm *pElt;
	nlverify (root.getNodeByName (&pElt, "continents list"));
	uint size;
	nlverify (pElt->getArraySize (size));
	string value;
	
	Continents.reserve(size);
	for (uint32 i = 0; i <size; ++i)
	{
		const UFormElm *pEltOfList;
		// Get the continent
		if (pElt->getArrayNode (&pEltOfList, i) && pEltOfList)
		{
			nlverify( pEltOfList->getValueByName( value, "continent_name" ) );
			CSheetId sheet( value + ".continent" );
			if ( sheet == CSheetId::Unknown )
				nlerror("CStaticWorld sheet '%s' is invalid. ryzom.world is broken",value.c_str() );

			uint contId = ( CONTINENT::TContinent ) CONTINENT::toContinent( value );
			if ( contId == CONTINENT::UNKNOWN )
			{
				nlverify( pEltOfList->getValueByName( value, "selection_name" ) );
				contId = ( CONTINENT::TContinent ) CONTINENT::toContinent( value );
			}
			if ( contId != CONTINENT::UNKNOWN )
			{
				if ( contId >= Continents.size() )
					Continents.resize( contId + 1 );
				Continents[contId] = sheet;
			}
			else
				nlwarning("CStaticWorld continent '%s' is invalid. ryzom.world is broken",value.c_str() );
		}
	}		
}

///////////////////////////////////////////////////////////////////////////////////////////

void CStaticContinent::readGeorges (const NLMISC::CSmartPtr<NLGEORGES::UForm> &form, const NLMISC::CSheetId &sheetId)
{
	UFormElm &root = form->getRootNode();
	const UFormElm *elm;
	string value;
	if(root.getNodeByName(&elm, "ZCs") && elm)
	{
		uint nbZC;
		nlverify(elm->getArraySize(nbZC));
		Outposts.reserve( nbZC );
		for(uint i = 0; i < nbZC; ++i)
		{
			// Village pointer
			const UFormElm *zc;
			if(elm->getArrayNode(&zc, i) && zc)
				nlverify(zc->getValueByName(value, "outpost_number"));
			uint index = (uint) atoi(value.c_str());
			Outposts.push_back( index );
		}
	}
}



