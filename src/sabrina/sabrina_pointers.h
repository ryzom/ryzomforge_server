/** \file sabrina_pointers.h
 * Interface for all Sabrina phrases
 *
 * $Id: sabrina_pointers.h,v 1.3 2004/03/01 19:22:19 lecroart Exp $
 */




#ifndef RY_SABRINA_POINTERS_H
#define RY_SABRINA_POINTERS_H

#include "nel/misc/smart_ptr.h"
 
/**
 * ISabrinaPhraseModel safe pointer
 * \author Sadge
 * \author Nevrax France
 * \date 2003
 */

class ISabrinaPhraseModel;
typedef NLMISC::CSmartPtr<ISabrinaPhraseModel> ISabrinaPhraseModelPtr;


/**
 * CSabrinaPhraseInstance safe pointer
 * \author Sadge
 * \author Nevrax France
 * \date 2003
 */

class CSabrinaPhraseInstance;
typedef NLMISC::CSmartPtr<CSabrinaPhraseInstance> CSabrinaPhraseInstancePtr;


/**
 * Sabrina actor base class safe pointer
 * \author Sadge
 * \author Nevrax France
 * \date 2003
 */

//class ISabrinaActor;
//typedef NLMISC::CSmartPtr<ISabrinaActor> ISabrinaActorPtr;


/**
 * ISabrinaPhraseDescription safe pointer
 * \author Sadge
 * \author Nevrax France
 * \date 2003
 */

class ISabrinaPhraseDescription;
typedef NLMISC::CSmartPtr<ISabrinaPhraseDescription> ISabrinaPhraseDescriptionPtr;


#endif
