/** \file ai_inline.h
 *
 * $Id: ai_inline.h,v 1.21 2004/08/18 14:20:46 ledorze Exp $
 */



#ifndef RYAI_AI_INLINE_H
#define RYAI_AI_INLINE_H


//-------------------------------------------------------------------
// Important boolean showing true when the singleton has been initialised
// and other pseudo-constants initialised at service init time

/*inline bool CAIS::initialised()
{
	return _initialised;
}
*/
//-------------------------------------------------------------------
// Interface to the random number generator
inline sint32 CAIS::randPlusMinus(uint16 mod)	{ return _random.randPlusMinus(mod); }
inline float CAIS::frand(double mod)			{ return _random.frand(mod); }
inline float CAIS::frandPlusMinus(double mod)	{ return _random.frandPlusMinus(mod); }

inline uint32 CAIS::rand32()
{ 
	return ((uint32(_random.rand()))<<16)+uint32(_random.rand());
}
inline uint32 CAIS::rand32(uint32 mod)
{ 
	if (mod==0)
		return	0;
	return rand32()%mod;
}
inline uint32 CAIS::rand16(uint32 mod)
{ 
	if (mod==0)
		return	0;
	return _random.rand()%mod;
}

//-------------------------------------------------------------------
// Interface to the vision management matrices

// read accessors for getting hold of the vision matrices
inline const CAIEntityMatrixIteratorTblRandom	*CAIS::matrixIterator2x2()	{ return &_matrixIterator2x2; }
inline const CAIEntityMatrixIteratorTblRandom	*CAIS::matrixIterator3x3()	{ return &_matrixIterator3x3; }


#endif


