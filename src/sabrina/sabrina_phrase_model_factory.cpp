/** \file sabrina_phrase_model_factory.cpp
 *
 * $Id: sabrina_phrase_model_factory.cpp,v 1.3 2004/03/01 19:22:19 lecroart Exp $
 */



// game_share
#include "game_share/egs_sheets/egs_sheets.h"
// sabrina
#include "sabrina_phrase_model_factory.h"
#include "sabrina_phrase_model_craft.h"
#include "sabrina_phrase_model_fight.h"
#include "sabrina_phrase_model_magic.h"
 

//-----------------------------------------------
//			newPhraseModel()
//-----------------------------------------------
ISabrinaPhraseModelPtr CSabrinaPhraseModelFactory::newPhraseModel(const std::vector< const CStaticBrick* >& bricks)
{
	// quick idiot test before we begin...
	if (bricks.empty())
		return NULL;

	ISabrinaPhraseModel* newModel=NULL;

	// instantiate the new model
	switch (bricks[0]->Type)
	{
	case BRICK_TYPE::MAGIC:				newModel= new CSabrinaPhraseModelMagic; break;
	case BRICK_TYPE::COMBAT:			newModel= new CSabrinaPhraseModelFight;	break;
	case BRICK_TYPE::FABER:				newModel= new CSabrinaPhraseModelCraft;	break;
	case BRICK_TYPE::HARVEST:			
	case BRICK_TYPE::TRACKING:			
	case BRICK_TYPE::SHOPKEEPER:		
	case BRICK_TYPE::TRAINING:			
	case BRICK_TYPE::MISCELLANEOUS:		
	case BRICK_TYPE::COMMERCE:			

	default:
		nlwarning("CSabrinaPhraseModelFactory::newPhraseModel(): Failed due to unhandled root brick type for root brick: %s",
			bricks[0]->SheetId.toString().c_str());
		return NULL;
	}

	// add bricks to the instantiated model
	for (uint32 i=0;i<bricks.size();++i)
		newModel->addBrick(bricks[i]);

	// if the new model's no good then return NULL and let smart ptr delete the newModel object
	if (!newModel->isValid())
		return NULL;
	return newModel;
}

//-----------------------------------------------
//			newPhraseModel()
//-----------------------------------------------
ISabrinaPhraseModelPtr CSabrinaPhraseModelFactory::newPhraseModel(const std::vector< NLMISC::CSheetId >& brickIds)
{
	// transform sheet ids into forms
	std::vector< const CStaticBrick* > bricks;
	bricks.reserve(brickIds.size());
	for ( uint i = 0; i < brickIds.size(); ++i )
	{
		// skip unknown sheetIds
		if (  brickIds[i] == NLMISC::CSheetId::Unknown )
		{
			continue;
		}
		
		const CStaticBrick* staticBrick=NULL;
		if( NLMISC::CSheetId::fileExtensionFromType( brickIds[i].getType() ) == std::string("sbrick") )
		{
			staticBrick= CSheets::getSBrickForm( brickIds[i] );
		}
		else if( NLMISC::CSheetId::fileExtensionFromType( brickIds[i].getType() ) == std::string("sitem") )
		{
			staticBrick= (const CStaticBrick*) CSheets::getForm( brickIds[i] );
		}

		if ( staticBrick == NULL )
		{
			nlwarning( "<ISabrinaPhraseModelFactory buildPhrase> invalid SBrick sheet %u, named %s",brickIds[i].asInt(),brickIds[i].toString().c_str() );
			return NULL;
		}
		bricks.push_back(staticBrick);
	}
	// call the proper factory method
	return newPhraseModel(bricks);
}


//-----------------------------------------------
//			newPhraseModel()
//-----------------------------------------------
ISabrinaPhraseModelPtr CSabrinaPhraseModelFactory::newPhraseModel(const std::vector< std::string >& brickNames)
{
	// allocate a vector of sheet ids
	std::vector< NLMISC::CSheetId > brickIds;
	brickIds.reserve(brickNames.size());

	for (uint32 i=0;i<brickNames.size();++i)
	{
		// lookup the sheet id
		NLMISC::CSheetId sheetId= NLMISC::CSheetId(brickNames[i]);
		// make sure the sheet id was found
		if (sheetId==NLMISC::CSheetId::Unknown)
		{
			nlwarning("newPhraseModel(): Aborting due to failure to match sheet id for brick: %s",brickNames[i].c_str());
			return NULL;
		}
		// add the sheet id to our new vector
		brickIds.push_back(sheetId);
	}
	// call the proper factory method
	return newPhraseModel(brickIds);
}

