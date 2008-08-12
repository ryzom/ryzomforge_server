/** \file ai_pos_mirror.h
 *
 * $Id: ai_pos_mirror.h,v 1.13 2005/12/16 09:35:09 vuarand Exp $
 */



#ifndef RYAI_POS_MIRROR_H
#define RYAI_POS_MIRROR_H

//#include "ai.h"
#include "ai_vector_mirror.h"


class CAngle;
class CAIPos;
class CAIVector;

//----------------------------------------------------------------------------
// The class
//----------------------------------------------------------------------------

/** A position based on CAIPos with components in the mirror shared memory.



*/

class CAIPosMirror: public CAIVectorMirror  
{
public:
	// ctor
	inline CAIPosMirror(const TDataSetRow& entityIndex=TDataSetRow());
	inline std::string toString() const; 

	// == and != operators
	inline bool operator==(const CAIPos &other)	const;
	inline bool operator!=(const CAIPos &other)	const;
	
	inline bool operator==(const CAIPosMirror &other)	 const;
	inline bool operator!=(const CAIPosMirror &other)	 const;
	
	// = operator
	inline const CAIPosMirror &operator=(const CAIPos &other);

	// += and -= operators
	template <class C>	inline const CAIPosMirror &operator+=(const C &v);
	template <class C>	inline const CAIPosMirror &operator-=(const C &v);

	// * and / operators
	inline const CAIPos  operator* (double d)	const;
	inline const CAIPos  operator/ (double d)	const;

	// + and - operators
	inline CAIPos  operator+ (const NLMISC::CVector2d &v)		const;
	template <class C> 	inline CAIPos  operator+ (const C &v)	const;
	template <class C>	inline CAIPos  operator- (const C &v)	const;
	
	inline const sint32 &h()	const;
	inline CAngle	theta()		const;
	template <class C> inline void setH(C h);
	template <class C> inline void setTheta(C theta);
	
private:
	CMirrorPropValue<TYPE_POSZ>			_h;
	CMirrorPropValue<TYPE_ORIENTATION>	_theta;
};

#include "ai_pos_mirror_inline.h"

#endif

