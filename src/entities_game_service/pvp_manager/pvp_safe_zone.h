/** \file pvp_safe_zone.h
 * 
 *
 * $Id: pvp_safe_zone.h,v 1.4 2005/06/23 18:14:21 boucher Exp $
 */



#ifndef RY_PVP_SAFE_ZONE_H
#define RY_PVP_SAFE_ZONE_H

#include "nel/misc/smart_ptr.h"
#include "nel/ligo/primitive.h"
#include "mission_manager/ai_alias_translator.h"


/**
 * A PVP safe zone
 * \author Sébastien Guignot
 * \author Nevrax France
 * \date 2004
 */
class CPVPSafeZone : public NLMISC::CRefCount
{
	NL_INSTANCE_COUNTER_DECL(CPVPSafeZone);
public:

	/// build a PVP safe zone from a primitive
	static NLMISC::CSmartPtr<CPVPSafeZone> build(const NLLIGO::CPrimPoint * point);

public:
	/// get name
	const std::string & getName() const { return _Name; }

	/// get persistent alias
	TAIAlias getAlias() const { return _Alias; }

	/// get the center of the zone
	const NLMISC::CVector & getCenter() const { return _Center; }

	/// get the square of the radius (in meters)
	const float getSqrRadius() const { return _SqrRadius; }

	/// returns true if the zone contains the given position
	bool contains(const NLMISC::CVector & v) const;

protected:
	/// ctor
	CPVPSafeZone();

private:
	/// name of the zone
	std::string		_Name;

	/// persistent alias
	TAIAlias		_Alias;

	/// center of the zone
	NLMISC::CVector	_Center;

	/// square of the radius
	float			_SqrRadius;
};

#endif // RY_PVP_SAFE_ZONE
