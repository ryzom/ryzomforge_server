/** \file sabrina_messages.h
 * Interface for all Sabrina phrases
 *
 * $Id: sabrina_messages.h,v 1.2 2004/03/01 19:22:19 lecroart Exp $
 */




#ifndef RY_SABRINA_MESSAGES_H
#define RY_SABRINA_MESSAGES_H

#include "nel/misc/types_nl.h"
#include "game_share/sentence_appraisal.h"
 
struct CEvalReturnInfos
{
	CEvalReturnInfos()
		:Cost(0),Valid(false), Appraisal(SENTENCE_APPRAISAL::Undefined){}
	uint32			Cost;
	//std::string		ReturnString;
	SENTENCE_APPRAISAL::ESentenceAppraisal Appraisal;
	bool			Valid;
};

#endif
