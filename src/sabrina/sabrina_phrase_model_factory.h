/** \file sabrina_phrase_model_factory.h
 *
 * $Id: sabrina_phrase_model_factory.h,v 1.3 2004/03/01 19:22:19 lecroart Exp $
 */




#ifndef RY_SABRINA_PHRASE_MODEL_FACTORY_H
#define RY_SABRINA_PHRASE_MODEL_FACTORY_H

// stl
#include <vector>
// nel
#include "nel/misc/types_nl.h"
#include "nel/misc/sheet_id.h"
// game share
#include "game_share/egs_sheets/egs_static_brick.h"
// sabrina
#include "sabrina_pointers.h"
 

/**
 * Factory class for sabrina phrases
 * \author Sadge
 * \author Nevrax France
 * \date 2003
 */
class CSabrinaPhraseModelFactory
{
public:
	/**
	 * Singleton factory method
	 * \param bricks : bricks composing the phrase
	 * \return smart pointer to new phrase object or NULL on failure
	 */
	static ISabrinaPhraseModelPtr newPhraseModel(const std::vector< const CStaticBrick* >& bricks);

	/**
	 * Singleton factory method
	 * \param bricks : bricks composing the phrase
	 * \return smart pointer to new phrase object or NULL on failure
	 */
	static ISabrinaPhraseModelPtr newPhraseModel(const std::vector< NLMISC::CSheetId >& bricks);

	/**
	 * Singleton factory method
	 * \param bricks : bricks composing the phrase
	 * \return smart pointer to new phrase object or NULL on failure
	 */
	static ISabrinaPhraseModelPtr newPhraseModel(const std::vector< std::string >& bricks);

};

#endif
