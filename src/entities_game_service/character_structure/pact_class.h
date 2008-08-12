/** \pact_class.h
 * 
 *
 * $Id: pact_class.h,v 1.5 2004/12/08 13:26:46 besson Exp $
 */



#ifndef RY_PACT_CLASS_H
#define RY_PACT_CLASS_H

#include "game_share/pact.h"

/**
 * CPact
 *
 * \author Alain Saffray
 * \author Nevrax France
 * \date 2002
 */
struct CPact
{
	uint8	PactNature;
	uint8	PactType;

	CPact() { clear(); }
	CPact( uint8 Nature, uint8 Type ) { PactNature = Nature; PactType = Type; }

	void clear() { PactNature = GSPACT::Kamique; PactType = GSPACT::Type1; }

	bool operator == (const CPact &a) const
	{
		return (PactNature == a.PactNature && PactType == a.PactType );
	}

	bool operator != (const CPact &a) const
	{
		return (PactNature != a.PactNature || PactType != a.PactType );
	}


	// Start by declaring methods for persistent load/ save operations
	// The following macro is defined in persistent_data.h
	// At time of writing it evaluated to:
	//	void store(CPersistentDataRecord &pdr) const;
	//	void apply(CPersistentDataRecord &pdr);

	DECLARE_PERSISTENCE_METHODS

	void serial(NLMISC::IStream &f) throw(NLMISC::EStream)
	{
		f.serial( PactNature );
		f.serial( PactType );
	}
};

#endif // RY_PACT_CLASS_H
/* pact_class.h */
