/** \file mp.h
 * <File description>
 *
 * $Id: mp.h,v 1.4 2004/12/08 13:26:46 besson Exp $
 */



#ifndef BS_MP_H
#define BS_MP_H

#include "egs_sheets/egs_static_raw_material.h"

/**
 * class for raw material
 * \author David Fleury
 * \author Nevrax France
 * \date 2002
 */
class CRawMaterial
{
public:
	/// Constructor
	CRawMaterial() : MinQuality(0), MaxQuality(0)
	{}

	/// copy Constructor
	CRawMaterial( const CRawMaterial &m)
	{
		Name				= m.Name;
		AssociatedItemName	= m.AssociatedItemName;
		MinQuality			= m.MinQuality;
		MaxQuality			= m.MaxQuality;
	}


	/// copy Constructor
	CRawMaterial( const CStaticRawMaterial &m)
	{
		Name				= m.Name;
		AssociatedItemName	= m.AssociatedItemName;
		MinQuality			= m.MinQuality;
		MaxQuality			= m.MaxQuality;
	}
	

	/// Destructor
	~CRawMaterial()
	{}

	/// serial
	void serial(class NLMISC::IStream &f)
	{
		f.serial( Name );
		f.serial( AssociatedItemName );
		f.serial( MinQuality );
		f.serial( MaxQuality );
	}

public:
	/// name of the mp
	std::string		Name;

	/// associated item name
	std::string		AssociatedItemName;

	/// min quality
	uint8			MinQuality;

	/// max quality
	uint8			MaxQuality;
};


#endif // BS_MP_H

/* End of mp.h */
