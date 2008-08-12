/** \file egs_static_rolemaster_phrase.cpp
 * <File description>
 *
 * $Id: egs_static_rolemaster_phrase.cpp,v 1.5 2004/11/30 13:32:07 berenguier Exp $
 */



#include "stdpch.h"
#include "egs_static_rolemaster_phrase.h"
#include "egs_static_brick.h"
#include "egs_sheets.h"
#include "game_share/fame.h"

//Nel georges
#include "nel/georges/u_form_elm.h"
#include "nel/georges/load_form.h"

using namespace NLMISC;
using namespace NLGEORGES;
using namespace std;


// ***************************************************************************
void CStaticRolemasterPhrase::readGeorges (const NLMISC::CSmartPtr<NLGEORGES::UForm> &form, const NLMISC::CSheetId &sheetId)
{
	form->getRootNode().getValueByName( IsRolemasterPhrase, "usable_by_player" );
	form->getRootNode().getValueByName( IsValidPhrase, "castable" );

	string sbrickSheetName;
	uint i = 0;
	while ( i < 100 )
	{
		bool res = form->getRootNode().getValueByName( sbrickSheetName, toString( "brick %u", i ).c_str() );
		if ( (! res) || sbrickSheetName.empty() )
		{
			++i;
			continue;
		}
		Bricks.push_back( CSheetId( sbrickSheetName ) );
		++i;
	}

	computeMinFameValue();
}

// ***************************************************************************
void CStaticRolemasterPhrase::computeMinFameValue()
{
	MinFameValue = (sint32)0x80000000;
	for ( uint i = 0; i  < Bricks.size(); i++ )
	{
		const CStaticBrick * brick = CSheets::getSBrickForm( Bricks[i] );
		if( brick && brick->MinFameValue > MinFameValue )
			MinFameValue = brick->MinFameValue;
	}
}

// ***************************************************************************
void CStaticRolemasterPhrase::reloadSheet(const CStaticRolemasterPhrase &o)
{
	// nothing special
	*this= o;
}

