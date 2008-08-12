/** \file sabrina_phrase_model_fight.h
 * Interface for all Sabrina phrases
 *
 * $Id: sabrina_phrase_model_fight.h,v 1.2 2004/03/01 19:22:19 lecroart Exp $
 */




#ifndef RY_SABRINA_PHRASE_MODEL_FIGHT_H
#define RY_SABRINA_PHRASE_MODEL_FIGHT_H

#include "sabrina_phrase_model.h"
 
/**
 * Base virtual class for all Sabrina phrases
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CSabrinaPhraseModelFight : public ISabrinaPhraseModel
{
public:
	//--------------------------------------------------------------------
	// specialisation of virtual methods from ISabrinaPhraseModel

	virtual bool addBrick( const CStaticBrick* brick ) 
	{
		return true;	// TODO
	}

	virtual bool isValid( ) 
	{
		return true;	// TODO
	}

	virtual SABRINA::TEventCode evaluate(const CSabrinaPhraseInstance* phraseInstance, CEvalReturnInfos* msg = NULL) 
	{
		return SABRINA::SuccessNormal;	// TODO
	}

	virtual bool requiresTarget() 
	{
		return true;
	}

	virtual SABRINA::TEventCode validate(const CSabrinaPhraseInstance* phraseInstance) 
	{
		return SABRINA::SuccessNormal;	// TODO
	}

	virtual uint32 calculatePreExecutionDelay(const CSabrinaPhraseInstance* phraseInstance) 
	{
		return 10;		// TODO
	}

	virtual SABRINA::TEventCode executeAndApplyResults(const CSabrinaPhraseInstance* phraseInstance) 
	{
		return SABRINA::SuccessNormal;	// TODO
	}

	virtual uint32 calculatePostExecutionDelay(const CSabrinaPhraseInstance* phraseInstance) 
	{
		return 0;		// TODO
	}
};

#endif
