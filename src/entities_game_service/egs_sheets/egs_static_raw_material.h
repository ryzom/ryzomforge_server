/** \file egs_static_raw_material.h
 * <File description>
 *
 * $Id: egs_static_raw_material.h,v 1.4 2004/12/08 13:26:46 besson Exp $
 */



#ifndef RY_EGS_STATIC_RAW_MATERIAL_H
#define RY_EGS_STATIC_RAW_MATERIAL_H


/**
 * class for raw material *for creatures only*
 * \author David Fleury
 * \author Nevrax France
 * \date 2002
 */
class CStaticRawMaterial
{
public:
	/// Constructor
	CStaticRawMaterial() : MinQuality(0), MaxQuality(0)
	{}

	/// copy Constructor
	CStaticRawMaterial( const CStaticRawMaterial &m)
	{
		Name				= m.Name;
		AssociatedItemName	= m.AssociatedItemName;
		MinQuality			= m.MinQuality;
		MaxQuality			= m.MaxQuality;
	}


	/// Destructor
	~CStaticRawMaterial()
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
