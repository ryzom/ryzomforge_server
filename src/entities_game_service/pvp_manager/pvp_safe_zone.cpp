/** \file pvp_safe_zone.cpp
 * 
 *
 * $Id: pvp_safe_zone.cpp,v 1.4 2005/02/22 10:22:36 besson Exp $
 */


#include "stdpch.h"
#include "nel/ligo/primitive_utils.h"

#include "pvp_manager/pvp_safe_zone.h"
#include "primitives_parser.h"


using namespace std;
using namespace NLMISC;
using namespace NLNET;

NL_INSTANCE_COUNTER_IMPL(CPVPSafeZone);

//----------------------------------------------------------------------------
CPVPSafeZone::CPVPSafeZone()
: _Alias(CAIAliasTranslator::Invalid), _Center(CVector::Null), _SqrRadius(0)
{
}

#define PRIM_ASSERT(exp) \
	nlassertex( exp, ("<CPVPSafeZone::build> fatal error in primitive: '%s'", NLLIGO::buildPrimPath(point).c_str() ) )

#define PRIM_VERIFY(exp) \
	nlverifyex( exp, ("<CPVPSafeZone::build> fatal error in primitive: '%s'", NLLIGO::buildPrimPath(point).c_str() ) )

//----------------------------------------------------------------------------
NLMISC::CSmartPtr<CPVPSafeZone> CPVPSafeZone::build(const NLLIGO::CPrimPoint * point)
{
	nlassert(point);

	string value;

	CSmartPtr<CPVPSafeZone> safeZone = new CPVPSafeZone;
	nlassert( !safeZone.isNull() );

	PRIM_VERIFY( point->getPropertyByName("name", safeZone->_Name) );

	PRIM_VERIFY( CPrimitivesParser::getAlias(point, safeZone->_Alias) );
	PRIM_ASSERT( safeZone->_Alias != CAIAliasTranslator::Invalid );

	safeZone->_Center = point->Point;

	PRIM_VERIFY( point->getPropertyByName("radius", value) );
	const float radius = (float) atof(value.c_str());
	if (radius == 0)
		return NULL;
	safeZone->_SqrRadius = radius * radius;

	return safeZone;
}

#undef PRIM_ASSERT
#undef PRIM_VERIFY

//----------------------------------------------------------------------------
bool CPVPSafeZone::contains(const NLMISC::CVector & v) const
{
	if ( (_Center - v).sqrnorm() <= _SqrRadius )
		return true;

	return false;
}
