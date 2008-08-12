/** \file s_phrase_factory.cpp
 * <File description>
 *
 * $Id: s_phrase_factory.cpp,v 1.3 2004/12/09 14:17:28 besson Exp $
 */



#include "stdpch.h"
#include "s_phrase_factory.h"

using namespace std;
using namespace NLMISC;

vector< std::pair< BRICK_TYPE::EBrickType , ISPhraseFactory* > > * ISPhraseFactory::Factories;

CSPhrasePtr ISPhraseFactory::buildPhrase( const TDataSetRow & actorRowId,const std::vector< NLMISC::CSheetId>& brickIds, bool execution )
{
	// the check to see if there is at least a brick is made before
	nlassert( !brickIds.empty() );
	nlassert( Factories );
	
	// transform sheet ids into forms
	std::vector< const CStaticBrick* > bricks( brickIds.size() );
	uint16 nbNull = 0;
	for ( uint i = 0; i < bricks.size(); ++i )
	{
		// skip unknown sheetIds
		if (  brickIds[i] == NLMISC::CSheetId::Unknown )
		{
			++nbNull;
			continue;
		}
		
		bricks[i-nbNull] = CSheets::getSBrickForm( brickIds[i] );
		
		if ( bricks[i-nbNull] == NULL )
		{
			nlwarning( "<ISPhraseFactory buildPhrase> invalid SBrick sheet %u, named %s",brickIds[i].asInt(),brickIds[i].toString().c_str() );
			return NULL;
		}
	}
	
	if (nbNull)
		bricks.resize( bricks.size() - nbNull);
	
#ifdef NL_DEBUG
	if (UseDebugBrick)
	{
		NLMISC::CEntityId id = TheDataset.getEntityId(actorRowId);
		if ( id.getType() == RYZOMID::player )
			bricks.push_back(&DebugBrick);
	}		
#endif
	
	//get the root brick family and the associated factory
	for ( uint i = 0; i < Factories->size(); i++ )
	{
		if ( (*Factories)[i].first == BRICK_FAMILIES::brickType(bricks[0]->Family) )
		{
			CSPhrasePtr phrase = (*Factories)[i].second->buildPhrase( actorRowId, bricks, execution);
			if ( phrase )
			{
				phrase->setBrickSheets(brickIds);
				return phrase;
			}
			return NULL;
		}
	}
	nlwarning( "<ISPhraseFactory buildPhrase> the brick type %s has no corresponding phrase class", BRICK_TYPE::toString(BRICK_FAMILIES::brickType( bricks[0]->Family )).c_str() );
	return NULL;
}

