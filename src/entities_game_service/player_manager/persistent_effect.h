/* \file persistent_effect.h
 *
 * $Id: persistent_effect.h,v 1.2 2006/10/09 15:53:42 saffray Exp $
 */


#ifndef PERSISTENT_EFFECT_H
#define PERSISTENT_EFFECT_H

//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

// NeL Misc
#include "nel/misc/time_nl.h"

#include "game_share/persistent_data.h"

#include <vector>

//-------------------------------------------------------------------------------------------------
// forward decalarations
//-------------------------------------------------------------------------------------------------

class CCharacter;
class CSTimedEffect;

//-------------------------------------------------------------------------------------------------
// class CPersistentEffect
//-------------------------------------------------------------------------------------------------

/**
 *	CPersistentEffect
 * \author Alain Saffray
 * \author Nevrax France
 * \date 2006
 */

class CPersistentEffect
{
public:
	DECLARE_VIRTUAL_PERSISTENCE_METHODS
	
	// default ctor
	CPersistentEffect(CCharacter* theCharacter);

	// dtor
	~CPersistentEffect();

	// copy persistent effect class in _PersitentEffects vector
	void collectPersistentEffect();

	// clear _PersistentEffects vector
	void clear();

	// activate all persistent effects
	void activate();

	// read/write specific method for store and apply persistent data
	void writePdr(CSTimedEffect * effect, CPersistentDataRecord& pdr) const;
	void readPdr(CPersistentDataRecord& pdr);

private:
	CCharacter *	_TheCharacter;
	// vector of effects must be persistent
	std::vector< NLMISC::CSmartPtr<CSTimedEffect> >	_PersistentEffects;
};


#endif // PERSISTENT_EFFECT_H
