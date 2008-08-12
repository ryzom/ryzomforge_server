/** \file ai_pos.h
 *
 * $Id: ai_pos.h,v 1.25 2005/12/16 09:35:09 vuarand Exp $
 */



class CAIPos;

#ifndef RYAI_POS_H
#define RYAI_POS_H

#include "ai_share/ai_vector.h"
#include "ai_vector_mirror.h"

class CAIPosMirror;


//----------------------------------------------------------------------------
// The class
//----------------------------------------------------------------------------

/** This class is an extension of CAIVector with an added height and
orientation information.

This class as an additionnal sint32 h field and a CAngle theta field. The
height unit is 1 meter length (and thus there is no precision smaller than 1
meter), and the orientation (see CAngle) is on the horizontal XY plane.

*/
class CAIPos
: public CAIVector  
{
public:
	CAIPos() : CAIVector(0., 0.), _h(0), _theta(0.f) { }
	CAIPos(CAIPos const& pos) : CAIVector(pos), _h(pos._h), _theta(pos._theta) { }
	
	explicit CAIPos(CAIVector const& xy, sint32 h, float theta) : CAIVector(xy), _h(h), _theta(theta) { }
	explicit CAIPos(CAIVector const& xy, sint32 h, CAngle const& theta) : CAIVector(xy), _h(h), _theta(theta) { }
	
	CAIPos(CAIPosMirror const& pos);
	explicit CAIPos(CAIVectorMirror const& xy, sint32 h, float theta);
	explicit CAIPos(CAIVectorMirror const& xy, sint32 h, CAngle const& theta);
	template <class C>
	explicit CAIPos(C x, C y, sint32 h, float theta) : CAIVector(x, y), _h(h), _theta(theta) { }
	template <class C>
	explicit CAIPos(C x, C y, sint32 h, CAngle theta) :CAIVector(x, y), _h(h), _theta(theta) { }
	
	std::string toString() const 
	{
		return NLMISC::toString("(%9s,%9s,%d) %3d\"",x().toString().c_str(),y().toString().c_str(),h(),theta().asDegrees());
	}
	
	inline bool operator==(const CAIPos &other)				const	{ return	CAIVector::operator==(other) && other.h()==h(); }
	inline bool operator!=(const CAIPos &other)				const	{ return	CAIVector::operator!=(other) || other.h()!=h(); }
	inline bool operator==(const CAIPosMirror &other)		const;
	inline bool operator!=(const CAIPosMirror &other)		const;	
	
	inline bool operator==(const CAIVectorMirror &other)	const	{	return CAIVector::operator==(other);	}
	inline bool operator!=(const CAIVectorMirror &other)	const	{	return CAIVector::operator!=(other);	}
	
	
	inline const CAIPos &operator= (const CAIPos &other)		{ setX(other.x()); setY(other.y()); _h=other._h; _theta=other._theta; return *this; }
	inline const CAIPos &operator= (const CAIPosMirror &other); /*	{ setX(other.x()); setY(other.y()); _h=other.h(); _theta=other.theta(); return *this; }*/
	
	template <class V> inline const CAIPos &operator+=(const V &v) { CAIVector::operator +=(v); return *this; }
	template <class V> inline const CAIPos &operator-=(const V &v) { CAIVector::operator -=(v); return *this; }
	
	template <class V> inline const CAIPos operator+(const V &v) const { CAIPos p(*this); return p+=v; }
	template <class V> inline const CAIPos operator-(const V &v) const { CAIPos p(*this); return p-=v; }
	
	inline const sint32	 &h()		const	{ return _h; }
	inline const CAngle	 &theta()	const	{ return _theta; }
	
	template <class C> inline void setH(const C &h)					{ _h=h; }
	template <class C> inline void setTheta(const C &theta)			{ _theta=theta; }
	
private:
	sint32	_h;
	CAngle	_theta;
};

//--------------------------------------------------------------------------
// The inlines
//--------------------------------------------------------------------------

#include "ai_pos_mirror.h"


inline const CAIPos &CAIPos::operator= (const CAIPosMirror &other)	
{ 
	setX(other.x()); 
	setY(other.y()); 
	_h=other.h(); 
	_theta=other.theta(); 
	return *this; 
}


inline CAIPos::CAIPos(const CAIPosMirror &pos):
CAIVector(pos.x(),pos.y()), _h(pos.h()), _theta(pos.theta())
{
}

inline CAIPos::CAIPos(const CAIVectorMirror &xy, sint32 h, float theta):
	CAIVector(xy.x(),xy.y()), _h(h), _theta(theta)		
{
}

inline CAIPos::CAIPos(const CAIVectorMirror &xy, sint32 h, const CAngle &theta):
	CAIVector(xy.x(),xy.y()), _h(h), _theta(theta)		
{
}

inline bool CAIPos::operator==(const CAIPosMirror &other) const
{
	return	(other.x()==x()) && (other.y()==y()) && other.h()==h();
}

inline bool CAIPos::operator!=(const CAIPosMirror &other) const
{
	return	!(*this == other); 
}
#endif
