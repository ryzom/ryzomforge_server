/** \file mirror_equipment.h
 * 
 *
 * $Id: mirror_equipment.h,v 1.7 2005/02/22 10:25:14 besson Exp $
 */



#ifndef RY_MIRROR_EQUIPMENT_H
#define RY_MIRROR_EQUIPMENT_H

#include "nel/misc/types_nl.h"
#include "nel/misc/stream.h"
#include "nel/misc/sheet_id.h"
#include "game_share/persistent_data.h"
//


/**
 * SMirrorEquipment
 * \author Alain Saffray
 * \author Nevrax France
 * \date 2002
 */
class SMirrorEquipment
{
public:
	// Start by declaring methods for persistent load/ save operations
	// The following macro is defined in persistent_data.h
	// At time of writing it evaluated to:
	//	void store(CPersistentDataRecord &pdr) const;
	//	void apply(CPersistentDataRecord &pdr);

	DECLARE_PERSISTENCE_METHODS

	NLMISC::CSheetId	IdSheet;
	uint16				Quality;

	// Default contructor
	SMirrorEquipment() { IdSheet = 0; Quality = 0; }
	SMirrorEquipment( const NLMISC::CSheetId& id, uint16 Q ) { IdSheet = id; Quality = Q; }

	// operators
	const SMirrorEquipment &operator = (const SMirrorEquipment &e)
	{
		IdSheet = e.IdSheet;
		Quality = e.Quality;
		return *this;
	}

	virtual bool operator == (const SMirrorEquipment &e) const
	{
		return ( IdSheet == e.IdSheet && Quality == e.Quality);
	}

	virtual bool operator != (const SMirrorEquipment &e) const
	{
		return ( IdSheet != e.IdSheet || Quality != e.Quality);
	}

	void serial(NLMISC::IStream &f) throw(NLMISC::EStream)
	{
		f.serial( IdSheet );
		f.serial( Quality );
	}
};

namespace NLMISC
{
	std::string toString( const SMirrorEquipment& );
};

#endif // RY_MIRROR_EQUIPMENT_H
/* End of mirror_equipment.h */

