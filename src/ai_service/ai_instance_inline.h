/** \file ai_instance_inline.h
 *
 * $Id: ai_instance_inline.h,v 1.6 2006/05/31 12:10:21 boucher Exp $
 */



#ifndef RYAI_AI_INSTANCE_INLINE_H
#define RYAI_AI_INSTANCE_INLINE_H

inline
CContinent* CAIInstance::locateContinentForPos(CAIVector const& pos)
{
	FOREACH(it, CCont<CContinent>, _Continents)
	{
		if (it->_BoundingBox.isInside(pos))
			return	*it;
	}
	return NULL;
}

inline
CRegion* CAIInstance::locateRegionForPos(CAIVector const& pos)
{
	CContinent* cont = locateContinentForPos(pos);
	if	(!cont)
		return	NULL;
	FOREACH(it, CCont<CRegion>, cont->regions())
	{
		if (it->_BoundingBox.isInside(pos))
			return *it;
	}
	return NULL;
}

inline
CCellZone* CAIInstance::locateCellZoneForPos(CAIVector const& pos)
{
	CRegion* region = locateRegionForPos(pos);
	if (!region)
		return	NULL;
	FOREACH(it, CCont<CCellZone>, region->cellZones())
	{
		if (it->_BoundingBox.isInside(pos))
			return *it;
	}
	return NULL;
}

inline
CCell* CAIInstance::locateCellForPos(CAIVector const& pos)
{
	CCellZone* cz = locateCellZoneForPos(pos);
	if (!cz)
		return NULL;
	FOREACH(it, CCont<CCell>, cz->cells())
	{
		if	(it->_BoundingBox.isInside(pos))
			return *it;
	}
	return NULL;
}

#endif
