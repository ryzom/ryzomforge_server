/** \file egs_static_world.h
 * <File description>
 *
 * $Id: egs_static_world.h,v 1.3 2004/12/08 13:26:46 besson Exp $
 */



#ifndef EGS_STATIC_WORLD_H
#define EGS_STATIC_WORLD_H

//Nel georges
#include "nel/georges/u_form.h"


/**
 * class used to store the world organisation ( continent ids, ... )
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2003
 */
class CStaticWorld
{
public:
	/// ctor
	CStaticWorld(){}

	/// Read georges sheet
	void readGeorges (const NLMISC::CSmartPtr<NLGEORGES::UForm> &form, const NLMISC::CSheetId &sheetId);
	/// Return the version of this class, increments this value when the content of this class has changed
	inline static uint getVersion () { return 1; }
	/// Serial
	void serial(class NLMISC::IStream &f)
	{
		f.serialCont( Continents );
	}
	/// Removed
	void removed() {}
	
	/// continent in the world (indexed by CONTINENT::TContinent)
	std::vector< NLMISC::CSheetId > Continents;
};

/**
 * class used to store a continent organisation
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2003
 */
class CStaticContinent
{
public:
	/// ctor
	CStaticContinent(){}

	/// Read georges sheet
	void readGeorges (const NLMISC::CSmartPtr<NLGEORGES::UForm> &form, const NLMISC::CSheetId &sheetId);
	/// Return the version of this class, increments this value when the content of this class has changed
	inline static uint getVersion () { return 1; }
	/// Serial
	void serial(class NLMISC::IStream &f)
	{
		f.serialCont(Outposts);
	}
	/// Removed
	void removed() {}

	/// index of the outposts in this continent
	std::vector<uint8> Outposts;
};


#endif // EGS_STATIC_WORLD_H

/* End of egs_static_world.h */

